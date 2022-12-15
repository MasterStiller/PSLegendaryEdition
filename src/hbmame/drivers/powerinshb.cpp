// license:BSD-3-Clause
// copyright-holders:Gaston90 (2016-2022)

#include "../mame/drivers/powerins.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( powerinshc01 )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-3a_hc01.u108", 0x00000, 0x454F48, CRC(1aa0b604) SHA1(67bc37584e7d697b28537eb43622fccf83dd87e7) )
	ROM_LOAD16_WORD_SWAP( "93095-4.u109",  0x80000, 0x80000, CRC(d3d7a782) SHA1(7846de0ebb09bd9b2534cd451ff9aa5175e60647) )

	ROM_REGION( 0x20000, "soundcpu", 0 )
	ROM_LOAD( "93095-2.u90",  0x00000, 0x20000, CRC(4b123cc6) SHA1(ed61d3a2ab20c86b91fd7bafa717be3ce26159be) )

	ROM_REGION( 0x280000, "gfx1", 0 )
	ROM_LOAD( "93095-5.u16",  0x000000, 0x100000, CRC(b1371808) SHA1(15fca313314ff2e0caff35841a2fdda97f6235a8) )
	ROM_LOAD( "93095-6_hc01.u17",  0x100000, 0x100000, CRC(4a7a6bd8) SHA1(953bba9606795ec32c9c0e4e0fd4e88da9708cf8) )
	ROM_LOAD( "93095-7.u18",  0x200000, 0x080000, CRC(2dd76149) SHA1(975e4d371fdfbbd9a568da4d4c91ffd3f0ae636e) )

	ROM_REGION( 0x100000, "gfx2", 0 )
	ROM_LOAD( "93095-1_hc01.u15",  0x000000, 0x020000, CRC(7e73e1d8) SHA1(ff8d8ecbb01122291404f93a60d6e0c3fc56c3c7) )

	ROM_REGION( 0x800000, "gfx3", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-12.u116", 0x000000, 0x100000, CRC(35f3c2a3) SHA1(70efebfe248401ba3d766dc0e4bcc2846cd0d9a0) )
	ROM_LOAD16_WORD_SWAP( "93095-13.u117", 0x100000, 0x100000, CRC(1ebd45da) SHA1(99b0ac734890673064b2a4b4b57ff2694e338dea) )
	ROM_LOAD16_WORD_SWAP( "93095-14.u118", 0x200000, 0x100000, CRC(760d871b) SHA1(4887122ad0518c90f08c11a7a6b694f3fd218498) )
	ROM_LOAD16_WORD_SWAP( "93095-15.u119", 0x300000, 0x100000, CRC(d011be88) SHA1(837409a2584abdf22e022b0f06181a600a974cbe) )
	ROM_LOAD16_WORD_SWAP( "93095-16.u120", 0x400000, 0x100000, CRC(a9c16c9c) SHA1(a34e81324c875c2a57f778d1dbdda8da81850a29) )
	ROM_LOAD16_WORD_SWAP( "93095-17.u121", 0x500000, 0x100000, CRC(51b57288) SHA1(821473d51565bc0a8b9a979723ce1307b97e517e) )
	ROM_LOAD16_WORD_SWAP( "93095-18.u122", 0x600000, 0x100000, CRC(b135e3f2) SHA1(339fb4007ca0f379b7554a1c4f711f494a371fb2) )
	ROM_LOAD16_WORD_SWAP( "93095-19.u123", 0x700000, 0x100000, CRC(67695537) SHA1(4c78ce3e36f27d2a6a9e50e8bf896335d4d0958a) )

	ROM_REGION( 0x240000, "oki1", 0 )
	ROM_LOAD( "93095-10.u48", 0x040000, 0x100000, CRC(329ac6c5) SHA1(e809b94e2623141f5a48995cfa97fe1ead7ab40b) )
	ROM_LOAD( "93095-11.u49", 0x140000, 0x100000, CRC(75d6097c) SHA1(3c89a7c9b12087e2d969b822419d3e5f98f5cb1d) )

	ROM_REGION( 0x240000, "oki2", 0 )
	ROM_LOAD( "93095-8.u46",  0x040000, 0x100000, CRC(f019bedb) SHA1(4b6e10f85671c75b666e547887d403d6e607cec8) )
	ROM_LOAD( "93095-9.u47",  0x140000, 0x100000, CRC(adc83765) SHA1(9e760443f9de21c1bb7e33eaa1541023fcdc60ab) )

	ROM_REGION( 0x0220, "proms", 0 )
	ROM_LOAD( "22.u81",       0x000000, 0x0020, CRC(67d5ec4b) SHA1(87d32948a0c88277dcdd0eaa035bde40fc7db5fe) )
	ROM_LOAD( "21.u71",       0x000020, 0x0100, CRC(182cd81f) SHA1(3a76bea81b34ea7ccf56044206721058aa5b03e6) )
	ROM_LOAD( "20.u54",       0x000100, 0x0100, CRC(38bd0e2f) SHA1(20d311869642cd96bb831fdf4a458e0d872f03eb) )
ROM_END

ROM_START( powerinshc02 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-3a_hc02.u108", 0x00000, 0x80000, CRC(432453c5) SHA1(38111f755737ea852ca3dd364103383697420158) )
	ROM_LOAD16_WORD_SWAP( "93095-4.u109",  0x80000, 0x80000, CRC(d3d7a782) SHA1(7846de0ebb09bd9b2534cd451ff9aa5175e60647) )

	ROM_REGION( 0x20000, "soundcpu", 0 )
	ROM_LOAD( "93095-2.u90",  0x00000, 0x20000, CRC(4b123cc6) SHA1(ed61d3a2ab20c86b91fd7bafa717be3ce26159be) )

	ROM_REGION( 0x280000, "gfx1", 0 )
	ROM_LOAD( "93095-5.u16",  0x000000, 0x100000, CRC(b1371808) SHA1(15fca313314ff2e0caff35841a2fdda97f6235a8) )
	ROM_LOAD( "93095-6.u17",  0x100000, 0x100000, CRC(29c85d80) SHA1(abd54f9c8bade21ea918a426627199da04193165) )
	ROM_LOAD( "93095-7.u18",  0x200000, 0x080000, CRC(2dd76149) SHA1(975e4d371fdfbbd9a568da4d4c91ffd3f0ae636e) )

	ROM_REGION( 0x100000, "gfx2", 0 )
	ROM_LOAD( "93095-1.u15",  0x000000, 0x020000, CRC(6a579ee0) SHA1(438e87b930e068e0cf7352e614a14049ebde6b8a) )

	ROM_REGION( 0x800000, "gfx3", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-12.u116", 0x000000, 0x100000, CRC(35f3c2a3) SHA1(70efebfe248401ba3d766dc0e4bcc2846cd0d9a0) )
	ROM_LOAD16_WORD_SWAP( "93095-13.u117", 0x100000, 0x100000, CRC(1ebd45da) SHA1(99b0ac734890673064b2a4b4b57ff2694e338dea) )
	ROM_LOAD16_WORD_SWAP( "93095-14.u118", 0x200000, 0x100000, CRC(760d871b) SHA1(4887122ad0518c90f08c11a7a6b694f3fd218498) )
	ROM_LOAD16_WORD_SWAP( "93095-15.u119", 0x300000, 0x100000, CRC(d011be88) SHA1(837409a2584abdf22e022b0f06181a600a974cbe) )
	ROM_LOAD16_WORD_SWAP( "93095-16.u120", 0x400000, 0x100000, CRC(a9c16c9c) SHA1(a34e81324c875c2a57f778d1dbdda8da81850a29) )
	ROM_LOAD16_WORD_SWAP( "93095-17.u121", 0x500000, 0x100000, CRC(51b57288) SHA1(821473d51565bc0a8b9a979723ce1307b97e517e) )
	ROM_LOAD16_WORD_SWAP( "93095-18.u122", 0x600000, 0x100000, CRC(b135e3f2) SHA1(339fb4007ca0f379b7554a1c4f711f494a371fb2) )
	ROM_LOAD16_WORD_SWAP( "93095-19.u123", 0x700000, 0x100000, CRC(67695537) SHA1(4c78ce3e36f27d2a6a9e50e8bf896335d4d0958a) )

	ROM_REGION( 0x240000, "oki1", 0 )
	ROM_LOAD( "93095-10.u48", 0x040000, 0x100000, CRC(329ac6c5) SHA1(e809b94e2623141f5a48995cfa97fe1ead7ab40b) )
	ROM_LOAD( "93095-11.u49", 0x140000, 0x100000, CRC(75d6097c) SHA1(3c89a7c9b12087e2d969b822419d3e5f98f5cb1d) )

	ROM_REGION( 0x240000, "oki2", 0 )
	ROM_LOAD( "93095-8.u46",  0x040000, 0x100000, CRC(f019bedb) SHA1(4b6e10f85671c75b666e547887d403d6e607cec8) )
	ROM_LOAD( "93095-9.u47",  0x140000, 0x100000, CRC(adc83765) SHA1(9e760443f9de21c1bb7e33eaa1541023fcdc60ab) )

	ROM_REGION( 0x0220, "proms", 0 )
	ROM_LOAD( "22.u81",       0x000000, 0x0020, CRC(67d5ec4b) SHA1(87d32948a0c88277dcdd0eaa035bde40fc7db5fe) )
	ROM_LOAD( "21.u71",       0x000020, 0x0100, CRC(182cd81f) SHA1(3a76bea81b34ea7ccf56044206721058aa5b03e6) )
	ROM_LOAD( "20.u54",       0x000100, 0x0100, CRC(38bd0e2f) SHA1(20d311869642cd96bb831fdf4a458e0d872f03eb) )
ROM_END

ROM_START( powerinshc03 ) //powerinsl
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-3a_hc03.u108", 0x00000, 0x80000, CRC(1686cae2) SHA1(6eb4b42d2f0f9a5ab2a98998b0416f5d88f98cef) )
	ROM_LOAD16_WORD_SWAP( "93095-4.u109",  0x80000, 0x80000, CRC(d3d7a782) SHA1(7846de0ebb09bd9b2534cd451ff9aa5175e60647) )

	ROM_REGION( 0x20000, "soundcpu", 0 )
	ROM_LOAD( "93095-2.u90",  0x00000, 0x20000, CRC(4b123cc6) SHA1(ed61d3a2ab20c86b91fd7bafa717be3ce26159be) )

	ROM_REGION( 0x280000, "gfx1", 0 )
	ROM_LOAD( "93095-5.u16",  0x000000, 0x100000, CRC(b1371808) SHA1(15fca313314ff2e0caff35841a2fdda97f6235a8) )
	ROM_LOAD( "93095-6.u17",  0x100000, 0x100000, CRC(29c85d80) SHA1(abd54f9c8bade21ea918a426627199da04193165) )
	ROM_LOAD( "93095-7.u18",  0x200000, 0x080000, CRC(2dd76149) SHA1(975e4d371fdfbbd9a568da4d4c91ffd3f0ae636e) )

	ROM_REGION( 0x100000, "gfx2", 0 )
	ROM_LOAD( "93095-1.u15",  0x000000, 0x020000, CRC(6a579ee0) SHA1(438e87b930e068e0cf7352e614a14049ebde6b8a) )

	ROM_REGION( 0x800000, "gfx3", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-12.u116", 0x000000, 0x100000, CRC(35f3c2a3) SHA1(70efebfe248401ba3d766dc0e4bcc2846cd0d9a0) )
	ROM_LOAD16_WORD_SWAP( "93095-13.u117", 0x100000, 0x100000, CRC(1ebd45da) SHA1(99b0ac734890673064b2a4b4b57ff2694e338dea) )
	ROM_LOAD16_WORD_SWAP( "93095-14.u118", 0x200000, 0x100000, CRC(760d871b) SHA1(4887122ad0518c90f08c11a7a6b694f3fd218498) )
	ROM_LOAD16_WORD_SWAP( "93095-15.u119", 0x300000, 0x100000, CRC(d011be88) SHA1(837409a2584abdf22e022b0f06181a600a974cbe) )
	ROM_LOAD16_WORD_SWAP( "93095-16.u120", 0x400000, 0x100000, CRC(a9c16c9c) SHA1(a34e81324c875c2a57f778d1dbdda8da81850a29) )
	ROM_LOAD16_WORD_SWAP( "93095-17.u121", 0x500000, 0x100000, CRC(51b57288) SHA1(821473d51565bc0a8b9a979723ce1307b97e517e) )
	ROM_LOAD16_WORD_SWAP( "93095-18.u122", 0x600000, 0x100000, CRC(b135e3f2) SHA1(339fb4007ca0f379b7554a1c4f711f494a371fb2) )
	ROM_LOAD16_WORD_SWAP( "93095-19.u123", 0x700000, 0x100000, CRC(67695537) SHA1(4c78ce3e36f27d2a6a9e50e8bf896335d4d0958a) )

	ROM_REGION( 0x240000, "oki1", 0 )
	ROM_LOAD( "93095-10.u48", 0x040000, 0x100000, CRC(329ac6c5) SHA1(e809b94e2623141f5a48995cfa97fe1ead7ab40b) )
	ROM_LOAD( "93095-11.u49", 0x140000, 0x100000, CRC(75d6097c) SHA1(3c89a7c9b12087e2d969b822419d3e5f98f5cb1d) )

	ROM_REGION( 0x240000, "oki2", 0 )
	ROM_LOAD( "93095-8.u46",  0x040000, 0x100000, CRC(f019bedb) SHA1(4b6e10f85671c75b666e547887d403d6e607cec8) )
	ROM_LOAD( "93095-9.u47",  0x140000, 0x100000, CRC(adc83765) SHA1(9e760443f9de21c1bb7e33eaa1541023fcdc60ab) )

	ROM_REGION( 0x0220, "proms", 0 )
	ROM_LOAD( "22.u81",       0x000000, 0x0020, CRC(67d5ec4b) SHA1(87d32948a0c88277dcdd0eaa035bde40fc7db5fe) )
	ROM_LOAD( "21.u71",       0x000020, 0x0100, CRC(182cd81f) SHA1(3a76bea81b34ea7ccf56044206721058aa5b03e6) )
	ROM_LOAD( "20.u54",       0x000100, 0x0100, CRC(38bd0e2f) SHA1(20d311869642cd96bb831fdf4a458e0d872f03eb) )
ROM_END

ROM_START( powerinshc04 ) //powerinsj
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-3a_hc04.u108", 0x00000, 0x80000, CRC(45d14b06) SHA1(57ac115d14962bff1dc81571da6e53760c468c4f) )
	ROM_LOAD16_WORD_SWAP( "93095-4_hc04.u109",  0x80000, 0x80000, CRC(0117de7e) SHA1(26cb4f25e61d5d1334d1e02af83284d6f0b50e32) )

	ROM_REGION( 0x20000, "soundcpu", 0 )
	ROM_LOAD( "93095-2.u90",  0x00000, 0x20000, CRC(4b123cc6) SHA1(ed61d3a2ab20c86b91fd7bafa717be3ce26159be) )

	ROM_REGION( 0x280000, "gfx1", 0 )
	ROM_LOAD( "93095-5.u16",  0x000000, 0x100000, CRC(b1371808) SHA1(15fca313314ff2e0caff35841a2fdda97f6235a8) )
	ROM_LOAD( "93095-6.u17",  0x100000, 0x100000, CRC(29c85d80) SHA1(abd54f9c8bade21ea918a426627199da04193165) )
	ROM_LOAD( "93095-7.u18",  0x200000, 0x080000, CRC(2dd76149) SHA1(975e4d371fdfbbd9a568da4d4c91ffd3f0ae636e) )

	ROM_REGION( 0x100000, "gfx2", 0 )
	ROM_LOAD( "93095-1.u15",  0x000000, 0x020000, CRC(6a579ee0) SHA1(438e87b930e068e0cf7352e614a14049ebde6b8a) )

	ROM_REGION( 0x800000, "gfx3", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-12.u116", 0x000000, 0x100000, CRC(35f3c2a3) SHA1(70efebfe248401ba3d766dc0e4bcc2846cd0d9a0) )
	ROM_LOAD16_WORD_SWAP( "93095-13.u117", 0x100000, 0x100000, CRC(1ebd45da) SHA1(99b0ac734890673064b2a4b4b57ff2694e338dea) )
	ROM_LOAD16_WORD_SWAP( "93095-14.u118", 0x200000, 0x100000, CRC(760d871b) SHA1(4887122ad0518c90f08c11a7a6b694f3fd218498) )
	ROM_LOAD16_WORD_SWAP( "93095-15.u119", 0x300000, 0x100000, CRC(d011be88) SHA1(837409a2584abdf22e022b0f06181a600a974cbe) )
	ROM_LOAD16_WORD_SWAP( "93095-16.u120", 0x400000, 0x100000, CRC(a9c16c9c) SHA1(a34e81324c875c2a57f778d1dbdda8da81850a29) )
	ROM_LOAD16_WORD_SWAP( "93095-17.u121", 0x500000, 0x100000, CRC(51b57288) SHA1(821473d51565bc0a8b9a979723ce1307b97e517e) )
	ROM_LOAD16_WORD_SWAP( "93095-18.u122", 0x600000, 0x100000, CRC(b135e3f2) SHA1(339fb4007ca0f379b7554a1c4f711f494a371fb2) )
	ROM_LOAD16_WORD_SWAP( "93095-19.u123", 0x700000, 0x100000, CRC(67695537) SHA1(4c78ce3e36f27d2a6a9e50e8bf896335d4d0958a) )

	ROM_REGION( 0x240000, "oki1", 0 )
	ROM_LOAD( "93095-10.u48", 0x040000, 0x100000, CRC(329ac6c5) SHA1(e809b94e2623141f5a48995cfa97fe1ead7ab40b) )
	ROM_LOAD( "93095-11.u49", 0x140000, 0x100000, CRC(75d6097c) SHA1(3c89a7c9b12087e2d969b822419d3e5f98f5cb1d) )

	ROM_REGION( 0x240000, "oki2", 0 )
	ROM_LOAD( "93095-8.u46",  0x040000, 0x100000, CRC(f019bedb) SHA1(4b6e10f85671c75b666e547887d403d6e607cec8) )
	ROM_LOAD( "93095-9.u47",  0x140000, 0x100000, CRC(adc83765) SHA1(9e760443f9de21c1bb7e33eaa1541023fcdc60ab) )

	ROM_REGION( 0x0220, "proms", 0 )
	ROM_LOAD( "22.u81",       0x000000, 0x0020, CRC(67d5ec4b) SHA1(87d32948a0c88277dcdd0eaa035bde40fc7db5fe) )
	ROM_LOAD( "21.u71",       0x000020, 0x0100, CRC(182cd81f) SHA1(3a76bea81b34ea7ccf56044206721058aa5b03e6) )
	ROM_LOAD( "20.u54",       0x000100, 0x0100, CRC(38bd0e2f) SHA1(20d311869642cd96bb831fdf4a458e0d872f03eb) )
ROM_END

ROM_START( powerinshc05 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-3a_hc05.u108", 0x00000, 0x80000, CRC(522e776a) SHA1(4b3965a3388fdbb438d5cdbff7194cc3344a51e7) )
	ROM_LOAD16_WORD_SWAP( "93095-4.u109",  0x80000, 0x80000, CRC(d3d7a782) SHA1(7846de0ebb09bd9b2534cd451ff9aa5175e60647) )

	ROM_REGION( 0x20000, "soundcpu", 0 )
	ROM_LOAD( "93095-2.u90",  0x00000, 0x20000, CRC(4b123cc6) SHA1(ed61d3a2ab20c86b91fd7bafa717be3ce26159be) )

	ROM_REGION( 0x280000, "gfx1", 0 )
	ROM_LOAD( "93095-5.u16",  0x000000, 0x100000, CRC(b1371808) SHA1(15fca313314ff2e0caff35841a2fdda97f6235a8) )
	ROM_LOAD( "93095-6_hc01.u17",  0x100000, 0x100000, CRC(4a7a6bd8) SHA1(953bba9606795ec32c9c0e4e0fd4e88da9708cf8) )
	ROM_LOAD( "93095-7.u18",  0x200000, 0x080000, CRC(2dd76149) SHA1(975e4d371fdfbbd9a568da4d4c91ffd3f0ae636e) )

	ROM_REGION( 0x100000, "gfx2", 0 )
	ROM_LOAD( "93095-1_hc01.u15",  0x000000, 0x020000, CRC(7e73e1d8) SHA1(ff8d8ecbb01122291404f93a60d6e0c3fc56c3c7) )

	ROM_REGION( 0x800000, "gfx3", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-12.u116", 0x000000, 0x100000, CRC(35f3c2a3) SHA1(70efebfe248401ba3d766dc0e4bcc2846cd0d9a0) )
	ROM_LOAD16_WORD_SWAP( "93095-13.u117", 0x100000, 0x100000, CRC(1ebd45da) SHA1(99b0ac734890673064b2a4b4b57ff2694e338dea) )
	ROM_LOAD16_WORD_SWAP( "93095-14.u118", 0x200000, 0x100000, CRC(760d871b) SHA1(4887122ad0518c90f08c11a7a6b694f3fd218498) )
	ROM_LOAD16_WORD_SWAP( "93095-15.u119", 0x300000, 0x100000, CRC(d011be88) SHA1(837409a2584abdf22e022b0f06181a600a974cbe) )
	ROM_LOAD16_WORD_SWAP( "93095-16.u120", 0x400000, 0x100000, CRC(a9c16c9c) SHA1(a34e81324c875c2a57f778d1dbdda8da81850a29) )
	ROM_LOAD16_WORD_SWAP( "93095-17.u121", 0x500000, 0x100000, CRC(51b57288) SHA1(821473d51565bc0a8b9a979723ce1307b97e517e) )
	ROM_LOAD16_WORD_SWAP( "93095-18.u122", 0x600000, 0x100000, CRC(b135e3f2) SHA1(339fb4007ca0f379b7554a1c4f711f494a371fb2) )
	ROM_LOAD16_WORD_SWAP( "93095-19.u123", 0x700000, 0x100000, CRC(67695537) SHA1(4c78ce3e36f27d2a6a9e50e8bf896335d4d0958a) )

	ROM_REGION( 0x240000, "oki1", 0 )
	ROM_LOAD( "93095-10.u48", 0x040000, 0x100000, CRC(329ac6c5) SHA1(e809b94e2623141f5a48995cfa97fe1ead7ab40b) )
	ROM_LOAD( "93095-11.u49", 0x140000, 0x100000, CRC(75d6097c) SHA1(3c89a7c9b12087e2d969b822419d3e5f98f5cb1d) )

	ROM_REGION( 0x240000, "oki2", 0 )
	ROM_LOAD( "93095-8.u46",  0x040000, 0x100000, CRC(f019bedb) SHA1(4b6e10f85671c75b666e547887d403d6e607cec8) )
	ROM_LOAD( "93095-9.u47",  0x140000, 0x100000, CRC(adc83765) SHA1(9e760443f9de21c1bb7e33eaa1541023fcdc60ab) )

	ROM_REGION( 0x0220, "proms", 0 )
	ROM_LOAD( "22.u81",       0x000000, 0x0020, CRC(67d5ec4b) SHA1(87d32948a0c88277dcdd0eaa035bde40fc7db5fe) )
	ROM_LOAD( "21.u71",       0x000020, 0x0100, CRC(182cd81f) SHA1(3a76bea81b34ea7ccf56044206721058aa5b03e6) )
	ROM_LOAD( "20.u54",       0x000100, 0x0100, CRC(38bd0e2f) SHA1(20d311869642cd96bb831fdf4a458e0d872f03eb) )
ROM_END

ROM_START( powerinshc06 )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "rom1_hc01", 0x000000, 0x080000, CRC(cf74aefb) SHA1(0f19100327378bd12f8dc7504b53980e0d5622ce) )
	ROM_LOAD16_WORD_SWAP( "rom2", 0x080000, 0x080000, CRC(d3d7a782) SHA1(7846de0ebb09bd9b2534cd451ff9aa5175e60647) )

	ROM_REGION( 0x280000, "gfx1", 0 )
	ROM_LOAD( "rom6",  0x000000, 0x200000, CRC(b6c10f80) SHA1(feece0aeaa01a455d0c4885a3699f8bda14fe00f) )
	ROM_LOAD( "rom4",  0x200000, 0x080000, CRC(2dd76149) SHA1(975e4d371fdfbbd9a568da4d4c91ffd3f0ae636e) )

	ROM_REGION( 0x100000, "gfx2", 0 )
	ROM_LOAD( "rom3",  0x000000, 0x020000, CRC(6a579ee0) SHA1(438e87b930e068e0cf7352e614a14049ebde6b8a) )

	ROM_REGION( 0x800000, "gfx3", 0 )
	ROM_LOAD16_WORD_SWAP( "rom10", 0x000000, 0x200000, CRC(efad50e8) SHA1(89e8c307b927e987a32d22ab4ab7f3be037cca03) )
	ROM_LOAD16_WORD_SWAP( "rom9",  0x200000, 0x200000, CRC(08229592) SHA1(759679e89832b475adfdc783630d9ee2c105b0f3) )
	ROM_LOAD16_WORD_SWAP( "rom8",  0x400000, 0x200000, CRC(b02fdd6d) SHA1(1e2c52b4e9999f0b564fcf13ff41b097ad7d0c39) )
	ROM_LOAD16_WORD_SWAP( "rom7",  0x600000, 0x200000, CRC(92ab9996) SHA1(915ec8f383cc3652c3816a9b56ee54e22e104a5c) )

	ROM_REGION( 0x080000, "oki1", 0 )
	ROM_LOAD( "rom5", 0x000000, 0x080000, CRC(88579c8f) SHA1(13083934ab294c9b08d3e36f55c00a6a2e5a0507) )
ROM_END

ROM_START( powerinshc07 ) //powerinspu
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "93095-3a_hc07.u108", 0x00000, 0x80000, CRC(343c79e8) SHA1(0a7cdf0290fa4ed771667adee5779690183552c3) )
	ROM_LOAD16_WORD_SWAP( "93095-4.u109",  0x80000, 0x80000, CRC(d3d7a782) SHA1(7846de0ebb09bd9b2534cd451ff9aa5175e60647) )

	ROM_REGION( 0x20000, "soundcpu", 0 )
	ROM_LOAD( "93095-2.u90",  0x00000, 0x20000, CRC(4b123cc6) SHA1(ed61d3a2ab20c86b91fd7bafa717be3ce26159be) )

	ROM_REGION( 0x280000, "gfx1", 0 )
	ROM_LOAD( "ba0.s0.27c040", 0x000000, 0x80000, CRC(1975b4b8) SHA1(cb400967744fa602df1bd2d88950dfdbdc77073f) )
	ROM_LOAD( "ba1.s1.27c040", 0x080000, 0x80000, CRC(376e4919) SHA1(12baa17382c176838df1b5ef86f1fa6dbcb978dd) )
	ROM_LOAD( "ba2.s2.27c040", 0x100000, 0x80000, CRC(0d5ff532) SHA1(4febdb9cdacd85903a4a28e8df945dee0ce85558) )
	ROM_LOAD( "ba3.s3.27c040", 0x180000, 0x80000, CRC(99b25791) SHA1(82f4bb5780826773d2e5f7143afb3ba209f57652) )
	ROM_LOAD( "ba4.s4.27c040", 0x200000, 0x80000, CRC(2dd76149) SHA1(975e4d371fdfbbd9a568da4d4c91ffd3f0ae636e) )

	ROM_REGION( 0x100000, "gfx2", 0 )
	ROM_LOAD( "93095-1.u15",  0x000000, 0x020000, CRC(6a579ee0) SHA1(438e87b930e068e0cf7352e614a14049ebde6b8a) )

	ROM_REGION( 0x800000, "gfx3", 0 )
	ROM_LOAD16_BYTE( "fo0.mo0.27c040", 0x000001, 0x80000, CRC(8b9b89c9) SHA1(f1d39d1a62e40a14642d8f22fc38b764465a8daa) )
	ROM_LOAD16_BYTE( "fe0.me0.27c040", 0x000000, 0x80000, CRC(4d127bdf) SHA1(26a7c277e7660a7c7c0c11cacadf815d2487ba8a) )
	ROM_LOAD16_BYTE( "fo1.mo1.27c040", 0x100001, 0x80000, CRC(298eb50e) SHA1(2b922c1473bb559a1e8bd6221619141658179bb9) )
	ROM_LOAD16_BYTE( "fe1.me1.27c040", 0x100000, 0x80000, CRC(57e6d283) SHA1(4701576c8663ba47f388a02e61ef078a9dbbd212) )
	ROM_LOAD16_BYTE( "fo2.mo2.27c040", 0x200001, 0x80000, CRC(fb184167) SHA1(20924d3f35509f2f6af61f565b852ea72326d02c) )
	ROM_LOAD16_BYTE( "fe2.me2.27c040", 0x200000, 0x80000, CRC(1b752a4d) SHA1(1b13f28af208542bee9da298d6e9db676cbc0845) )
	ROM_LOAD16_BYTE( "fo3.mo3.27c040", 0x300001, 0x80000, CRC(2f26ba7b) SHA1(026f960fa4de09ed940dd83a3db467c3676c5024) )
	ROM_LOAD16_BYTE( "fe3.me3.27c040", 0x300000, 0x80000, CRC(0263d89b) SHA1(526b8ed05dffcbe98a44372bd55ad7b0ba91fc0f) )
	ROM_LOAD16_BYTE( "fo4.mo4.27c040", 0x400001, 0x80000, CRC(c4633294) SHA1(9578f516eaf09e743ee0262ce227f811bea1be8f) )
	ROM_LOAD16_BYTE( "fe4.me4.27c040", 0x400000, 0x80000, CRC(5e4b5655) SHA1(f86509e75ec0c68f728715a5a325f6d1a30cfd93) )
	ROM_LOAD16_BYTE( "fo5.mo5.27c040", 0x500001, 0x80000, CRC(4d4b0e4e) SHA1(782c5edc533f10757cb18d2411046e44aa075ba1) )
	ROM_LOAD16_BYTE( "fe5.me5.27c040", 0x500000, 0x80000, CRC(7e9f2d2b) SHA1(cfee03c38a6c781ad370638748244a164b83d588) )
	ROM_LOAD16_BYTE( "fo6.mo6.27c040", 0x600001, 0x80000, CRC(0e7671f2) SHA1(301af5c4229451cba9fdf40285dd7243626ffed4) )
	ROM_LOAD16_BYTE( "fe6.me6.27c040", 0x600000, 0x80000, CRC(ee59b1ec) SHA1(437bc50c3b32c2edee549f5021345f1c924896b4) )
	ROM_LOAD16_BYTE( "fo7.mo7.27c040", 0x700001, 0x80000, CRC(9ab1998c) SHA1(fadaa4a46cefe0093ee1ebeddbae63143fa7bb5a) )
	ROM_LOAD16_BYTE( "fe7.me7.27c040", 0x700000, 0x80000, CRC(1ab0c88a) SHA1(8bc72732f5911e0d4e0cf12fd2fb12d67e03299e) )

	ROM_REGION( 0x240000, "oki1", 0 )
	ROM_LOAD( "ao0.ad00.27c040", 0x040000, 0x80000, CRC(8cd6824e) SHA1(aa6d8917558de4f2aa8d80527209b9fe91122eb3) )
	ROM_LOAD( "ao1.ad01.27c040", 0x0c0000, 0x80000, CRC(e31ae04d) SHA1(c08d58a4250d8bdb68b8e5012624f345936520e1) )
	ROM_LOAD( "ao2.ad02.27c040", 0x140000, 0x80000, CRC(c4c9f599) SHA1(1d74acd626406052bec533a918ca24e14a2578f2) )
	ROM_LOAD( "ao3.ad03.27c040", 0x1c0000, 0x80000, CRC(f0a9f0e1) SHA1(4221e0824cdc8bcd6ea1c3811f4e3b7cd99478f2) )

	ROM_REGION( 0x240000, "oki2", 0 )
	ROM_LOAD( "ad10.ad10.27c040", 0x040000, 0x80000, CRC(62557502) SHA1(d72abdaec1c6f55f9b0099b7a8a297e0e14f920c) )
	ROM_LOAD( "ad11.ad11.27c040", 0x0c0000, 0x80000, CRC(dbc86bd7) SHA1(6f1bc3c7e6976fdcd4b2341cea07002fb0cefb14) )
	ROM_LOAD( "ad12.ad12.27c040", 0x140000, 0x80000, CRC(5839a2bd) SHA1(53988086ef97b2671044f6da9d97b1886900b64d) )
	ROM_LOAD( "ad13.ad13.27c040", 0x1c0000, 0x80000, CRC(446f9dc3) SHA1(5c81eb9a7cbea995db9a10d3b6460d02e104825f) )

	ROM_REGION( 0x0220, "proms", 0 )
	ROM_LOAD( "22.u81",       0x000000, 0x0020, CRC(67d5ec4b) SHA1(87d32948a0c88277dcdd0eaa035bde40fc7db5fe) )
	ROM_LOAD( "21.u71",       0x000020, 0x0100, CRC(182cd81f) SHA1(3a76bea81b34ea7ccf56044206721058aa5b03e6) )
	ROM_LOAD( "20.u54",       0x000100, 0x0100, CRC(38bd0e2f) SHA1(20d311869642cd96bb831fdf4a458e0d872f03eb) )
ROM_END

/*    YEAR  NAME             PARENT     MACHINE        INPUT                           INIT     MONITOR   COMPANY       FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2015, powerinshc01,    powerins, powerins,      powerins,   powerins_state,   empty_init,  ROT0,    "hack",      "Power Instinct (Great Blood Temple Simplification 2015-12-05)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, powerinshc02,    powerins, powerins,      powerins,   powerins_state,   empty_init,  ROT0,    "hack",      "Power Instinct (Enable Hidden Character)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, powerinshc03,    powerins, powerins,      powerins,   powerins_state,   empty_init,  ROT0,    "hack",      "Power Instinct (Simplify Edition 2018-06-04)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, powerinshc04,    powerins, powerins,      powerins,   powerins_state,   empty_init,  ROT0,    "hack",      "Power Instinct (Optimised Edition 2020-05-15)", MACHINE_SUPPORTS_SAVE )
GAME( 2006, powerinshc05,    powerins, powerins,      powerins,   powerins_state,   empty_init,  ROT0,    "hack",      "Power Instinct (translation Brazilian)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, powerinshc06,    powerins, powerinsa,     powerins,   powerins_state,   empty_init,  ROT0,    "hack",      "Power Instinct (Dragon Edition Fixed 2022-03-29)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, powerinshc07,    powerins, powerins,      powerinj,   powerins_state,   empty_init,  ROT0,    "hack",      "Power Instinct (Dragon Edition 2022-03-27)", MACHINE_SUPPORTS_SAVE )
