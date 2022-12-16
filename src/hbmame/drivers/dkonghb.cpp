// license:BSD-3-Clause
// copyright-holders:Gaston90
#include "../mame/drivers/dkong.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( dkonghc01 ) //dkduel
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "c_5et_g_hc01.bin",  0x0000, 0x1000, CRC(87a4912f) SHA1(bca9f1c489c193f4cd15a108dd4dd2d99aa89c35) )
	ROM_LOAD( "c_5ct_g_hc01.bin",  0x1000, 0x1000, CRC(1c547c2b) SHA1(d5373bae4e3a067821253ec6e0e5169a2bfd9dfe) )
	ROM_LOAD( "c_5bt_g_hc01.bin",  0x2000, 0x1000, CRC(fce41e06) SHA1(fdab4f37f914d56a28092592f9cbb3d2502c925e) )
	ROM_LOAD( "c_5at_g_hc01.bin",  0x3000, 0x1000, CRC(c1e0654c) SHA1(decf2a73730b117d977ca90039a9b93651883f8d) )
	ROM_LOAD( "diag.bin",     0x4000, 0x1000, NO_DUMP )

	ROM_REGION( 0x1800, "soundcpu", 0 )
	ROM_LOAD( "s_3i_b_hc01.bin",   0x0000, 0x0800, CRC(cc9aea3b) SHA1(e5b985efc1447ad04cfe347a7b761c9e5ff8ea5c) )
	ROM_RELOAD(               0x0800, 0x0800 )
	ROM_LOAD( "s_3j_b.bin",   0x1000, 0x0800, CRC(4743fe92) SHA1(6c82b57637c0212a580591397e6a5a1718f19fd2) )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "v_5h_b_hc01.bin",   0x0000, 0x0800, CRC(3cf6ef8b) SHA1(d4f1ac5dfa93b7073d9b441f05b24077c0d22924) )
	ROM_LOAD( "v_3pt_hc01.bin",    0x0800, 0x0800, CRC(3775dd7b) SHA1(0e73e1e64673140e8e5fd318cc679c64812608a7) )

	ROM_REGION( 0x2000, "gfx2", 0 )
	ROM_LOAD( "l_4m_b.bin",   0x0000, 0x0800, CRC(59f8054d) SHA1(793dba9bf5a5fe76328acdfb90815c243d2a65f1) )
	ROM_LOAD( "l_4n_b.bin",   0x0800, 0x0800, CRC(672e4714) SHA1(92e5d379f4838ac1fa44d448ce7d142dae42102f) )
	ROM_LOAD( "l_4r_b.bin",   0x1000, 0x0800, CRC(feaa59ee) SHA1(ecf95db5a20098804fc8bd59232c66e2e0ed3db4) )
	ROM_LOAD( "l_4s_b.bin",   0x1800, 0x0800, CRC(20f2ef7e) SHA1(3bc482a38bf579033f50082748ee95205b0f673d) )

	ROM_REGION( 0x0300, "proms", 0 )
	ROM_LOAD( "c-2k_hc01.bpr",     0x0000, 0x0100, CRC(02e1f91b) SHA1(fadb853a060db98ea13d67059fda91e7095b0050) )
	ROM_LOAD( "c-2j_hc01.bpr",     0x0100, 0x0100, CRC(4176057f) SHA1(ccb7d553f6aa82bff4d30da9b97d107684f329ca) )
	ROM_LOAD( "v-5e_hc01.bpr",     0x0200, 0x0100, CRC(94695888) SHA1(fc0167730b303c9743d24dba577b6a72ffc07c15) )
ROM_END

