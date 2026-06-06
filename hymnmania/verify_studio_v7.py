import asyncio
from playwright.async_api import async_playwright
import os

async def verify():
    async with async_playwright() as p:
        browser = await p.chromium.launch()
        page = await browser.new_page()
        try:
            await page.goto("http://localhost:8501", timeout=30000)
            await asyncio.sleep(5)
            tabs = await page.query_selector_all('button[role="tab"]')
            if len(tabs) >= 3:
                await tabs[2].click()
                await asyncio.sleep(2)

            await page.screenshot(path="studio_v7_interactive.png", full_page=True)
            print("Screenshot saved to studio_v7_interactive.png")
        except Exception as e:
            print(f"Error: {e}")
        finally:
            await browser.close()

if __name__ == "__main__":
    asyncio.run(verify())
