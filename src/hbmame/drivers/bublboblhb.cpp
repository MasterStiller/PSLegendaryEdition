// Proyecto Shadow Legendary Edition
// copyright-holders:Gaston90 (2016 - 2023)
#include "../mame/drivers/bublbobl.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( bublboblhc01 ) //bublboblu
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "a78-06_hc01.51",    0x00000, 0x08000, CRC(a6345edd) SHA1(144f33002ee40acdbfa6a49119092a319048bb00) )
	ROM_LOAD( "a78-05_hc01.52",    0x10000, 0x10000, CRC(b31d2edc) SHA1(b7d317c0b5b86c0bf39b18cfe584bca9d22d4eba) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08_hc01.37",    0x0000, 0x08000, CRC(d544be2e) SHA1(1472db52dcd9e17a866ea2766cfea500d8f712ab) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x10000, "mcu", 0 )
	ROM_LOAD( "a78-01.17",    0xf000, 0x1000, CRC(b1bfb53d) SHA1(31b8f31acd3aa394acd80db362774749842e1285) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE   INPUT                        INIT   MONITOR   COMPANY     FULLNAME FLAGS */
// Hack/Homebrow
GAME( 1986, bublboblhc01,  bublbobl, bublbobl, bublbobl, bublbobl_state, init_common, ROT0,   "hack",    "Bubble Bobble (Ultra Version)", MACHINE_SUPPORTS_SAVE )
