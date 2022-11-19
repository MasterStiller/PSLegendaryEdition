// license:BSD-3-Clause
// copyright-holders:Gaston90
#include "../mame/drivers/raiden2.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( zeroteamhc01 ) //zeroteamab
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD32_BYTE("seibu__1.u024_hc01.5k",   0x000000, 0x40000, CRC(854149c1) SHA1(ce12d5369df244f2c8c9b2560ddc82cb51dcfe03) )
	ROM_LOAD32_BYTE("seibu__3.u023_hc01.6k",   0x000002, 0x40000, CRC(0a8f8d95) SHA1(b9261f453824ec7f2af926e045a620a8db2d5643) )
	ROM_LOAD32_BYTE("seibu__2.u025_hc01.6l",   0x000001, 0x40000, CRC(d29c2966) SHA1(4758cdac0b630f4e53a708fae1ac850433b6cfad) )
	ROM_LOAD32_BYTE("seibu__4.u026_hc01.5l",   0x000003, 0x40000, CRC(eb3c3985) SHA1(faf98732ad5762818f964ce1a3c62bba5beb462b) )

	ROM_REGION( 0x40000, "user2", 0 )
	ROM_LOAD( "copx-d2.u0313.6n",   0x00000, 0x40000, CRC(a6732ff9) SHA1(c4856ec77869d9098da24b1bb3d7d58bb74b4cda) )

	ROM_REGION( 0x20000, "audiocpu", ROMREGION_ERASEFF )
	ROM_LOAD( "seibu__5.u1110.5b",  0x000000, 0x08000, CRC(7ec1fbc3) SHA1(48299d6530f641b18764cc49e283c347d0918a47) )
	ROM_CONTINUE(0x10000,0x8000)
	ROM_COPY( "audiocpu", 0x000000, 0x018000, 0x08000 )

	ROM_REGION( 0x020000, "gfx1", 0 )
	ROM_LOAD16_BYTE( "seibu__7.u072.5s",    0x000000,   0x010000,   CRC(9f6aa0f0) SHA1(1caad7092c07723d12a07aa363ae2aa69cb6be0d) )
	ROM_LOAD16_BYTE( "seibu__8.u077.5r",    0x000001,   0x010000,   CRC(68f7dddc) SHA1(6938fa974c6ef028751982fdabd6a3820b0d30a8) )

	ROM_REGION( 0x400000, "gfx2", 0 )
	ROM_LOAD( "musha_back-1.u075.4s",   0x000000, 0x100000, CRC(8b7f9219) SHA1(3412b6f8a4fe245e521ddcf185a53f2f4520eb57) )
	ROM_LOAD( "musha_back-2.u0714.2s",   0x100000, 0x080000, CRC(ce61c952) SHA1(52a843c8ba428b121fab933dd3b313b2894d80ac) )

	ROM_REGION32_LE( 0x800000, "gfx3", ROMREGION_ERASEFF )
	ROM_LOAD32_WORD( "musha_obj-1.u0811.6f",  0x000000, 0x200000, CRC(45be8029) SHA1(adc164f9dede9a86b96a4d709e9cba7d2ad0e564) )
	ROM_LOAD32_WORD( "musha_obj-2.u082.5f",  0x000002, 0x200000, CRC(cb61c19d) SHA1(151a2ce9c32f3321a974819e9b165dddc31c8153) )

	ROM_REGION( 0x100000, "oki", 0 )
	ROM_LOAD( "seibu__6.u105.4a", 0x00000, 0x40000,  CRC(48be32b1) SHA1(969d2191a3c46871ee8bf93088b3cecce3eccf0c) )

	ROM_REGION( 0x10000, "pals", 0 )
	ROM_LOAD( "v3c001.pal.u0310.jed", 0x0000, 0x288, NO_DUMP)
	ROM_LOAD( "v3c002.tibpal16l8-25.u0322.jed", 0x0000, 0x288, NO_DUMP)
	ROM_LOAD( "v3c003.ami18cv8p-15.u0619.jed", 0x0000, 0x288, NO_DUMP)
	ROM_LOAD( "v3c004x.ami18cv8pc-25.u0310.jed", 0x0000, 0x288, NO_DUMP)
ROM_END

/*    YEAR  NAME              PARENT            MACHINE             INPUT                       INIT           MONITOR COMPANY       FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2022, zeroteamhc01,     zeroteam,         zeroteam,         zeroteam, raiden2_state, init_zeroteam,      ROT0,  "hack",        "Zero Team USA (Special Attack Team Question Mark Version 2022-05-11)", MACHINE_SUPPORTS_SAVE )
