// license:BSD-3-Clause
// copyright-holders:Gaston90
#include "../mame/drivers/cave.cpp"

/********************
  Hack And Homebrow
***********************/

ROM_START( agallethc01 ) //agalleta
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "bp962a_hc01.u45", 0x000000, 0x080000, CRC(a99f51d5) SHA1(acc2b0d9037a260b7ce198d8983985a63de7ebea) )

	ROM_REGION( 0x80000, "audiocpu", 0 )
	ROM_LOAD( "bp962a.u9",  0x00000, 0x80000, CRC(06caddbe) SHA1(6a3cc50558ba19a31b21b7f3ec6c6e2846244ff1) )

	ROM_REGION( 0x400000 * 2, "sprites0", 0 )
	ROM_LOAD( "bp962a.u76", 0x000000, 0x200000, CRC(858da439) SHA1(33a3d2a3ec3fa3364b00e1e43b405e5030a5b2a3) )
	ROM_LOAD( "bp962a.u77", 0x200000, 0x200000, CRC(ea2ba35e) SHA1(72487f21d44fe7be9a98068ce7f57a43c132945f) )

	ROM_REGION( 0x100000, "layer0", 0 )
	ROM_LOAD( "bp962a.u53", 0x000000, 0x100000, CRC(fcd9a107) SHA1(169b94db8389e7d47d4d77f36907a62c30fea727) )
	ROM_CONTINUE(           0x000000, 0x100000             )

	ROM_REGION( 0x200000, "layer1", 0 )
	ROM_LOAD( "bp962a.u54", 0x000000, 0x200000, CRC(0cfa3409) SHA1(17107e26762ef7e3b902fb29a6d7bc534a4d09aa) )

	ROM_REGION( (1*0x200000)*2, "layer2", 0 )

	ROM_LOAD( "bp962a.u57", 0x000000, 0x200000, CRC(6d608957) SHA1(15f6e8346f5f95eb229505b1b4666dabeb810ee8) )

	ROM_LOAD( "bp962a.u65", 0x200000, 0x100000, CRC(135fcf9a) SHA1(2e8c89c2627bbdef160d96724d07883fb2fa1a57) )
	ROM_CONTINUE(           0x200000, 0x100000             ) 

	ROM_REGION( 0x200000, "oki1", 0 )
	ROM_LOAD( "bp962a.u48", 0x000000, 0x200000, CRC(ae00a1ce) SHA1(5e8c74df0ac77efb3080406870856f958be14f79) )

	ROM_REGION( 0x200000, "oki2", 0 )
	ROM_LOAD( "bp962a.u47", 0x000000, 0x200000, CRC(6d4e9737) SHA1(81c7ecdfc2d38d0b35e26745866f6672f566f936) )

	ROM_REGION16_BE( 0x80, "eeprom", 0 )
	ROM_LOAD16_WORD( "agallet_europe.nv", 0x0000, 0x0080, CRC(ec38bf65) SHA1(cb8d9eacc0cf55a0c6b187e6673e3354554314b5) )
ROM_END

ROM_START( ddonpachhc01 ) //ddonpachddj
	ROM_REGION( 0x100000, "maincpu", 0 )    
	ROM_LOAD16_BYTE( "b1_hc01.u27", 0x000000, 0x080000, CRC(cdd41ce2) SHA1(01ba0817b1044ac9cf79addc3a234fd69cfb3f59) )
	ROM_LOAD16_BYTE( "b2_hc01.u26", 0x000001, 0x080000, CRC(ff0e6033) SHA1(f0d098cfbf7e7c3738cf4b844e5578205d7960b5) )

	ROM_REGION( 0x800000 * 2, "sprites0", 0 )
	ROM_LOAD16_WORD_SWAP( "u50.bin", 0x000000, 0x200000, CRC(14b260ec) SHA1(33bda210302428d5500115d0c7a839cdfcb67d17) )
	ROM_LOAD16_WORD_SWAP( "u51.bin", 0x200000, 0x200000, CRC(e7ba8cce) SHA1(ad74a6b7d53760b19587c4a6dbea937daa7e87ce) )
	ROM_LOAD16_WORD_SWAP( "u52.bin", 0x400000, 0x200000, CRC(02492ee0) SHA1(64d9cc64a4ad189a8b03cf6a749ddb732b4a0014) )
	ROM_LOAD16_WORD_SWAP( "u53.bin", 0x600000, 0x200000, CRC(cb4c10f0) SHA1(a622e8bd0c938b5d38b392b247400b744d8be288) )

	ROM_REGION( 0x200000, "layer0", 0 )
	ROM_LOAD( "u60.bin", 0x000000, 0x200000, CRC(903096a7) SHA1(a243e903fef7c4a7b71383263e82e42acd869261) )

	ROM_REGION( 0x200000, "layer1", 0 )
	ROM_LOAD( "u61.bin", 0x000000, 0x200000, CRC(d89b7631) SHA1(a66bb4955ca58fab8973ca37a0f971e9a67ce017) )

	ROM_REGION( 0x200000, "layer2", 0 )
	ROM_LOAD( "u62.bin", 0x000000, 0x200000, CRC(292bfb6b) SHA1(11b385991ee990eb5ef36e136b988802b5f90fa4) )

	ROM_REGION( 0x400000, "ymz", 0 )
	ROM_LOAD( "u6.bin", 0x000000, 0x200000, CRC(9dfdafaf) SHA1(f5cb450cdc78a20c3a74c6dac05c9ac3cba08327) )
	ROM_LOAD( "u7.bin", 0x200000, 0x200000, CRC(795b17d5) SHA1(cbfc29f1df9600c82e0fdae00edd00da5b73e14c) )

	ROM_REGION16_BE( 0x80, "eeprom", 0 )
	ROM_LOAD16_WORD( "eeprom-ddonpach.bin", 0x0000, 0x0080, CRC(315fb546) SHA1(7f597107d1610fc286413e0e93c794c80c0c554f) )