ROM_START( dkonghc02 ) //dkong40y
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "c_5et_g_hc02.bin",  0x0000, 0x1000, CRC(cf44c2dd) SHA1(26776fa00250fbffdc1cb2ef012f851cffd67b3d) )
	ROM_LOAD( "c_5ct_g_hc02.bin",  0x1000, 0x1000, CRC(34238a95) SHA1(a997989a33d5ad8dc77483781de12fd161e57f39) )
	ROM_LOAD( "c_5bt_g_hc02.bin",  0x2000, 0x1000, CRC(6c5614e5) SHA1(cf8a31c303eb18260cc328593f365ebd9d81fb5c) )
	ROM_LOAD( "c_5at_g_hc02.bin",  0x3000, 0x1000, CRC(0b92803c) SHA1(01bb401837ddeeb5ff36d98eebde9a5819ac19e8) )
	ROM_LOAD( "diag.bin",     0x4000, 0x1000, NO_DUMP )

	ROM_REGION( 0x1800, "soundcpu", 0 )
	ROM_LOAD( "s_3i_b_hc02.bin",   0x0000, 0x0800, CRC(44993c29) SHA1(7beeae49df5126bbf268dc66bb61e6a8b832fa31) )
	ROM_RELOAD(               0x0800, 0x0800 )
	ROM_LOAD( "s_3j_b.bin",   0x1000, 0x0800, CRC(4743fe92) SHA1(6c82b57637c0212a580591397e6a5a1718f19fd2) )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "v_5h_b_hc02.bin",   0x0000, 0x0800, CRC(ae4c3990) SHA1(20db41211bfdc6b79198fc8cd022465468430059) )
	ROM_LOAD( "v_3pt_hc02.bin",    0x0800, 0x0800, CRC(25cc07d4) SHA1(62374e89c79527cb78a70f83781299d4786bcec0) )

	ROM_REGION( 0x2000, "gfx2", 0 )
	ROM_LOAD( "l_4m_b_hc02.bin",   0x0000, 0x0800, CRC(410ab9a2) SHA1(c98f2053bc2f2140209ac2d8d0a7c1f489ec429c) )
	ROM_LOAD( "l_4n_b_hc02.bin",   0x0800, 0x0800, CRC(4f7e8fd4) SHA1(b031f512a40d6cdd430cc57f470efe53e55fbad7) )
	ROM_LOAD( "l_4r_b_hc02.bin",   0x1000, 0x0800, CRC(9eb470c0) SHA1(58644eed4c4f0b714f51147fbf77b9c2ee18ad2c) )
	ROM_LOAD( "l_4s_b_hc02.bin",   0x1800, 0x0800, CRC(73ef61cc) SHA1(7736e1451a36f1b9b20108c0d5f6ba861602d307) )

	ROM_REGION( 0x0300, "proms", 0 )
	ROM_LOAD( "c-2k.bpr",     0x0000, 0x0100, CRC(e273ede5) SHA1(b50ec9e1837c00c20fb2a4369ec7dd0358321127) )
	ROM_LOAD( "c-2j.bpr",     0x0100, 0x0100, CRC(d6412358) SHA1(f9c872da2fe8e800574ae3bf483fb3ccacc92eb3) )
	ROM_LOAD( "v-5e.bpr",     0x0200, 0x0100, CRC(b869b8f5) SHA1(c2bdccbf2654b64ea55cd589fd21323a9178a660) )
ROM_END

ROM_START( dkonghc03 ) //dkrndmzr
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "c_5et_g_hc03.bin",  0x0000, 0x1000, CRC(281b9bb6) SHA1(b8602325070ace94928c0431c5ecb55e22c55c97) )
	ROM_LOAD( "c_5ct_g_hc03.bin",  0x1000, 0x1000, CRC(7fa1be23) SHA1(3c79c2a5df44b60ccf9c46ffdef65d1f02f738bc) )
	ROM_LOAD( "c_5bt_g_hc03.bin",  0x2000, 0x1000, CRC(50ad6d22) SHA1(b3187bc24245740e0c617d35b968fe5371492cf8) )
	ROM_LOAD( "c_5at_g_hc03.bin",  0x3000, 0x1000, CRC(4c9e7085) SHA1(6b8fefd44426848407e8a2f4f7010751dcf8cf39) )
	ROM_LOAD( "diag.bin",     0x4000, 0x1000, NO_DUMP )

	ROM_REGION( 0x1800, "soundcpu", 0 )
	ROM_LOAD( "s_3i_b.bin",   0x0000, 0x0800, CRC(45a4ed06) SHA1(144d24464c1f9f01894eb12f846952290e6e32ef) )
	ROM_RELOAD(               0x0800, 0x0800 )
	ROM_LOAD( "s_3j_b.bin",   0x1000, 0x0800, CRC(4743fe92) SHA1(6c82b57637c0212a580591397e6a5a1718f19fd2) )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "v_5h_b_hc03.bin",   0x0000, 0x0800, CRC(c77456de) SHA1(130ad5ea31a485169dcbdd719ec9753f4f125567) )
	ROM_LOAD( "v_3pt_hc03.bin",    0x0800, 0x0800, CRC(994f28be) SHA1(dd21af28b39b8b7963b083556abc5565213621ea) )

	ROM_REGION( 0x2000, "gfx2", 0 )
	ROM_LOAD( "l_4m_b.bin",   0x0000, 0x0800, CRC(59f8054d) SHA1(793dba9bf5a5fe76328acdfb90815c243d2a65f1) )
	ROM_LOAD( "l_4n_b.bin",   0x0800, 0x0800, CRC(672e4714) SHA1(92e5d379f4838ac1fa44d448ce7d142dae42102f) )
	ROM_LOAD( "l_4r_b.bin",   0x1000, 0x0800, CRC(feaa59ee) SHA1(ecf95db5a20098804fc8bd59232c66e2e0ed3db4) )
	ROM_LOAD( "l_4s_b.bin",   0x1800, 0x0800, CRC(20f2ef7e) SHA1(3bc482a38bf579033f50082748ee95205b0f673d) )

	ROM_REGION( 0x0300, "proms", 0 )
	ROM_LOAD( "c-2k.bpr",     0x0000, 0x0100, CRC(e273ede5) SHA1(b50ec9e1837c00c20fb2a4369ec7dd0358321127) )
	ROM_LOAD( "c-2j.bpr",     0x0100, 0x0100, CRC(d6412358) SHA1(f9c872da2fe8e800574ae3bf483fb3ccacc92eb3) )
	ROM_LOAD( "v-5e.bpr",     0x0200, 0x0100, CRC(b869b8f5) SHA1(c2bdccbf2654b64ea55cd589fd21323a9178a660) )
