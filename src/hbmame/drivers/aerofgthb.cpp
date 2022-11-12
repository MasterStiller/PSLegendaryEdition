// license:BSD-3-Clause
// copyright-holders:Gaston90
#include "../mame/drivers/aerofgt.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( aerofgthc01 ) //aerofgtddj
	ROM_REGION( 0x80000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "1_hc01.u4",  0x00000, 0x80000, CRC(d5a8155c) SHA1(bc7cc172da9dfb554dbf8c35e069c83570310f81) )

	ROM_REGION( 0x20000, "audiocpu", 0 )
	ROM_LOAD( "2.153",        0x00000, 0x20000, CRC(a1ef64ec) SHA1(fa3e434738bf4e742ad68882c1e914100ce0f761) )

	ROM_REGION( 0x100000, "gfx1", 0 )
	ROM_LOAD( "538a54.124",   0x000000, 0x80000, CRC(4d2c4df2) SHA1(f51c2b3135f0a921ac1a79e63d6878c03cb6254b) )
	ROM_LOAD( "1538a54.124",  0x080000, 0x80000, CRC(286d109e) SHA1(3a5f3d2d89cf58f6ef15e4bd3f570b84e8e695b2) )

	ROM_REGION( 0x400000, "gfx2", 0 )
	ROM_LOAD( "538a53.u9",    0x000000, 0x100000, CRC(630d8e0b) SHA1(5a0c252ccd53c5199a695909d25ecb4e53dc15b9) )
	ROM_LOAD( "534g8f.u18",   0x200000, 0x080000, CRC(76ce0926) SHA1(5ef4cec215d4dd600d8fcd1bd9a4c09081d59e33) )

	ROM_REGION( 0x40000, "ymsnd.deltat", 0 )
	ROM_LOAD( "it-19-01",     0x00000, 0x40000, CRC(6d42723d) SHA1(57c59234e9925430a4c687733682efed06d7eed1) )

	ROM_REGION( 0x100000, "ymsnd", 0 )
	ROM_LOAD( "it-19-06",     0x000000, 0x100000, CRC(cdbbdb1d) SHA1(067c816545f246ff1fd4c821d70df1e7eb47938c) )
ROM_END

/*    YEAR     NAME         PARENT          MACHINE      INPUT                       INIT          MONITOR   COMPANY      FULLNAME FLAGS */
// Hack/Homebrow
GAME( 1992, aerofgthc01,    aerofgt,        aerofgt,    aerofgt,   aerofgt_state, empty_init,      ROT270,   "hack",      "Aero Fighters (The Strongest Firepower)", MACHINE_SUPPORTS_SAVE | MACHINE_NO_COCKTAIL )