ROM_END

ROM_START( espradehc01 ) //espradejo
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "u42_hc01.int", 0x000000, 0x080000, CRC(3c9a58e6) SHA1(bbdaac280023ec907036c31715e6f53cc157d0d4) )
	ROM_LOAD16_BYTE( "u41_hc01.int", 0x000001, 0x080000, CRC(f1b4bd9b) SHA1(12dce739bf8163046d16a8f92583d3021667bea9) )

	ROM_REGION( 0x1000000, "sprites0", 0 )
	ROM_LOAD16_BYTE( "esp_u63.u63", 0x000000, 0x400000, CRC(2f2fe92c) SHA1(9519e365248bcec8419786eabb16fe4aae299af5) )
	ROM_LOAD16_BYTE( "esp_u64.u64", 0x000001, 0x400000, CRC(491a3da4) SHA1(53549a2bd3edc7b5e73fb46e1421b156bb0c190f) )
	ROM_LOAD16_BYTE( "esp_u65.u65", 0x800000, 0x400000, CRC(06563efe) SHA1(94e72da1f542b4e0525b4b43994242816b43dbdc) )
	ROM_LOAD16_BYTE( "esp_u66.u66", 0x800001, 0x400000, CRC(7bbe4cfc) SHA1(e77d0ed7a11b5abca1df8a0eb20ac9360cf79e76) )

	ROM_REGION( 0x800000, "layer0", 0 )
	ROM_LOAD( "esp_u54.u54", 0x000000, 0x400000, CRC(e7ca6936) SHA1(b7f5ab67071a1d9dd3d2c1cd2304d9cdad68850c) )
	ROM_LOAD( "esp_u55.u55", 0x400000, 0x400000, CRC(f53bd94f) SHA1(d0a74fb3d36fe522ef075e5ae44a9980da8abe2f) )

	ROM_REGION( 0x800000, "layer1", 0 )
	ROM_LOAD( "esp_u52.u52", 0x000000, 0x400000, CRC(e7abe7b4) SHA1(e98da45497e1aaf0d6ab352ec3e43c7438ed792a) )
	ROM_LOAD( "esp_u53.u53", 0x400000, 0x400000, CRC(51a0f391) SHA1(8b7355cbad119f4e1add14e5cd5e343ec6706104) )

	ROM_REGION( 0x400000, "layer2", 0 )
	ROM_LOAD( "esp_u51.u51", 0x000000, 0x400000, CRC(0b9b875c) SHA1(ef05447cd8565ae24bb71db42342724622ad1e3e) )

	ROM_REGION( 0x400000, "ymz", 0 )
	ROM_LOAD( "esp_u19.u19", 0x000000, 0x400000, CRC(f54b1cab) SHA1(34d70bb5798de85d892c062001d9ac1d6604fd9f) )

	ROM_REGION16_BE( 0x80, "eeprom", 0 )
	ROM_LOAD16_WORD( "eeprom-esprade.bin", 0x0000, 0x0080, CRC(315fb546) SHA1(7f597107d1610fc286413e0e93c794c80c0c554f) )
ROM_END

ROM_START( feversoshc01 ) //feversosddj
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "cv01-u34_hc01.sos", 0x000000, 0x080000, CRC(0243de22) SHA1(746963279f9a665cf1cc7c47e58389b41b3a582e) )
	ROM_LOAD16_BYTE( "cv01-u33_hc01.sos", 0x000001, 0x080000, CRC(1033b945) SHA1(ec01c1cc400ec6a66e6b36c59014f3f55507c7cb) )

	ROM_REGION( 0x800000 * 2, "sprites0", 0 )
	ROM_LOAD( "cv01-u25.bin", 0x000000, 0x400000, CRC(a6f6a95d) SHA1(e1eb45cb5d0e6163edfd9d830633b913fb53c6ca) )
	ROM_LOAD( "cv01-u26.bin", 0x400000, 0x400000, CRC(32edb62a) SHA1(3def74e1316b80cc25a8c3ac162cd7bcb8cc807c) )

	ROM_REGION( 0x200000, "layer0", 0 )
	ROM_LOAD( "cv01-u50.bin", 0x000000, 0x200000, CRC(7a344417) SHA1(828bd8f95d2fcc34407e17629ccafc904a4ea12d) )

	ROM_REGION( 0x200000, "layer1", 0 )
	ROM_LOAD( "cv01-u49.bin", 0x000000, 0x200000, CRC(d21cdda7) SHA1(cace4650de580c3c4a037f1f5c32bfc1846b383c) )

	ROM_REGION( 0x400000, "ymz", 0 )
	ROM_LOAD( "cv01-u19.bin", 0x000000, 0x400000, CRC(5f5514da) SHA1(53f27364aee544572a82649c9ff29bacc642b732) )

	ROM_REGION16_BE( 0x80, "eeprom", 0 )
	ROM_LOAD16_WORD( "eeprom-feversos.bin", 0x0000, 0x0080, CRC(d80303aa) SHA1(8580f7c2223c72614516d800a98465e362c333ef) )