ROM_END

ROM_START( dkonghc04 ) //dkwizardry
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "c_5et_g_hc04.bin",  0x0000, 0x1000, CRC(f42bb2e5) SHA1(2bd74d51d9ce43207f2ec879746ec44bdd13aef1) )
	ROM_LOAD( "c_5ct_g_hc04.bin",  0x1000, 0x1000, CRC(85cf6e4c) SHA1(4140865b1dabee98346f4217e9b7b355d177ebc7) )
	ROM_LOAD( "c_5bt_g_hc04.bin",  0x2000, 0x1000, CRC(6e888d7b) SHA1(58d164193d95a9a93238a06ab1338e14b448f3f7) )
	ROM_LOAD( "c_5at_g_hc04.bin",  0x3000, 0x1000, CRC(b8e1a56d) SHA1(5551faf1477492c570b5d58c8bc2359b83520186) )
	ROM_LOAD( "diag.bin",     0x4000, 0x1000, NO_DUMP )

	ROM_REGION( 0x1800, "soundcpu", 0 )
	ROM_LOAD( "s_3i_b.bin",   0x0000, 0x0800, CRC(45a4ed06) SHA1(144d24464c1f9f01894eb12f846952290e6e32ef) )
	ROM_RELOAD(               0x0800, 0x0800 )
	ROM_LOAD( "s_3j_b.bin",   0x1000, 0x0800, CRC(4743fe92) SHA1(6c82b57637c0212a580591397e6a5a1718f19fd2) )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "v_5h_b_hc04.bin",   0x0000, 0x0800, CRC(39736a8a) SHA1(8825f1473415fc588a189887f4aa302313bfcec8) )
	ROM_LOAD( "v_3pt_hc04.bin",    0x0800, 0x0800, CRC(c94468a9) SHA1(136b204735223c5e3f94340db5f6b7cfd0ad2666) )

	ROM_REGION( 0x2000, "gfx2", 0 )
	ROM_LOAD( "l_4m_b_hc04.bin",   0x0000, 0x0800, CRC(f98da4c5) SHA1(362c2083b0bad94174c3bd2e77b52dee18069d00) )
	ROM_LOAD( "l_4n_b_hc04.bin",   0x0800, 0x0800, CRC(cf3cdb75) SHA1(9ac98e0cfada360b9615af1c14c2d5e27129f328) )
	ROM_LOAD( "l_4r_b_hc04.bin",   0x1000, 0x0800, CRC(7e2d1ef4) SHA1(2f6d2d7afd4b595b2e24e31263433611e9761c86) )
	ROM_LOAD( "l_4s_b_hc04.bin",   0x1800, 0x0800, CRC(cc547d47) SHA1(087f9c5da33831d2a7a9f5f86d9da1d7f1cf15b6) )

	ROM_REGION( 0x0300, "proms", 0 )
	ROM_LOAD( "c-2k_hc04.bpr",     0x0000, 0x0100, CRC(193134e9) SHA1(6101bbdff23f0a1ccaba99cdbd966bcf780751bd) )
	ROM_LOAD( "c-2j_hc04.bpr",     0x0100, 0x0100, CRC(dcbba451) SHA1(31bf6bc17f790d4a61392ca1fd68361698ac9338) )
	ROM_LOAD( "v-5e_hc04.bpr",     0x0200, 0x0100, CRC(c24f2312) SHA1(61dfcec8ecaa7a38ed222f2d3c4d6695db6f33b1) )
ROM_END

