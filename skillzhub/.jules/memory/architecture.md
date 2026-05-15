**Architecture Overview**
SkillzHub is a C2B marketplace MVP designed to bridge the gap between human creators capturing real-world GoPro/FPV footage and enterprise robotics/AI companies needing structured, high-fidelity datasets. The architecture is modular, host-agnostic, and API-first, built on a modern full-stack web framework.

*   **Frontend/Backend Engine:** Next.js 16.2.6 utilizing the App Router. The platform leverages Server Components for performance, Server Actions for mutations, and Route Handlers for the REST API layer (`/api/v1/*`).
*   **Database & ORM:** PostgreSQL managed via Neon, accessed using Prisma ORM. The schema includes entities for `User`, `Mission`, `Submission`, `Dataset`, `DatasetSample`, `APIKey`, and `PaymentLedger`.
*   **Authentication & Security:** 
    *   NextAuth (v5 Beta) handles session-based authentication for the web UI.
    *   Role-Based Access Control (RBAC) isolates permissions strictly between Creator, Company, and Admin users.
    *   Programmatic access for Companies uses generated API keys, hashed using SHA-256 for fast `O(1)` database lookups, intentionally avoiding bcrypt to prevent DoS vulnerabilities on the event loop.
    *   API input payload validation is strictly enforced using Zod (`src/lib/schemas/index.ts`).
    *   Edge Validation: The Next.js Edge Middleware intercepts API requests (`src/middleware.ts`), immediately returning a 401 response for malformed Bearer tokens before they hit the Node.js event loop or database connection pool.
*   **Asynchronous Processing Pipeline:** BullMQ running on top of an `ioredis` client handles async video processing tasks triggered upon file upload. This isolates heavy media operations from the web server thread. This worker is containerized independently via `Dockerfile.worker`.
    *   **Normalization:** Uses `fluent-ffmpeg` and `@ffmpeg-installer/ffmpeg` to extract real metadata (resolution, duration, fps) and enforce QA constraints.
    *   **Auto-Labeling:** Integrates the `@google/genai` (Gemini API) SDK via a VLM processing stub (`src/lib/services/vlm-processor.ts`) to automatically infer `action_summary`, `objects`, and `environment` labels directly from the video stream.
*   **Rate Limiting:** A Redis-backed token bucket algorithm (`src/lib/rate-limit.ts`) protects sensitive endpoints like registration and file uploads. It utilizes an atomic Lua script (get-and-increment with conditional expire) to prevent race conditions and fails open if Redis is unavailable.

**Core Integrations & Patterns**
*   **Storage (`src/lib/services/storage.ts`):** Integrated with the AWS SDK (`@aws-sdk/client-s3` and `@aws-sdk/s3-request-presigner`). The platform generates presigned URLs for secure, direct-to-bucket video uploads (Creators), temporary dataset downloads (Companies), and raw video previews for the Admin QC Dashboard (`/api/v1/admin/submissions/[id]/video`) and Creator Dashboard (`/api/v1/creator/submissions/[id]/video`).
*   **Payments (`src/lib/services/payments.ts`):** Integrated with the official `stripe` Node.js SDK. Uses Stripe Connect Express for Creator onboarding (`stripe.accountLinks.create`) and executes programmatic transfers (`stripe.transfers.create`) to route funds to creators when an Admin accepts a video submission.
*   **Webhooks (`src/lib/services/webhooks.ts`):** Supports asynchronous webhook dispatch to company endpoints when new dataset samples are approved. Payloads are signed with a SHA-256 HMAC signature using the company's custom secret to guarantee origin authenticity.
*   **Creator Trust Tiers:** The `User` model tracks a `trust_tier` (default 1). If a creator achieves Tier 2 or higher, their videos bypass the manual Admin QC queue and are automatically accepted by the BullMQ worker upon passing automated ffmpeg checks, triggering instant dataset generation and payouts.
*   **Marketplace Dynamics (Bounty Boosts):** Companies can dynamically surge pricing on open missions by +20% (`/api/v1/missions/[id]/boost`) via the UI to incentivize immediate creator fulfillment.
*   **Lazy Instantiation:** External service clients (Stripe, Redis, Gemini) are lazily instantiated inside their service modules. This prevents Next.js static build generation from hanging or failing if environment variables are temporarily missing during the build phase.
*   **Dataset Generation (Idempotency):** Uses upsert-style logic during the Admin review phase. If a Dataset already exists for a specific mission, the duration is simply appended, and the sample is attached. This mitigates duplicate datasets if multiple submissions are approved concurrently.
*   **API Documentation:** Interactive OpenAPI (Swagger) documentation is automatically generated from JSDoc comments via `swagger-jsdoc` and rendered using `swagger-ui-react` at `/docs`.
*   **Data Aggregation:** Dedicated analytics endpoints (`/api/v1/company/analytics`) leverage Prisma's `groupBy` and `aggregate` functions to generate complex charting data (Total Capital Deployed, Pipeline Status Distributions, Dataset Volumes) rendered via Recharts on the frontend.
*   **Error Boundaries:** The UI implements `src/app/error.tsx` and `src/app/global-error.tsx` to trap unhandled runtime errors, replacing raw server stack traces with graceful, user-friendly recovery prompts.

**Testing Strategy**
*   **Frameworks:** Vitest (Integration/Unit) and Playwright (E2E).
*   **Mocks & Isolation:** The test setup (`vitest.setup.ts`) globally mocks `next/server` (`NextRequest`, `NextResponse`), `ioredis`, `bullmq`, Prisma, NextAuth, and the AWS SDK. Background worker logic (like FFprobe metadata extraction) is extracted into pure utility functions (`src/lib/video-processor.ts`) to enable direct unit testing. 
*   **E2E:** `playwright.config.ts` is configured to spin up the local Next.js dev server dynamically and run DOM verification tests against Chromium (e.g., `e2e/home.spec.ts`).

**Development Directives & Repository Rules**
1.  **Versioning:** Every operational session must result in a version bump. The global version is stored in a root `VERSION` file, documented in `CHANGELOG.md`, visually displayed in the frontend layout (`src/app/layout.tsx`), and explicitly noted in the git commit message.
2.  **Documentation & Organization:** The project maintains a strict suite of global documentation (`VISION.md`, `ROADMAP.md`, `TODO.md`, `IDEAS.md`, `LIBRARIES.md`, `DEPLOY.md`, `HANDOFF.md`). The repository is kept clean by grouping related service utilities in `src/lib/services/` and storing agent instruction profiles in `docs/agents/`.
3.  **Code Comments:** Code must be commented in extreme depth, explaining the "why" and highlighting architectural reasoning. Self-explanatory code should be left bare.
4.  **UI Representation:** Every implemented backend feature must be comprehensively represented in the UI, fully functional, and well-documented for the end-user.
5.  **Submodules & Branching:** Always merge feature branches intelligently into `main` to prevent regression. Outdated feature branches should be back-merged from `main` to catch them up. All submodules must be updated recursively during syncs.
6.  **Environment Constraints:** Docker is avoided for local execution due to host permission quirks; cloud services (Neon, Upstash) or native installations are preferred. Blocking terminal commands (e.g., `npm run dev`) must be run in the background. Node processes should never be mass-killed, as this destroys the active agent environment.