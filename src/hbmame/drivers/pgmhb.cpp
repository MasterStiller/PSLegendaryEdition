// license:BSD-3-Clause
// copyright-holders:Gaston90
#include "../mame/drivers/pgm.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( kovplushc01 ) //kovplus2012dw
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hc01.119", 0x100000, 0x400000, CRC(4403c58b) SHA1(8d80bc4a312975d0584edb1796ee8a5a13234b88) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600hc01.rom",     0x180000, 0x800000, CRC(842b7711) SHA1(b999d55e6e304b4057c66d57bf970f7b181ddac8) )

	ROM_REGION( 0x1c00000, "sprcol", 0 )
	ROM_LOAD( "a0600_hc01.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601.rom",         0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a060_hc01.rom",     0x1000000, 0x0800000, CRC(b64e6473) SHA1(d231b85d1a3466565a90b2bb1489ef3038377fd2) )
	ROM_LOAD( "a0603.rom",         0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hc01.rom",    0x0000000, 0x0800000, CRC(07d91ea3) SHA1(8713409439eb4a2875baffbda711587f283a652b) )
	ROM_LOAD( "b0601_hc01.rom",    0x0800000, 0x0400000, CRC(3737c3f7) SHA1(ed01d926ac080991fd5b98b04977dde84152f8e1) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "pgm_m01s_hc01.rom", 0x000000, 0x200000, CRC(692511a5) SHA1(b272fdd0aa3724ba8ff30d2568c3a6b63f1358b3) )
	ROM_LOAD( "m0600_hc01.rom",    0x400000, 0x400000, CRC(7a50501b) SHA1(1af6be69f3133ed56d4a132a1910cf562da83dac) )
ROM_END

ROM_START( kovplushc02 ) //kovplus12dw
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hc02.119",    0x100000, 0x400000, CRC(f14c9032) SHA1(93d09d9381955f49e687447dfe80c8c37ce37488) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hc02.rom",    0x180000, 0x800000, CRC(364aec7e) SHA1(3b0a20502824d3ca571f7915ade50232e5ac4bbe) )

	ROM_REGION( 0x1c00000, "sprcol", 0 )
	ROM_LOAD( "a0600_hc02.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601.rom",        0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hc02.rom",    0x1000000, 0x0800000, CRC(f68a56b7) SHA1(fb5a77476cb5a30533a528ddc454517cc6428043) )
	ROM_LOAD( "a0603.rom",        0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hc02.rom",    0x0000000, 0x0800000, CRC(07d91ea3) SHA1(8713409439eb4a2875baffbda711587f283a652b) )
	ROM_LOAD( "b0601_hc02.rom",    0x0800000, 0x0400000, CRC(a8fc03a0) SHA1(1e48d52b30463c142221683e1ffa7523fb70a10b) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "pgm_m01s_hc01.rom", 0x000000, 0x200000, CRC(692511a5) SHA1(b272fdd0aa3724ba8ff30d2568c3a6b63f1358b3) )
	ROM_LOAD( "m0600_hc02.rom",    0x400000, 0x400000, CRC(acadac0d) SHA1(f6b195b7cd33a197d377c750a1f9f5bee2900779) )
ROM_END

ROM_START( kovplushc03 ) //kovplus2020t
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hc03.119",    0x100000, 0x400000, CRC(170ac31e) SHA1(8f69be9fd9082f8edfde17345e921bb2062e587d) )
    ROM_IGNORE( 0x200000 )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hc03.rom",    0x180000, 0x800000, CRC(f21fd1bb) SHA1(d4523e37dcd1382a47d28c1cb07651fc9c3a1b74) )

	ROM_REGION( 0x2000000, "sprcol", 0 )
	ROM_LOAD( "a0600_hc03.rom",    0x0000000, 0x0800000, CRC(75a6632a) SHA1(73253b55c9590a44d67161de35ca85518c953954) )
	ROM_LOAD( "a0601_hc03.rom",    0x0800000, 0x0800000, CRC(d4e68dee) SHA1(01cecf774f3007549e874108fa2c3337882e7279) )
	ROM_LOAD( "a0602.rom",         0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603_hc03.rom",    0x1800000, 0x0800000, CRC(28c3b83e) SHA1(37f2df10db12bac16e0fdc59ac387d6ac1b30b87) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hc03.rom",    0x0000000, 0x0800000, CRC(2a419d21) SHA1(61821e1925e1ba892700d7fbf937bda6562655ca) )
	ROM_LOAD( "b0601_hc03.rom",    0x0800000, 0x0800000, CRC(630a3d64) SHA1(c5b49284c995170ed1fa89ccde94cd7971e7ac3a) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600_hc03.rom",    0x400000, 0x400000, CRC(51c242f1) SHA1(8dc7a34a0db098f862e390a6370499addae03bdf) )
ROM_END

ROM_START( kovplushc04 ) //kovplus12dw
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hc04.119",    0x100000, 0x400000, CRC(e2bb7762) SHA1(3bc62deb7bcdb53cb72dcfccfad99936f268704d) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hc02.rom",    0x180000, 0x800000, CRC(364aec7e) SHA1(3b0a20502824d3ca571f7915ade50232e5ac4bbe) )

	ROM_REGION( 0x1c00000, "sprcol", 0 )
	ROM_LOAD( "a0600_hc02.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601.rom",        0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hc02.rom",    0x1000000, 0x0800000, CRC(f68a56b7) SHA1(fb5a77476cb5a30533a528ddc454517cc6428043) )
	ROM_LOAD( "a0603.rom",        0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hc02.rom",    0x0000000, 0x0800000, CRC(07d91ea3) SHA1(8713409439eb4a2875baffbda711587f283a652b) )
	ROM_LOAD( "b0601_hc02.rom",    0x0800000, 0x0400000, CRC(a8fc03a0) SHA1(1e48d52b30463c142221683e1ffa7523fb70a10b) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "pgm_m01s_hc01.rom", 0x000000, 0x200000, CRC(692511a5) SHA1(b272fdd0aa3724ba8ff30d2568c3a6b63f1358b3) )
	ROM_LOAD( "m0600_hc02.rom",    0x400000, 0x400000, CRC(acadac0d) SHA1(f6b195b7cd33a197d377c750a1f9f5bee2900779) )
ROM_END

ROM_START( kovplushc05 ) //kovplus2012m
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hc05.119",    0x100000, 0x400000, CRC(145f39f9) SHA1(19cf0b1bccd6c7ec12040e5f9f533429d97675f3) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hc05.rom",    0x180000, 0x800000, CRC(597ee034) SHA1(40ca9fb7659b55f44161443e96414fedda714799) )

	ROM_REGION( 0x1c00000, "sprcol", 0 )
	ROM_LOAD( "a0600_hc02.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601.rom",         0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602.rom",         0x1000000, 0x0800000, CRC(e7a32959) SHA1(3d0ed684dc5b269238890836b2ce7ef46aa5265b) )
	ROM_LOAD( "a0603.rom",         0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hc02.rom",    0x0000000, 0x0800000, CRC(07d91ea3) SHA1(8713409439eb4a2875baffbda711587f283a652b) )
	ROM_LOAD( "b0601_hc05.rom",    0x0800000, 0x0400000, CRC(a0bb1c2f) SHA1(0542348c6e27779e0a98de16f04f9c18158f2b28) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "pgm_m01s_hc05.rom", 0x000000, 0x200000, CRC(bc785efc) SHA1(a07a519a9be66de9295236e49bc721e0d0b3b883) )
	ROM_LOAD( "m0600_hc01.rom",    0x400000, 0x400000, CRC(7a50501b) SHA1(1af6be69f3133ed56d4a132a1910cf562da83dac) )
ROM_END

ROM_START( kovplushc06 ) //kovplus12dw
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600_hc04.119",    0x100000, 0x400000, CRC(59b7a7b1) SHA1(48a40567185eeec870a368d682d8259347d3c224) )

	ROM_REGION( 0x4000, "prot", 0 )
	ROM_LOAD( "kov_igs027a.bin", 0x000000, 0x04000, NO_DUMP )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600_hc02.rom",    0x180000, 0x800000, CRC(364aec7e) SHA1(3b0a20502824d3ca571f7915ade50232e5ac4bbe) )

	ROM_REGION( 0x1c00000, "sprcol", 0 )
	ROM_LOAD( "a0600_hc02.rom",    0x0000000, 0x0800000, CRC(5bd7ea9f) SHA1(0eb33bd0e23441394ae7c6fa28aafe11adf0b22f) )
	ROM_LOAD( "a0601.rom",        0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602_hc02.rom",    0x1000000, 0x0800000, CRC(f68a56b7) SHA1(fb5a77476cb5a30533a528ddc454517cc6428043) )
	ROM_LOAD( "a0603.rom",        0x1800000, 0x0400000, CRC(ec31abda) SHA1(ee526655369bae63b0ef0730e9768b765c9950fc) )

	ROM_REGION( 0x1000000, "sprmask", 0 )
	ROM_LOAD( "b0600_hc02.rom",    0x0000000, 0x0800000, CRC(07d91ea3) SHA1(8713409439eb4a2875baffbda711587f283a652b) )
	ROM_LOAD( "b0601_hc02.rom",    0x0800000, 0x0400000, CRC(a8fc03a0) SHA1(1e48d52b30463c142221683e1ffa7523fb70a10b) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "pgm_m01s_hc01.rom", 0x000000, 0x200000, CRC(692511a5) SHA1(b272fdd0aa3724ba8ff30d2568c3a6b63f1358b3) )
	ROM_LOAD( "m0600_hc02.rom",    0x400000, 0x400000, CRC(acadac0d) SHA1(f6b195b7cd33a197d377c750a1f9f5bee2900779) )
ROM_END

ROM_START( kovshphc01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	PGM_68K_BIOS
	ROM_LOAD16_WORD_SWAP( "p0600h_101hc01.rom",   0x100000, 0x400000, CRC(19d1ec84) SHA1(65e2d9dbb41776470245265d17bfa29a1437d8f5) )
    ROM_IGNORE( 0x200000 )

	ROM_REGION( 0x8000, "prot", 0 )
	ROM_LOAD( "kovsh_v100_china_hc01.asic", 0x000000, 0x08000, BAD_DUMP CRC(53f3ceac) SHA1(d1fadc76769b3d39dfeccdf326ad5d082e389559) )

	ROM_REGION( 0xa00000, "tiles", 0 )
	PGM_VIDEO_BIOS
	ROM_LOAD( "t0600hc01.rom",    0x180000, 0x800000, CRC(6e6fb378) SHA1(38998d3979fab5efd7945d06a640e1f66d527ed7) )

	ROM_REGION( 0x4000000, "sprcol", 0 )
	ROM_LOAD( "a0600.rom",    0x0000000, 0x0800000, CRC(d8167834) SHA1(fa55a99629d03b2ea253392352f70d2c8639a991) )
	ROM_LOAD( "a0601.rom",    0x0800000, 0x0800000, CRC(ff7a4373) SHA1(7def9fca7513ad5a117da230bebd2e3c78679041) )
	ROM_LOAD( "a0602hc01.rom",    0x1000000, 0x0800000, CRC(bb211e0f) SHA1(4d3246642faf5c009caa04c8f3a4327d76ba9241) )
	ROM_LOAD( "a0540hc01.rom",    0x1800000, 0x1000000, CRC(c58c518f) SHA1(b0a1b96eeb3d314d4be6378b78ad050998c3b244) )

	ROM_REGION( 0x2000000, "sprmask", 0 )
	ROM_LOAD( "b0600.rom",     0x0000000, 0x0800000, CRC(7d3cd059) SHA1(00cf994b63337e0e4ebe96453daf45f24192af1c) )
	ROM_LOAD( "b0540hc01.rom", 0x0800000, 0x1000000, CRC(3ac97a58) SHA1(a2d00df19a8b98553d3b191f6ec88fd401529343) )

	ROM_REGION( 0x800000, "ics", 0 )
	PGM_AUDIO_BIOS
	ROM_LOAD( "m0600hc01.rom",    0x400000, 0x400000, CRC(574353db) SHA1(f941243f21ba1004f4cb4cd6282c80424945915e) )
    ROM_IGNORE( 0x400000 )
ROM_END

/*    YEAR  NAME              PARENT            MACHINE            INPUT                              INIT           MONITOR COMPANY    FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2022, kovplushc01,      kovplus,     pgm_arm_type1_sim,      sango,     pgm_arm_type1_state,  init_kov,        ROT0,   "hack",       "Knights of Valour Plus (Warriors Classic 2022-06-30)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, kovplushc02,      kovplus,     pgm_arm_type1_sim,      sango,     pgm_arm_type1_state,  init_kov,        ROT0,   "hack",       "Knights of Valour Plus (Peerless Edition 2022-06-28)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2021, kovplushc03,      kovplus,     pgm_arm_type1_sim,      sango,     pgm_arm_type1_state,  init_kov,        ROT0,   "hack",       "Knights of Valour Plus (Devour the world 2021-08-22)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2022, kovplushc04,      kovplus,     pgm_arm_type1_sim,      sango,     pgm_arm_type1_state,  init_kov,        ROT0,   "hack",       "Knights of Valour Plus (Peerless Edition 2022-06-28)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2022, kovplushc05,      kovplus,     pgm_arm_type1_sim,      sango,     pgm_arm_type1_state,  init_kov,        ROT0,   "hack",       "Knights of Valour Plus (Nightmare Edition 2022-07-04)", MACHINE_NOT_WORKING |MACHINE_SUPPORTS_SAVE )
GAME( 2022, kovplushc06,      kovplus,     pgm_arm_type1_sim,      sango,     pgm_arm_type1_state,  init_kov,        ROT0,   "hack",       "Knights of Valour Plus (Peerless Edition 2022-07-28)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2022, kovshphc01,       kovshp,      pgm_arm_type1,          kovsh,     pgm_arm_type1_state,  init_kovshp,     ROT0,   "hack",       "Knights of Valour Super Heroes Plus (The Fourth Story 2020 2022-06-07)", MACHINE_SUPPORTS_SAVE )