ROM_START( dkonghc05 ) //dkongbp1
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "c_5et_g_hc05.bin",  0x0000, 0x1000, CRC(c80c0431) SHA1(446e897150d027f797edbe30d0502f5f5a652ba7) )
	ROM_LOAD( "c_5ct_g_hc05.bin",  0x1000, 0x1000, CRC(c742739c) SHA1(a143af813f7c23b6bab483ad2610e686ebc568da) )
	ROM_LOAD( "c_5bt_g_hc05.bin",  0x2000, 0x1000, CRC(a46859ec) SHA1(bbe8a32b7396f6347ce8b4a77b760277fb965551) )
	ROM_LOAD( "c_5at_g_hc05.bin",  0x3000, 0x1000, CRC(4742a48e) SHA1(ddef0c7e25cbeba37a387de1d72583a2861dbbf4) )
	ROM_LOAD( "diag.bin",     0x4000, 0x1000, NO_DUMP )

	ROM_REGION( 0x1800, "soundcpu", 0 )
	ROM_LOAD( "s_3i_b_hc05.bin",   0x0000, 0x0800, CRC(7590f5ee) SHA1(b08245ce86d2c2de1b0d000743b7e9fcdf2ee215) )
	ROM_RELOAD(               0x0800, 0x0800 )
	ROM_LOAD( "s_3j_b.bin",   0x1000, 0x0800, CRC(4743fe92) SHA1(6c82b57637c0212a580591397e6a5a1718f19fd2) )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "v_5h_b_hc05.bin",   0x0000, 0x0800, CRC(caf8820b) SHA1(b3e5768bd19c16510d05cd9d5d7ad72e05d08a8c) )
	ROM_LOAD( "v_3pt_hc05.bin",    0x0800, 0x0800, CRC(b0cd1e84) SHA1(16f8404114e3f62e0789819f6a65f34189b595bc) )

	ROM_REGION( 0x2000, "gfx2", 0 )
	ROM_LOAD( "l_4m_b_hc05.bin",   0x0000, 0x0800, CRC(1b46aae1) SHA1(f08c57f2c85df81180444cab76acb4f367d71619) )
	ROM_LOAD( "l_4n_b_hc05.bin",   0x0800, 0x0800, CRC(fbaaa6f0) SHA1(e61e92418270fb81d9fd33da0a92970d458f69e4) )
	ROM_LOAD( "l_4r_b_hc05.bin",   0x1000, 0x0800, CRC(919362a0) SHA1(5df953cded45ad55ba2bbd5f6d5c7e4577dcaa5f) )
	ROM_LOAD( "l_4s_b_hc05.bin",   0x1800, 0x0800, CRC(d57098ca) SHA1(b746b0e137844e0e1cb715df065bbf7a3246f2e9) )

	ROM_REGION( 0x0300, "proms", 0 )
	ROM_LOAD( "c-2k_hc05.bpr",     0x0000, 0x0100, CRC(4826ce71) SHA1(5fe7d63ce7adece81ab8930196434410fbe4e241) )
	ROM_LOAD( "c-2j_hc05.bpr",     0x0100, 0x0100, CRC(4a7a511b) SHA1(c0d3ee62e5f6e22d24603ab24403b206d043956f) )
	ROM_LOAD( "v-5e.bpr",     0x0200, 0x0100, CRC(b869b8f5) SHA1(c2bdccbf2654b64ea55cd589fd21323a9178a660) ) /* character color codes on a per-column basis */
ROM_END

/*    YEAR  NAME           PARENT        MACHINE    INPUT                     INIT       MONITOR    COMPANY       FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2021, dkonghc01,     dkong,        dkong2b,   dkong,    dkong_state, empty_init,    ROT270,   "hack",       "Donkey Kong (Duel v1.02 2021-11-10)",    MACHINE_SUPPORTS_SAVE )
GAME( 2021, dkonghc02,     dkong,        dkong2b,   dkong,    dkong_state, empty_init,    ROT270,   "hack",       "Donkey Kong (40th Anniversary Edition 2021-03-02)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dkonghc03,     dkong,        dkong2b,   dkong,    dkong_state, empty_init,    ROT270,   "hack",       "Donkey Kong (RNDMZR v1.00 2022-05-22)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dkonghc04,     dkong,        dkong2b,   dkong,    dkong_state, empty_init,    ROT270,   "hack",       "Donkey Kong (Wizardry v1.03 2022-05-22)", MACHINE_SUPPORTS_SAVE )
GAME( 2021, dkonghc05,     dkong,        dkong2b,   dkong,    dkong_state, empty_init,    ROT270,   "hack",       "Donkey Kong (Carnival 1.07 2021-06-14)", MACHINE_SUPPORTS_SAVE )
