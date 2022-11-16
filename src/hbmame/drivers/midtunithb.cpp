// license:BSD-3-Clause
// copyright-holders:Gaston90
#include "../mame/drivers/midtunit.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( nbajamhc01 )
	ROM_REGION( 0x50000, "adpcm:cpu", 0 )
	ROM_LOAD(  "l2_nba_jam_u3_sound_rom.u3", 0x010000, 0x20000, CRC(3a3ea480) SHA1(d12a45cba5c35f046b176661d7877fa4fd0e6c13) )
	ROM_RELOAD(             0x030000, 0x20000 )

	ROM_REGION( 0x100000, "adpcm:oki", 0 )
	ROM_LOAD( "nbau12_hc01.u12", 0x000000, 0x80000, CRC(cd5d4532) SHA1(63ff4b5b22e02ee90cdcb745acc6bf9dbc1c3140) )
	ROM_LOAD( "nbau13_hc01.u13", 0x080000, 0x80000, CRC(e92fb0d3) SHA1(bac12a69f74051cb97326c05eb77d88acdf81a63) )

	ROM_REGION16_LE( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "l3_nba_jam_game_rom_uj12_hc01.uj12", 0x00000, 0x80000, CRC(9b3fc483) SHA1(4e7b6b85d9972063ebdb08ad2c860e082b6e886b) )
	ROM_LOAD16_BYTE( "l3_nba_jam_game_rom_ug12_hc01.ug12", 0x00001, 0x80000, CRC(18e75204) SHA1(e33eaa969dbc7ac19641238fc62d2af4d75bddef) )

	ROM_REGION( 0xc00000, "gfxrom", 0 )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_ug14.ug14", 0x000000, 0x80000, CRC(04bb9f64) SHA1(9e1a8c37e14cb6fe67f4aa3caa9022f356f1ca64) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_uj14.uj14", 0x000001, 0x80000, CRC(b34b7af3) SHA1(0abb74d2f414bc9da0380a81beb134f3a87c1a0a) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_ug19.ug19", 0x000002, 0x80000, CRC(a8f22fbb) SHA1(514208a9d6d0c8c2d7847cc02d4387eac90be659) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_uj19.uj19", 0x000003, 0x80000, CRC(8130a8a2) SHA1(f23f124024285d07d8cf822817b62e42c38b82db) )

	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_ug16_hc01.ug16", 0x200000, 0x80000, CRC(b9a07a6f) SHA1(0b9410ae9d761928b828449f45302f0951a6a8af) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_uj16_hc01.uj16", 0x200001, 0x80000, CRC(ffa7db04) SHA1(984a1011f378d7e77acf43f285f7c72f035fc7ee) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_ug20_hc01.ug20", 0x200002, 0x80000, CRC(67c8646b) SHA1(a0584e79cdd5c83cd62bda09470f67082a670fe1) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_uj20_hc01.uj20", 0x200003, 0x80000, CRC(71d028f8) SHA1(6c9d3cb6b937a53af8be0c7c5e209fb8740d6d9a) )

	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_ug17_hc01.ug17", 0x400000, 0x80000, CRC(34c6bdb8) SHA1(fe613fc3256eafc368ba566dd989c05293df1829) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_uj17_hc01.uj17", 0x400001, 0x80000, CRC(3af5b32e) SHA1(397d2524a5749f8e8419280cc3c48ec3081834b5) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_ug22_hc01.ug22", 0x400002, 0x80000, CRC(d41234d2) SHA1(9dab65c7843758572634c4805227fee1850b0349) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_uj22_hc01.uj22", 0x400003, 0x80000, CRC(42196c84) SHA1(7f30204a4764b4afd38cf82f8be909c9ee5a0a0b) )

	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_ug18_hc01.ug18", 0x600000, 0x80000, CRC(fe18a6ef) SHA1(58b8bbf257b3de5d7536421dda302e2d93f51999) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_uj18_hc01.uj18", 0x600001, 0x80000, CRC(9a6d36de) SHA1(1bb24ff5fdbdc1f7265da0ba43e3d96ab589548f) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_ug23_hc01.ug23", 0x600002, 0x80000, CRC(8d1af1a6) SHA1(4de21240ec0ffce9346e75b9719d9ae71bfbdb8e) )
	ROM_LOAD32_BYTE( "l1_nba_jam_game_rom_uj23_hc01.uj23", 0x600003, 0x80000, CRC(b5bf66f9) SHA1(de12e47e44f9cf7c611d674fe6c9b3466fde2081) )
ROM_END

/*    YEAR  NAME              PARENT            MACHINE            INPUT                       INIT       MONITOR COMPANY       FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2022, nbajamhc01,       nbajam,           tunit_adpcm,      nbajam,   midtunit_state, init_nbajam,   ROT0, "hack",       "NBA Jam (Rotation v1.1 2022-07-11)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
