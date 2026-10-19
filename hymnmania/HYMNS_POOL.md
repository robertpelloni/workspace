# Hymn Pool — 100 hymns & choruses (MIDI library)

_Last updated: 2026-09-10 (v5.97.20)_

Source: `submodules/ableton_psytrance_hymn_creator/hymnmania_src/hymn_remaker/input/`

The **46 classical pieces are kept separately** — see `CLASSICAL_PIECES.md`.

**Removed / blocked** (do not re-add) — see `BLOCKED_HYMNS.md`:
O Happy Day · Kumbayah · Brighten The Corner Where You Are · Leyenda · Praise Him! Praise Him! · Just Over The Mountains

## 100 hymns / choruses

  1. A_Childs_Prayer
  2. Adventist Youth
  3. Are You A Christian
  4. Are You Ready For Jesus To Come
  5. As For Me
  6. Beautiful
  7. Behold What Manner Of Love 1 John 3 1
  8. Blessed Be The Lord God Almighty
  9. Brighten The Corner Where You Are
 10. Can The World See Jesus In You
 11. Cares Chorus
 12. Christ The Joy Of Loving Hearts
 13. Come And Sing Praises
 14. Do You Know My Jesus
 15. Do, Lord
 16. Down In My Heart
 17. Echo Chorus
 18. Emmanuel
 19. Every Day With Jesus
 20. Every Moment Of Every Day
 21. Everybody Ought To Know
 22. Everything's Alright
 23. Far Beyond The Sun
 24. Father, I Adore You
 25. Father, We Love You
 26. Follow Me
 27. For God So Loved The World
 28. For God So Loved The World with Tag
 29. Friends
 30. Give Me Oil In My Lamp
 31. God Is So Good
 32. God's Love Is Wonderful
 33. Great Are You, Lord
 34. Ha-la-la-la-la
 35. Hallelu, Hallelu
 36. Happiness Is The Lord
 37. Happy All The Time
 38. He Keeps Me Singing
 39. He Lives
 40. He's Able
 41. He's Got The Whole World
 42. Heaven Came Down And Glory Filled My Soul
 43. Here Am I, Lord
 44. His Banner Over Me Is Love
 45. His Name Is Wonderful
 46. How Majestic Is Your Name
 47. Humble Thyself
 48. I Am A Christian
 49. I Have Decided To Follow Jesus
 50. I Just Came To Praise The Lord
 51. I Just Keep Trusting My Lord
 52. I Just Keep Trusting My Lord with Tag
 53. I Know The Lord Has Made A Way
 54. I Know The Lord Has Made A Way Tag
 55. I Shall Not Be Moved
 56. I Shall See The King
 57. I Want To Be Ready
 58. I Will Make You Fishers Of Men
 59. I Will Serve Thee
 60. I Will Sing Of The Mercies Of The Lord Psalm 89 1
 61. I'll Share My Faith
 62. I'm So Happy
 63. I've Found The Way
 64. I've Got A River Of Life
 65. I've Got Love Like An Ocean
 66. If You Know The Lord
 67. If You Want Joy
 68. In His Time
 69. In Moments Like These
 70. In My Heart There Rings A Melody
 71. In The Name Of Jesus
 72. In The Name Of Jesus with Yesterday, Today, Forever
 73. In The Service Of The King
 74. Isn't He Wonderful
 75. It's About Grace
 76. It's the Sabbath
 77. Jesus Is Coming Again
 78. Jesus Is The Joy Of Living
 79. Jesus, Name Above All Names
 80. Joy Is The Flag
 81. Just To Know Him
 82. King Of Kings
 83. Kumbayah
 84. Let's Sing A Happy Song
 85. Lord, Be Glorified
 86. Love Is In Your Hand
 87. Love Is Something
 88. Love, Love
 89. Majesty
 90. Make A Joyfiul Noise
 91. Make Me A Servant
 92. Mansion Over The Hilltop
 93. Maranatha
 94. My God Is So Great
 95. My God Loves Me
 96. My Lord Knows The Way
 97. My Peace
 98. New Life In Christ
 99. O Friend Do You Love Jesus
100. O How He Loves You And Me

---

### Already covered (beat videos on the channel)
Amazing Grace · Canon in D · Clair de Lune · How Great Thou Art · Thy Word · Emmanuel ·
Oh For a Thousand Tongues · He Leadeth Me · Winchester · Neon Valse · Toccata and Fugue in D minor ·
Jesus Comes With Power · When Love Shines In · God Is So Good · I Have Decided To Follow Jesus

### How to add a hymn to the pipeline
1. Render MIDI → sine MP3:
   `python scripts/audio_synthesis_render_midi_to_sine_wave_clean.py --midi "<file>.mid" --wav out.wav`
2. Upload + check: `python upload_robust2.py out.wav 3` → must print **VERIFIED**
   (a copyright match means the melody is fingerprinted → quarantine it)
3. Generate: `python gen_only.py psytrance <clip_id> "<Hymn Title>"`
4. Capture:  `python cap_cycle.py <cover_clip_id> "generated/<Hymn>_10x_psytrance_A_cover.mp3"`
5. Register the hymn in `post_to_youtube.PIECES` and `youtube_update_descriptions.HYMNS`
6. Compose + post (or let the scheduler pick it up)
