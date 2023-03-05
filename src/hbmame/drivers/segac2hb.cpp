// Proyecto Shadow Legendary Edition
// copyright-holders:Gaston90 (2016 - 2023)
#include "../mame/drivers/segac2.cpp"

ROM_START( sonicfgthc01 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "epr-16001_hc01.ic32", 0x000000, 0x040000, CRC(e05b7388) SHA1(38fd175c265986a14d1365e3a403e12fbc6c73c3) )
	ROM_LOAD16_BYTE( "epr-16000_hc01.ic31", 0x000001, 0x040000, CRC(7c2ec4eb) SHA1(f74f21f5dcfbf6ee902c2a44fed908a628d60363) )
	ROM_LOAD16_BYTE( "epr-16003.ic34", 0x100000, 0x040000, CRC(8933e91c) SHA1(5dc7451874f97e0e5d0c666800c26907b9abf5f5) )
	ROM_LOAD16_BYTE( "epr-16002.ic33", 0x100001, 0x040000, CRC(0ae979cd) SHA1(a4d4f096e976d4993123de0c2505382f878ea42a) )

	ROM_REGION( 0x040000, "upd", 0 )
	ROM_LOAD( "epr-16004_hc01.ic4", 0x000000, 0x040000, CRC(4211745d) SHA1(710f7dab436bf0551b95786efc5ea4303c0fd5ec) )
ROM_END

/*    YEAR  NAME           PARENT       MACHINE    INPUT                              INIT     MONITOR   COMPANY       FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2023, sonicfgthc01,  sonicfgt,    segac2, systemc_generic, segac2_state,    init_bloxeedc, ROT0,   "hack",       "Sega Sonic Cosmo Fighter 2023-02-14", 0 )