ROM_END

ROM_START( guwangehc01 ) //guwangeddj
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "gu-u0127_hc01.bin", 0x000000, 0x080000, CRC(26d2d8ee) SHA1(61a4ff1579aa83db7c7332f5973d87f2fa933743) )
	ROM_LOAD16_BYTE( "gu-u0129_hc01.bin", 0x000001, 0x080000, CRC(d29b2755) SHA1(669683a6ee007fe6117c81dbb07980de65cd14ef) )

	ROM_REGION( 0x2000000, "sprites0", 0 )
	ROM_LOAD16_BYTE( "u083.bin", 0x0000000, 0x800000, CRC(adc4b9c4) SHA1(3f9fb004e19187bbfa87ddfe8cfc69740656a1bd) )
	ROM_LOAD16_BYTE( "u082.bin", 0x0000001, 0x800000, CRC(3d75876c) SHA1(705b8c2dbdc31e9516f429969f87988beec796d7) )
	ROM_LOAD16_BYTE( "u086.bin", 0x1000000, 0x400000, CRC(188e4f81) SHA1(626074d81782a6de0b52406331b4b8561d3e36f5) )
	ROM_RELOAD(                  0x1800000, 0x400000 )
	ROM_LOAD16_BYTE( "u085.bin", 0x1000001, 0x400000, CRC(a7d5659e) SHA1(10abac022ebe106a3ca7186ff18ca2757f903033) )
	ROM_RELOAD(                  0x1800001, 0x400000 )

	ROM_REGION( 0x800000, "layer0", 0 )
	ROM_LOAD( "u101.bin", 0x000000, 0x800000, CRC(0369491f) SHA1(ca6b1345506f13a17c9bace01637d1f61a278644) )

	ROM_REGION( 0x400000, "layer1", 0 )
	ROM_LOAD( "u10102.bin", 0x000000, 0x400000, CRC(e28d6855) SHA1(7001a6e298c6a1fcceb79586bf5f4bf0f30027f6) )

	ROM_REGION( 0x400000, "layer2", 0 )
	ROM_LOAD( "u10103.bin", 0x000000, 0x400000, CRC(0fe91b8e) SHA1(8b71ebeef5e4d2b00fdaaab97776d74e1c96dc59) )

	ROM_REGION( 0x400000, "ymz", 0 )
	ROM_LOAD( "u0462.bin", 0x000000, 0x400000, CRC(b3d75691) SHA1(71d8dae92be1542a3cff50efeec0bf3c14ab59f5) )

	ROM_REGION( 0x0004, "plds", 0 )
	ROM_LOAD( "atc05-1.bin", 0x0000, 0x0001, NO_DUMP )
	ROM_LOAD( "u0259.bin",   0x0000, 0x0001, NO_DUMP )
	ROM_LOAD( "u108.bin",    0x0000, 0x0001, NO_DUMP )
	ROM_LOAD( "u084.bin",    0x0000, 0x0001, NO_DUMP )

	ROM_REGION16_BE( 0x80, "eeprom", 0 )
	ROM_LOAD16_WORD( "eeprom-guwange.bin", 0x0000, 0x0080, CRC(c3174959) SHA1(29b5c94722756481e4f84bfd75dee15fdb5c8cf7) )
ROM_END

/*    YEAR     NAME         PARENT          MACHINE      INPUT                       INIT      MONITOR   COMPANY      FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2022, agallethc01,    agallet,        sailormn,     cave,     cave_state, init_agallet,   ROT270, "hack",       "Air Gallet (The Strongest Firepower)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, ddonpachhc01,   ddonpach,       ddonpach,     cave,     cave_state, init_ddonpach,  ROT270, "hack",       "DoDonPachi (The Strongest Firepower)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, espradehc01,    esprade,        esprade,      cave,     cave_state, init_esprade,   ROT270, "hack",       "ESP Ra.De. (The Strongest Firepower)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, feversoshc01,   feversos,       dfeveron,     cave,     cave_state, init_feversos,  ROT270, "hack",       "Fever SOS (The Strongest Firepower)", MACHINE_SUPPORTS_SAVE )
GAME( 1999, guwangehc01,    guwange,        guwange,      guwange,  cave_state, init_guwange,   ROT270, "hack",       "Guwange (The Strongest Firepower)",  MACHINE_SUPPORTS_SAVE )
