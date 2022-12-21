// license:BSD-3-Clause
// copyright-holders:Gaston90 (2016-2022)
#include "../mame/drivers/toaplan2.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( batsugunhc01 )
	ROM_REGION( 0x080000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tp030_hc01.bin", 0x000000, 0x080000, CRC(63d28fd3) SHA1(aa3e111d596f408b735e4f79ab654eea24bd6f0c) )

	ROM_REGION( 0x400000, "gp9001_0", 0 )
	ROM_LOAD( "tp030_3l.bin", 0x000000, 0x100000, CRC(3024b793) SHA1(e161db940f069279356fca2c5bf2753f07773705) )
	ROM_LOAD( "tp030_3h.bin", 0x100000, 0x100000, CRC(ed75730b) SHA1(341f0f728144a049486d996c9bb14078578c6879) )
	ROM_LOAD( "tp030_4l.bin", 0x200000, 0x100000, CRC(fedb9861) SHA1(4b0917056bd359b21935358c6bcc729262be6417) )
	ROM_LOAD( "tp030_4h.bin", 0x300000, 0x100000, CRC(d482948b) SHA1(31be7dc5cff072403b783bf203b9805ffcad7284) )

	ROM_REGION( 0x200000, "gp9001_1", 0 )
	ROM_LOAD( "tp030_5.bin",  0x000000, 0x100000, CRC(bcf5ba05) SHA1(40f98888a29cdd30cda5dfb60fdc667c69b0fdb0) )
	ROM_LOAD( "tp030_6.bin",  0x100000, 0x100000, CRC(0666fecd) SHA1(aa8f921fc51590b5b05bbe0b0ad0cce5ff359c64) )

	ROM_REGION( 0x40000, "oki1", 0 )
	ROM_LOAD( "tp030_2.bin", 0x00000, 0x40000, CRC(276146f5) SHA1(bf11d1f6782cefcad77d52af4f7e6054a8f93440) )
ROM_END

ROM_START( mahoudaihc01 )
	ROM_REGION( 0x080000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "ra_ma_01_01.u65", 0x000000, 0x080000, CRC(970ccc5c) SHA1(c87cab83bde0284e631f02e50068407fee81d941) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "ra-ma-01_02.u66", 0x00000, 0x10000, CRC(eabfa46d) SHA1(402c99ebf88f9025f74f0a28ced22b7882a65eb3) )

	ROM_REGION( 0x200000, "gp9001_0", 0 )
	ROM_LOAD( "ra-ma01-rom2_hc01.u2",  0x000000, 0x100000, CRC(865bd232) SHA1(5e8f26b16356c314e244e939ebe696598c1e260d) )
	ROM_LOAD( "ra-ma01-rom3_hc01.u1",  0x100000, 0x100000, CRC(Be068595) SHA1(3e0f9179fce5d9337c18021debe3954157657568) )

	ROM_REGION( 0x008000, "text", 0 )
	ROM_LOAD( "ra_ma_01_05_hc01.u81",  0x000000, 0x008000, CRC(95d5d1dc) SHA1(a42cabb68443fe71702e552754ed0326480e7c98) )

	ROM_REGION( 0x40000, "oki1", 0 )
	ROM_LOAD( "ra-ma01-rom1.u57", 0x00000, 0x40000, CRC(6edb2ab8) SHA1(e3032e8eda2686f30df4b7a088c5a4d4d45782ed) )
ROM_END

ROM_START( snowbro2hc01 )
	ROM_REGION( 0x080000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pro-4_hc01", 0x000000, 0x080000, CRC(1ad75ae7) SHA1(4c9d7480df4b94aaee5616939547456a0c560f19) )

	ROM_REGION( 0x300000, "gp9001_0", 0 )
	ROM_LOAD( "rom2-l", 0x000000, 0x100000, CRC(e9d366a9) SHA1(e87e3966fce3395324b90db6c134b3345104c04b) )
	ROM_LOAD( "rom2-h", 0x100000, 0x080000, CRC(9aab7a62) SHA1(611f6a15fdbac5d3063426a365538c1482e996bf) )
	ROM_LOAD( "rom3-l", 0x180000, 0x100000, CRC(eb06e332) SHA1(7cd597bfffc153d178530c0f0903bebd751c9dd1) )
	ROM_LOAD( "rom3-h", 0x280000, 0x080000, CRC(df4a952a) SHA1(b76af61c8437caca573ff1312832898666a611aa) )

	ROM_REGION( 0x80000, "oki1", 0 )
	ROM_LOAD( "rom4", 0x00000, 0x80000, CRC(638f341e) SHA1(aa3fca25f099339ece1878ea730c5e9f18ec4823) )
ROM_END

ROM_START( snowbro2hc02 )
	ROM_REGION( 0x080000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "pro-4_hc02", 0x000000, 0x080000, CRC(2f219f0a) SHA1(49057ca9f736cd7c8c4588554599250b4aaf6cd1) )

	ROM_REGION( 0x300000, "gp9001_0", 0 )
	ROM_LOAD( "rom2-l", 0x000000, 0x100000, CRC(e9d366a9) SHA1(e87e3966fce3395324b90db6c134b3345104c04b) )
	ROM_LOAD( "rom2-h", 0x100000, 0x080000, CRC(9aab7a62) SHA1(611f6a15fdbac5d3063426a365538c1482e996bf) )
	ROM_LOAD( "rom3-l", 0x180000, 0x100000, CRC(eb06e332) SHA1(7cd597bfffc153d178530c0f0903bebd751c9dd1) )
	ROM_LOAD( "rom3-h", 0x280000, 0x080000, CRC(df4a952a) SHA1(b76af61c8437caca573ff1312832898666a611aa) )

	ROM_REGION( 0x80000, "oki1", 0 )
	ROM_LOAD( "rom4", 0x00000, 0x80000, CRC(638f341e) SHA1(aa3fca25f099339ece1878ea730c5e9f18ec4823) )
ROM_END

ROM_START( pipibibshc01 )
	ROM_REGION( 0x040000, "maincpu", 0 )         
	ROM_LOAD16_BYTE( "tp025-1_hc01.bin", 0x000000, 0x020000, CRC(38da1e2f) SHA1(890c5cc8e45ad709f48167c47dac0543da448175) )
	ROM_LOAD16_BYTE( "tp025-2_hc01.bin", 0x000001, 0x020000, CRC(7f6f32b3) SHA1(39b4ff18c266b6c9c86760379740618a0a479242) )

	ROM_REGION( 0x10000, "audiocpu", 0 )       
	ROM_LOAD( "tp025-5.bin", 0x0000, 0x8000, CRC(bf8ffde5) SHA1(79c09cc9a0ea979f5af5a7e5ad671ea486f5f43e) )

	ROM_REGION( 0x200000, "gp9001_0", 0 )
	ROM_LOAD( "tp025-4.bin", 0x000000, 0x100000, CRC(ab97f744) SHA1(c1620e614345dbd5c6567e4cb6f55c61b900d0ee) )
	ROM_LOAD( "tp025-3.bin", 0x100000, 0x100000, CRC(7b16101e) SHA1(ae0119bbfa0937d18c4fbb0a3ef7cdc3b9fa6b56) )
ROM_END

ROM_START( pipibibshc02 )
	ROM_REGION( 0x040000, "maincpu", 0 )         
	ROM_LOAD16_BYTE( "tp025-1_hc02.bin", 0x000000, 0x020000, CRC(28cec0bf) SHA1(f08a33249df902c76bbe717dbb8c25e9be2497eb) )
	ROM_LOAD16_BYTE( "tp025-2_hc02.bin", 0x000001, 0x020000, CRC(f3df3f3f) SHA1(96245fab49f23af4957e163509afdae7f51d11e7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )       
	ROM_LOAD( "tp025-5.bin", 0x0000, 0x8000, CRC(bf8ffde5) SHA1(79c09cc9a0ea979f5af5a7e5ad671ea486f5f43e) )

	ROM_REGION( 0x200000, "gp9001_0", 0 )
	ROM_LOAD( "tp025-4.bin", 0x000000, 0x100000, CRC(ab97f744) SHA1(c1620e614345dbd5c6567e4cb6f55c61b900d0ee) )
	ROM_LOAD( "tp025-3.bin", 0x100000, 0x100000, CRC(7b16101e) SHA1(ae0119bbfa0937d18c4fbb0a3ef7cdc3b9fa6b56) )
ROM_END

/*    YEAR  NAME           PARENT           MACHINE    INPUT                       INIT        MONITOR   COMPANY       FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2015, batsugunhc01,  batsugun,        batsugun, batsugun, toaplan2_state, init_dogyuun,  ROT270,  "hack",       "Batsugun Transparent (Crazy Gun Transparent Version 2015-03-22)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, mahoudaihc01,  sstriker,        mahoudai, mahoudai, toaplan2_state, empty_init,    ROT270,  "hack",       "Mahou Daisakusen (Translation Chinese)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, snowbro2hc01,  snowbro2,        snowbro2, snowbro2, toaplan2_state, empty_init,    ROT0,    "hack",       "Snow Bros 2 (Ex Super Version)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, snowbro2hc02,  snowbro2,        snowbro2, snowbro2, toaplan2_state, empty_init,    ROT0,    "DDJ",        "Snow Bros 2 (Change Character)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, pipibibshc01,  pipibibs,        pipibibs, pipibibs, toaplan2_state, empty_init,    ROT0,    "DDJ",        "Pipi & Bibis (Stage Select V1)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, pipibibshc02,  pipibibs,        pipibibs, pipibibs, toaplan2_state, empty_init,    ROT0,    "DDJ",        "Pipi & Bibis (Stage Select V2)", MACHINE_SUPPORTS_SAVE )
