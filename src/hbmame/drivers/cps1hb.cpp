// license:BSD-3-Clause
// copyright-holders:Gaston90

WRITE16_MEMBER( cps_state::dinoh_sound_command_w )
{
	/* Pass the Sound Code to the Q-Sound Shared Ram */
	m_qsound_sharedram1[1] = data;
}

WRITE16_MEMBER( cps_state::daimakb_palctrl_w )
{
	m_cps_b_regs[0x30 / 2] = data;
}

WRITE16_MEMBER(cps_state::daimakb_layer_w)
{
	if (offset == 0x00)
		m_cps_a_regs[0x0e / 2] = data; /* scroll 1y */
	else
	if (offset == 0x01)
		m_cps_a_regs[0x0c / 2] = data - 0x40; /* scroll 1x */
	else
	if (offset == 0x02)
	{
		m_cps_a_regs[0x12 / 2] = data; /* scroll 2y */
		m_cps_a_regs[0x20 / 2] = data; /* row scroll start */
	}
	else
	if (offset == 0x03)
		m_cps_a_regs[0x10 / 2] = data - 0x40; /* scroll 2x */
	else
	if (offset == 0x04)
		m_cps_a_regs[0x16 / 2] = data; /* scroll 3y */
	else
	if (offset == 0x05)
		m_cps_a_regs[0x14 / 2] = data - 0x40; /* scroll 3x */
	else
	if (offset == 0x06)
	{
		switch (data)
		{
		case 0x0000:
			data = (1 << 12) | (2 << 8) | (3 << 6);
			break;
		case 0x0001:
			data = (1 << 12) | (3 << 6);
			break;
		case 0x0002:
			data = (3 << 12) | (1 << 6);
			break;
		case 0x0006:
			data = 0;
			break;
		default:
			data = 0;
			printf ("Unknown control word = %X\n",data);
		}
		m_cps_b_regs[0x26 / 2] = data;
	}
}



/**************************************************************************

	Address Maps

***************************************************************************/

void cps_state::daimakb_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800001).portr("IN1");  /* Player input ports */
	map(0x800006,0x800007).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_hack_dsw_r));  /* System input ports / Dip Switches */
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800166,0x800171).nopw();  // not used
	map(0xe00000,0xe0003f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");  // dummy region
	map(0x880000,0x880001).w(FUNC(cps_state::daimakb_palctrl_w));
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x980000,0x98000d).w(FUNC(cps_state::daimakb_layer_w));
	map(0x990000,0x993fff).nopw();  // bootleg sprites, not needed
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::sk2h35_map(address_map &map) {
/* unknown addresses (all write): 930008-930807. No 3rd player controls. NVRAM doesn't work */
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800001).portr("IN1");  /* Player input ports */
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x80001c,0x80001d).portr("EEPROMIN").portw("EEPROMOUT");
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");  /* CPS-B custom */
	map(0x800180,0x800187).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x800188,0x80018f).w(FUNC(cps_state::cps1_soundlatch2_w));  /* Sound timer fade */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0x930008,0x930807).nopw();
	map(0xf18000,0xf19fff).rw(FUNC(cps_state::qsound_sharedram1_r),FUNC(cps_state::qsound_sharedram1_w));  /* Q RAM */
	map(0xf1ce74,0xf1ce75).nopw();
	map(0xf1e000,0xf1ffff).rw(FUNC(cps_state::qsound_sharedram2_r),FUNC(cps_state::qsound_sharedram2_w));  /* Q RAM */
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::sk2h3_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).ram().share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x880000,0x880001).portr("IN1");  /* Player input ports */
	map(0x880006,0x88000d).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x88000e,0x88000f).w(FUNC(cps_state::cps1_soundlatch_w));
	map(0x880e78,0x880e79).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls (later games) */
	map(0x890000,0x890001).nopw();
	map(0x8bfff6,0x8bfff9).nopr();  /* unknown */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::sk2h31_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800030,0x800031).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* Output ports */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x880000,0x880001).portr("IN1");  /* Player input ports */
	map(0x880006,0x880007).w(FUNC(cps_state::cps1_soundlatch_w));
	map(0x880008,0x88000f).r(FUNC(cps_state::cps1_dsw_r));  /* System input ports / Dip Switches */
	map(0x880e7e,0x880e7f).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls (later games) */
	map(0x890000,0x890001).nopw();
	map(0x8bfff6,0x8bfff9).nopr();  /* unknown */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram().share(m_mainram);
}

void cps_state::wofsf2_map(address_map &map) {
	map(0x000000,0x3fffff).rom();
	map(0x800000,0x800007).portr("IN1");
	map(0x800018,0x80001f).r(FUNC(cps_state::cps1_hack_dsw_r));
	map(0x800030,0x800037).w(FUNC(cps_state::cps1_coinctrl_w));
	map(0x800100,0x80013f).w(FUNC(cps_state::cps1_cps_a_w)).share("cps_a_regs");  /* CPS-A custom */
	map(0x800140,0x80017f).rw(FUNC(cps_state::cps1_cps_b_r),FUNC(cps_state::cps1_cps_b_w)).share("cps_b_regs");
	map(0x800180,0x800187).w(FUNC(cps_state::cps1_soundlatch_w));  /* Sound command */
	map(0x900000,0x92ffff).ram().w(FUNC(cps_state::cps1_gfxram_w)).share("gfxram");
	map(0xf18000,0xf19fff).ram();
	map(0xf1c000,0xf1c001).r(FUNC(cps_state::cps1_in2_r));  /* Player 3 controls */
	map(0xf1c004,0xf1c005).w(FUNC(cps_state::cpsq_coinctrl2_w));  /* Coin control2 (later games) */
	map(0xf1c006,0xf1c007).portr("EEPROMIN").portw("EEPROMOUT");
	map(0xff0000,0xffffff).ram().share("mainram");
}

/********************************************************************

	Inputs and dips

*********************************************************************/

static INPUT_PORTS_START( dinohz )
	PORT_INCLUDE( dino )

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT  ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN  ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP    ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT  ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN  ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP    ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_MODIFY("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
//	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )
INPUT_PORTS_END

static INPUT_PORTS_START( pnicku )
	PORT_INCLUDE( pnickj )
	PORT_MODIFY("DSWA")
	PORT_DIPNAME( 0x07, 0x07, DEF_STR( Coinage ) )  PORT_DIPLOCATION("SW(A):1,2,3")
	PORT_DIPSETTING(    0x00, DEF_STR( 5C_1C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 4C_1C ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 3C_1C ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0x07, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x06, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x05, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x04, DEF_STR( 1C_4C ) )

	PORT_DIPNAME( 0x10, 0x10, "Chuters" )           PORT_DIPLOCATION("SW(A):5")
	PORT_DIPSETTING(    0x00, "2" )
	PORT_DIPSETTING(    0x10, "1" )

	PORT_MODIFY("DSWC")
	PORT_DIPNAME( 0x04, 0x04, DEF_STR( Free_Play ) ) PORT_DIPLOCATION("SW(C):3")
	PORT_DIPSETTING(    0x04, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
INPUT_PORTS_END

static INPUT_PORTS_START( sk2h21 )
	PORT_INCLUDE( wof )

	PORT_MODIFY("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_MODIFY("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
//	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )
INPUT_PORTS_END


/***********************************************************
             INPUT PORTS, DIPs
***********************************************************/

static INPUT_PORTS_START( sk2h1 )
	PORT_START ("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWA")
	PORT_DIPNAME( 0x03, 0x00, "Play Mode" )
	PORT_DIPSETTING(    0x00, DEF_STR( Normal ) )
	PORT_DIPSETTING(    0x03, "Tournament" )
	PORT_BIT( 0xfc, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWB")
	PORT_DIPNAME( 0x03, 0x03, DEF_STR( Coinage ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_4C ) )
	PORT_BIT( 0xfc, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWC")
	PORT_BIT( 0xff, IP_ACTIVE_HIGH, IPT_UNKNOWN )

	PORT_START ("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(1)
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )

	PORT_START( "EEPROMIN" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_READ_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, do_read)

	PORT_START( "EEPROMOUT" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, di_write)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, clk_write)
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, cs_write)
INPUT_PORTS_END

static INPUT_PORTS_START( sk2h31 )
	PORT_START ("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_START2 )
	PORT_SERVICE_NO_TOGGLE( 0x40, IP_ACTIVE_LOW )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWA")	/* there are lots of other combinations, but this covers the useful ones */
	PORT_DIPNAME( 0xff, 0xff, DEF_STR( Coinage ) )
	PORT_DIPSETTING(    0xde, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0xff, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0xfe, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0xfd, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0xfc, DEF_STR( 1C_4C ) )
	PORT_DIPSETTING(    0x7f, DEF_STR( 1C_7C ) )
	PORT_DIPSETTING(    0xdf, DEF_STR( 1C_8C ) )

	PORT_START ("DSWB")      /* (not used, EEPROM) */
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("DSWC")      /* (not used, EEPROM) */
	PORT_BIT( 0xff, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("IN1")
	PORT_BIT( 0x0001, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0002, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0004, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0008, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(1)
	PORT_BIT( 0x0010, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x0020, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x0040, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0080, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START ("IN2")      /* Player 3 */
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_8WAY PORT_PLAYER(3)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(3)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(3)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN3 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_START3 )

	PORT_START( "EEPROMIN" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_READ_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, do_read)

	PORT_START( "EEPROMOUT" )
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, di_write)
	PORT_BIT( 0x40, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, clk_write)
	PORT_BIT( 0x80, IP_ACTIVE_HIGH, IPT_OUTPUT ) PORT_WRITE_LINE_DEVICE_MEMBER("eeprom", eeprom_serial_93cxx_device, cs_write)
INPUT_PORTS_END

/********************************************************************
*
*  Machine Driver macro
*  ====================
*
*
********************************************************************/


void cps_state::wofsf2(machine_config &config)
{
	wofhfh(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::wofsf2_map);
}

void cps_state::daimakb(machine_config &config)
{
	cps1_10MHz(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::daimakb_map);
}

void cps_state::sk2h3(machine_config &config)
{
	wofhfh(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sk2h3_map);
}

void cps_state::sk2h31(machine_config &config)
{
	wofhfh(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sk2h31_map);
}

void cps_state::sk2h35(machine_config &config)
{
	qsound(config);
	m_maincpu->set_addrmap(AS_PROGRAM, &cps_state::sk2h35_map);
}

void cps_state::init_dinoeh()
{
	m_maincpu->space(AS_PROGRAM).install_write_handler(0x800180, 0x800181, write16_delegate(FUNC(cps_state::dinoh_sound_command_w),this));
	kabuki_setup(dino_decode);
	init_cps1();
}

void cps_state::init_dinoh()
{
	/* Patch out Q-Sound test */
	uint16_t *rom = (uint16_t *)memregion("maincpu")->base();
	rom[0xaacf4/2] = 0x4e71;
	init_dinoeh();
}

void cps_state::init_dinohb()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Fix draw scroll
//	mem8[0x006c2] = 0xC0;
//	mem8[0x006c3] = 0xFF;
	// Fix gfx
	mem8[0x472] = 0xFC;
	mem8[0x473] = 0x33;
	mem8[0x474] = 0x0;
	mem8[0x475] = 0x90;
	mem8[0x476] = 0x80;
	mem8[0x478] = 0x0;
	mem8[0x479] = 0x1;
	mem8[0x47A] = 0xFC;
	mem8[0x47B] = 0x33;
	mem8[0x47C] = 0x80;
	mem8[0x47D] = 0x90;
	mem8[0x47E] = 0x80;
	mem8[0x480] = 0x2;
	mem8[0x481] = 0x1;
	mem8[0x482] = 0xFC;
	mem8[0x483] = 0x33;
	mem8[0x484] = 0xC0;
	mem8[0x485] = 0x90;
	mem8[0x486] = 0x80;
	mem8[0x487] = 0x0;
	mem8[0x488] = 0x4;
	mem8[0x489] = 0x1;
	mem8[0x48A] = 0xFC;
	mem8[0x48B] = 0x33;
	mem8[0x48C] = 0x0;
	mem8[0x48D] = 0x91;
	mem8[0x48E] = 0x80;
	mem8[0x48F] = 0x0;
	mem8[0x490] = 0x6;
	mem8[0x491] = 0x1;
	mem8[0x006cc] = 0x80;
	mem8[0x006cd] = 0x00;
	mem8[0x006ce] = 0x0C;
	mem8[0x006cf] = 0x01;
	mem8[0x006de] = 0x80;
	mem8[0x006df] = 0x00;
	mem8[0x006e0] = 0x10;
	mem8[0x006e1] = 0x01;
	mem8[0x006f0] = 0x80;
	mem8[0x006f1] = 0x00;
	mem8[0x006f2] = 0x14;
	mem8[0x006f3] = 0x01;
	mem8[0x00704] = 0x80;
	mem8[0x00705] = 0x00;
	mem8[0x00706] = 0x0E;
	mem8[0x00707] = 0x01;
	mem8[0x00718] = 0x80;
	mem8[0x00719] = 0x00;
	mem8[0x0071a] = 0x12;
	mem8[0x0071b] = 0x01;
	mem8[0x0072c] = 0x80;
	mem8[0x0072d] = 0x00;
	mem8[0x0072e] = 0x16;
	mem8[0x0072f] = 0x01;
	// Fix screen transitions
	mem8[0x00b28] = 0x00;
	mem8[0x00b29] = 0x70;
	mem8[0x00b2a] = 0x00;
	mem8[0x00b2b] = 0x72;
	mem8[0x00b2c] = 0x3C;
	mem8[0x00b2d] = 0x34;
	mem8[0x00b32] = 0xC1;
	mem8[0x00b33] = 0x20;
	// Fix sound
	mem8[0x00666] = 0xF1;
	mem8[0x00667] = 0x00;
	mem8[0x00668] = 0x02;
	mem8[0x00669] = 0x80;
	mem8[0xaaa6c] = 0xD8;
	mem8[0xaaa6d] = 0x00;

	kabuki_setup(dino_decode);
	init_cps1();
}

void cps_state::init_punisherb()
{
	// note: bytes are swapped around compared to rom_fill.
	uint8_t *mem8 = memregion("maincpu")->base();
	// Use standard ports
	mem8[0xAB3] = 0x33;
	mem8[0xAB4] = 0x30;
	mem8[0xAB6] = 0x80;
	mem8[0xAB7] = 0x0;
	mem8[0xAB8] = 0x56;
	mem8[0xAB9] = 0x1;
	mem8[0xABA] = 0xED;
	mem8[0xABB] = 0x33;
	mem8[0xABC] = 0x32;
	mem8[0xABD] = 0xDB;
	mem8[0xABE] = 0x80;
	mem8[0xABF] = 0x0;
	mem8[0xAC0] = 0x48;
	mem8[0xAC1] = 0x1;
	mem8[0xAC2] = 0xED;
	mem8[0xAC3] = 0x33;
	mem8[0xAC4] = 0x34;
	mem8[0xAC5] = 0xDB;
	mem8[0xAC6] = 0x80;
	mem8[0xAC7] = 0x0;
	mem8[0xAC8] = 0x4A;
	mem8[0xAC9] = 0x1;
	mem8[0xACA] = 0xED;
	mem8[0xACB] = 0x33;
	mem8[0xACC] = 0x2E;
	mem8[0xACD] = 0xDB;
	mem8[0xACE] = 0x80;
	mem8[0xAD0] = 0x52;
	mem8[0xAD1] = 0x1;
	mem8[0xAD2] = 0xED;
	mem8[0xAD3] = 0x33;
	mem8[0xAD4] = 0x88;
	mem8[0xAD5] = 0xDB;
	mem8[0xAD6] = 0x80;
	mem8[0xAD7] = 0x0;
	mem8[0xAD8] = 0x0;
	mem8[0xAD9] = 0x1;
	mem8[0xADA] = 0xED;
	mem8[0xADB] = 0x33;
	mem8[0xADC] = 0x8A;
	mem8[0xADD] = 0xDB;
	mem8[0xADE] = 0x80;
	mem8[0xADF] = 0x0;
	mem8[0xAE0] = 0x2;
	mem8[0xAE1] = 0x1;
	mem8[0xAE2] = 0xED;
	mem8[0xAE3] = 0x33;
	mem8[0xAE4] = 0x8C;
	mem8[0xAE5] = 0xDB;
	mem8[0xAE6] = 0x80;
	mem8[0xAE7] = 0x0;
	mem8[0xAE8] = 0x4;
	mem8[0xAE9] = 0x1;
	mem8[0xAEA] = 0xED;
	mem8[0xAEB] = 0x33;
	mem8[0xAEC] = 0x8E;
	mem8[0xAED] = 0xDB;
	mem8[0xAEE] = 0x80;
	mem8[0xAEF] = 0x0;
	mem8[0xAF0] = 0x6;
	mem8[0xAF1] = 0x1;
	mem8[0xAF2] = 0xED;
	mem8[0xAF3] = 0x33;
	mem8[0xAF4] = 0x90;
	mem8[0xAF5] = 0xDB;
	mem8[0xAF6] = 0x80;
	mem8[0xAF7] = 0x0;
	mem8[0xAF8] = 0x8;
	mem8[0xAF9] = 0x1;
	mem8[0xAFA] = 0xED;
	mem8[0xAFB] = 0x50;
	mem8[0xAFC] = 0x49;
	mem8[0xAFD] = 0xDB;
	mem8[0xAFE] = 0xFC;
	mem8[0xAFF] = 0x33;
	mem8[0xB00] = 0x3F;
	mem8[0xB02] = 0x80;
	mem8[0xB03] = 0x0;
	mem8[0xB04] = 0x4C;
	mem8[0xB05] = 0x1;
	mem8[0xB06] = 0xFC;
	mem8[0xB07] = 0x33;
	mem8[0xB08] = 0x40;
	mem8[0xB09] = 0x91;
	mem8[0xB0A] = 0x80;
	mem8[0xB0C] = 0xA;
	mem8[0xB0D] = 0x1;
	mem8[0xBA8] = 0x80;
	mem8[0xBAA] = 0xC;
	mem8[0xBAB] = 0x1;
	mem8[0xBBA] = 0x80;
	mem8[0xBBC] = 0x10;
	mem8[0xBBD] = 0x1;
	mem8[0xBCC] = 0x80;
	mem8[0xBCE] = 0x14;
	mem8[0xBCF] = 0x1;
	mem8[0xBDA] = 0x80;
	mem8[0xBDC] = 0xE;
	mem8[0xBDD] = 0x1;
	mem8[0xBEE] = 0x80;
	mem8[0xBF0] = 0x12;
	mem8[0xBF1] = 0x1;
	mem8[0xC02] = 0x80;
	mem8[0xC04] = 0x16;
	mem8[0xC05] = 0x1;
	// Transitions
	mem8[0x42b5] = 0;
	// Q sound
	mem8[0x4DBC] = 0x0;
	mem8[0x4DBE] = 0x58;
	mem8[0x4DBF] = 0x0;
	mem8[0x4DC0] = 0xF9;
	mem8[0x4DC1] = 0x41;
	mem8[0x4DC2] = 0xF1;
	mem8[0x4DC3] = 0x0;
	mem8[0x4DC4] = 0x0;
	mem8[0x4DC5] = 0x80;
	mem8[0x4DC6] = 0x28;
	mem8[0x4DC7] = 0x4A;
	mem8[0x4DC8] = 0x1F;
	mem8[0x4DC9] = 0x0;
	mem8[0x4DCA] = 0x0;
	mem8[0x4DCB] = 0x6A;
	mem8[0x4DCC] = 0x4A;
	mem8[0x4DCD] = 0x0;
	mem8[0x4DCE] = 0xED;
	mem8[0x4DCF] = 0x49;
	mem8[0x4DD0] = 0x96;
	mem8[0x4DD1] = 0xE2;
	mem8[0x4DD2] = 0xF4;
	mem8[0x4DD3] = 0x49;
	mem8[0x4DD4] = 0x0;
	mem8[0x4DD5] = 0x0;
	mem8[0x4DD6] = 0x40;
	mem8[0x4DD7] = 0x6;
	mem8[0x4DD8] = 0x10;
	mem8[0x4DDA] = 0x40;
	mem8[0x4DDB] = 0x2;
	mem8[0x4DDC] = 0xFF;
	mem8[0x4DDD] = 0xF;
	mem8[0x4DDE] = 0x40;
	mem8[0x4DDF] = 0x3B;
	mem8[0x4DE0] = 0xE8;
	mem8[0x4DE1] = 0xDA;
	mem8[0x4DE2] = 0x5C;
	mem8[0x4DE3] = 0x11;
	mem8[0x4DE4] = 0x1;
	mem8[0x4DE6] = 0x5C;
	mem8[0x4DE7] = 0x11;
	mem8[0x4DE8] = 0x3;
	mem8[0x4DE9] = 0x0;
	mem8[0x4DEA] = 0x5C;
	mem8[0x4DEB] = 0x11;
	mem8[0x4DEC] = 0x7;
	mem8[0x4DED] = 0x0;
	mem8[0x4DEE] = 0x5C;
	mem8[0x4DEF] = 0x11;
	mem8[0x4DF0] = 0x9;
	mem8[0x4DF1] = 0x0;
	mem8[0x4DF2] = 0x1C;
	mem8[0x4DF3] = 0x30;
	mem8[0x4DF4] = 0x40;
	mem8[0x4DF5] = 0x11;
	mem8[0x4DF6] = 0xD;
	mem8[0x4DF7] = 0x0;
	mem8[0x4DF8] = 0x5C;
	mem8[0x4DF9] = 0x11;
	mem8[0x4DFA] = 0xF;
	mem8[0x4DFB] = 0x0;
	mem8[0x4DFC] = 0x5C;
	mem8[0x4DFD] = 0x11;
	mem8[0x4DFE] = 0x11;
	mem8[0x4E00] = 0x5C;
	mem8[0x4E01] = 0x11;
	mem8[0x4E02] = 0x17;
	mem8[0x4E04] = 0x5C;
	mem8[0x4E05] = 0x11;
	mem8[0x4E06] = 0x19;
	mem8[0x4E07] = 0x0;
	mem8[0x4E08] = 0x5C;
	mem8[0x4E09] = 0x11;
	mem8[0x4E0A] = 0x13;
	mem8[0x4E0B] = 0x0;
	mem8[0x4E0C] = 0x5C;
	mem8[0x4E0D] = 0x11;
	mem8[0x4E0E] = 0x15;
	mem8[0x4E0F] = 0x0;
	mem8[0x4E10] = 0x7C;
	mem8[0x4E11] = 0x11;
	mem8[0x4E12] = 0x0;
	mem8[0x4E14] = 0x1F;
	mem8[0x4E16] = 0x75;
	mem8[0x4E17] = 0x4E;
	// Sprites
	mem8[0x14CA0] = 0x90;
	mem8[0x14CA3] = 0x0;
	mem8[0x14CB0] = 0x90;
	mem8[0x14CB3] = 0x40;
	mem8[0x14F68] = 0xFC;
	mem8[0x14F69] = 0x28;
	mem8[0x14F6A] = 0x0;
	mem8[0x14F6D] = 0x1;

	kabuki_setup(punisher_decode);
	init_cps1();
}

void cps_state::init_sf2h9()
{
	/* Patch out protection check */
	uint16_t *rom = (uint16_t *)memregion("maincpu")->base();
	rom[0xc0670/2] = 0x4e71;
	init_cps1();
}

void cps_state::init_sf2h13()
{
	uint16_t *rom = (uint16_t *)memregion("maincpu")->base();

	// Fix scroll
	rom[0x1d22a/2] = 0x0120;
	// Fix bg layer
	rom[0x1d270/2] = 0x0166;
	// Fix gfx
	rom[0x1d470/2] = 0x0170;

	// Fix title gfx
	rom[0x21bec/2] = 0x0083;
	rom[0x21cf8/2] = 0x828e;
	rom[0x21cfa/2] = 0x829e;
	rom[0x21cfc/2] = 0x82ae;
	rom[0x21d06/2] = 0x827f;
	rom[0x21d08/2] = 0x828f;
	rom[0x21d0a/2] = 0x829f;
	rom[0x21d0c/2] = 0x82af;
	rom[0x21d16/2] = 0x827e;
	rom[0x21d18/2] = 0x82a0;
	rom[0x21d1a/2] = 0x822c;
	rom[0x21d1c/2] = 0x823c;
	rom[0x21d2a/2] = 0x822d;

	init_cps1();
}

void cps_state::init_sk2h35()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Patch Q sound protection? check
	mem8[0x5A1A] = 0x00;
	mem8[0x5A1B] = 0x67;
	mem8[0x5A1C] = 0x56;
	mem8[0x5A1D] = 0x00;
	mem8[0x5A1E] = 0x7C;
	mem8[0x5A1F] = 0x20;
	mem8[0x5A20] = 0xF1;
	mem8[0x5A21] = 0x00;
	mem8[0x5A22] = 0x00;
	mem8[0x5A23] = 0x80;
	mem8[0x5A24] = 0x28;
	mem8[0x5A25] = 0x4A;
	mem8[0x5A26] = 0x1F;
	mem8[0x5A27] = 0x00;
	mem8[0x5A28] = 0x00;
	mem8[0x5A29] = 0x6A;
	mem8[0x5A40] = 0x5C;
	mem8[0x5A41] = 0x11;
	mem8[0x5A42] = 0x01;
	mem8[0x5A43] = 0x00;
	mem8[0x5A44] = 0x5C;
	mem8[0x5A45] = 0x11;
	mem8[0x5A46] = 0x03;
	mem8[0x5A47] = 0x00;
	mem8[0x5A4A] = 0x07;
	mem8[0x5A4B] = 0x00;
	mem8[0x5A4C] = 0x5C;
	mem8[0x5A4D] = 0x11;
	mem8[0x5A4E] = 0x09;
	mem8[0x5A4F] = 0x00;
	mem8[0x5A50] = 0x5C;
	mem8[0x5A51] = 0x31;
	mem8[0x5A52] = 0x0C;
	mem8[0x5A53] = 0x00;
	mem8[0x5A54] = 0x5C;
	mem8[0x5A55] = 0x11;
	mem8[0x5A56] = 0x0F;
	mem8[0x5A57] = 0x00;
	mem8[0x5A58] = 0x5C;
	mem8[0x5A59] = 0x11;
	mem8[0x72A6] = 0x71;
	mem8[0x72A7] = 0x4E;
	mem8[0x72A8] = 0x71;
	mem8[0x72A9] = 0x4E;
	mem8[0x72AA] = 0x71;
	mem8[0x72AB] = 0x4E;
	mem8[0x72AC] = 0x71;
	mem8[0x72AD] = 0x4E;
	mem8[0x72AE] = 0x71;
	mem8[0x72AF] = 0x4E;
	mem8[0x72B0] = 0x71;
	mem8[0x72B1] = 0x4E;
	mem8[0x72B2] = 0x39;
	mem8[0x72B3] = 0x30;
	mem8[0x72B4] = 0xF1;
	mem8[0x72B5] = 0x00;
	mem8[0x72B6] = 0xFE;
	mem8[0x72B7] = 0x9F;
	mem8[0x72B8] = 0x00;
	mem8[0x72B9] = 0x0C;
	/* enable coin slots 1 and 2 */
	mem8[0x71bc] = 0x0c;
	kabuki_setup(wof_decode);
	init_cps1();
}

void cps_state::init_sk2h1()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Stage Order
	mem8[0x72a6] = 0x00;
	// Disable Sprite Recoding
	mem8[0x5d858] = 0x00;
	mem8[0x5d859] = 0x61;
	mem8[0x5d85a] = 0xe6;
	mem8[0x5d85b] = 0x01;
	mem8[0x5d890] = 0x6d;
	mem8[0x5d891] = 0x0c;
	mem8[0x5d892] = 0x00;
	mem8[0x5d893] = 0x90;
	mem8[0x5d894] = 0xd2;
	mem8[0x5d895] = 0xe3;
	mem8[0x5d8e8] = 0x90;
	mem8[0x5d8e9] = 0x00;
	mem8[0x5d8ea] = 0x00;
	mem8[0x5d8eb] = 0x00;
	mem8[0x5d8f8] = 0x90;
	mem8[0x5d8f9] = 0x00;
	mem8[0x5d8fa] = 0x00;
	mem8[0x5d8fb] = 0x40;
	// Patch protection? check
	mem8[0xf11ec] = 0x71;
	mem8[0xf11ed] = 0x4e;
	mem8[0xf11ee] = 0x71;
	mem8[0xf11ef] = 0x4e;
	init_cps1();
}

void cps_state::init_sk2h3()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Disable Sprite Recoding
	mem8[0x5d858] = 0x00;
	mem8[0x5d859] = 0x61;
	mem8[0x5d85a] = 0xe6;
	mem8[0x5d85b] = 0x01;
	mem8[0x5d890] = 0x6d;
	mem8[0x5d891] = 0x0c;
	mem8[0x5d892] = 0x00;
	mem8[0x5d893] = 0x90;
	mem8[0x5d894] = 0xd2;
	mem8[0x5d895] = 0xe3;
	mem8[0x5d8e8] = 0x90;
	mem8[0x5d8eb] = 0x00;
	mem8[0x5d8f8] = 0x90;

	//Transitions
	//mem8[0x02449] = 0x07; // fixed by above code

	//Protections
	mem8[0x708da] = 0xff;
	mem8[0x708db] = 0xff;
	mem8[0x708dc] = 0xff;
	mem8[0x708dd] = 0xff;
	mem8[0xf11eb] = 0x60;

	//Start at stage 1
	mem8[0x072a6] = 0x00;

	init_cps1();
}

void cps_state::init_sk2h21()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Patch Q sound protection? check
	mem8[0x0554] = 0xb4;
	mem8[0x0555] = 0x54;
	mem8[0x5A50] = 0x5c;
	mem8[0x5A51] = 0x31;
	mem8[0x5A52] = 0x0c;
	mem8[0x5A53] = 0x00;
	mem8[0x5A54] = 0x5c;
	mem8[0x5A55] = 0x11;
	mem8[0x5A56] = 0x0f;
	mem8[0x5A58] = 0x5c;
	mem8[0x5A59] = 0x11;
	mem8[0x5A5A] = 0x11;
	mem8[0x5A5B] = 0x00;
	kabuki_setup(wof_decode);
	init_cps1();
}

void cps_state::init_sk2h22()
{
	uint8_t *mem8 = memregion("maincpu")->base();
	// Protection
	mem8[0xE7AD0] = 0x71;
	mem8[0xE7AD1] = 0x4E;

	// Disable Sprite Recoding
	mem8[0x5de96] = 0x00;
	mem8[0x5de97] = 0x61;
	mem8[0x5de98] = 0xe6;
	mem8[0x5de99] = 0x01;
	mem8[0x5dece] = 0x6d;
	mem8[0x5decf] = 0x0c;
	mem8[0x5ded0] = 0x00;
	mem8[0x5ded1] = 0x90;
	mem8[0x5ded2] = 0xd2;
	mem8[0x5ded3] = 0xe3;
	mem8[0x5df26] = 0x90;
	mem8[0x5df29] = 0x00;
	mem8[0x5df36] = 0x90;

	init_cps1();
}

ROM_START( 3wondrud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "3wondrud.30", 0x00000, 0x20000, CRC(b0953ff4) SHA1(79d0b68948a9b5be8eacd33810ddcf4fa08dbe71) )
	ROM_LOAD16_BYTE( "3wondrud.35", 0x00001, 0x20000, CRC(7695e8c6) SHA1(f78e7cb1098d77ce84d58a0d4509a77f5c483a77) )
	ROM_LOAD16_BYTE( "3wondrud.31", 0x40000, 0x20000, CRC(8cf00a3c) SHA1(dceb5bccf7c96802e7c228ea52f82fbb49388e0d) )
	ROM_LOAD16_BYTE( "3wondrud.36", 0x40001, 0x20000, CRC(b649ad19) SHA1(f91dad60a583a46f80e71bb23bfd051b3ed3fbe5) )
	ROM_LOAD16_BYTE( "rt_28a.9f",   0x80000, 0x20000, CRC(054137c8) SHA1(e4c406e0a32198323a5931093fbaa6836510b8ad) )
	ROM_LOAD16_BYTE( "rt_33a.9h",   0x80001, 0x20000, CRC(7264cb1b) SHA1(b367acb9f6579569321ecaa98a14e29dd775b9db) )
	ROM_LOAD16_BYTE( "rtu_29a.10f", 0xc0000, 0x20000, CRC(37ba3e20) SHA1(a128b1a17639b06a4fd8acffe0357f1dbd1d4fe9) )
	ROM_LOAD16_BYTE( "rtu_34a.10h", 0xc0001, 0x20000, CRC(f99f46c0) SHA1(cda24a6baa3f861e7078fb2fa91328cc1cddc866) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "rt-5m.7a",  0x000000, 0x80000, CRC(86aef804) SHA1(723927ef3bf992d12395c52db051ece7bf57d5e5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-7m.9a",  0x000002, 0x80000, CRC(4f057110) SHA1(b7d35c883a74cf4bfb242d9f15a0e40ed1ec111f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-1m.3a",  0x000004, 0x80000, CRC(902489d0) SHA1(748ba416a8b9343059a3e7d8b93f02162feb1d0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-3m.5a",  0x000006, 0x80000, CRC(e35ce720) SHA1(6c1a87a1f819bdc20408b5a7823cf35a79d34110) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-6m.8a",  0x200000, 0x80000, CRC(13cb0e7c) SHA1(e429d594d9a7ff4cc6306e2796a9d6ad0fa25569) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-8m.10a", 0x200002, 0x80000, CRC(1f055014) SHA1(d64f5be9bb2ef761ca9b2e797dbc3554cf996a79) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-2m.4a",  0x200004, 0x80000, CRC(e9a034f4) SHA1(deb4cb5886705380b57d4fe9b9bf3c032e1d6227) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "rt-4m.6a",  0x200006, 0x80000, CRC(df0eea8b) SHA1(5afa05654cccb0504bd44569d42fd68f08fd172f) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "rt_9.12b",   0x00000, 0x08000, CRC(abfca165) SHA1(428069d3bdc45775854cd0e8abe447f134fe5492) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "rt_18.11c",  0x00000, 0x20000, CRC(26b211ab) SHA1(0ea03fdd9edff41eacfc52aa9e0421c10968356b) )
	ROM_LOAD( "rt_19.12c",  0x20000, 0x20000, CRC(dbe64ad0) SHA1(09f2ad522fe75d7bcca094b8c6696c3733b539d5) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "3wondrud.key", 0x00, 0x80, CRC(5066be6f) SHA1(a514ffb7561b1d563382c4c69e24c81574902081) )
ROM_END

ROM_START( 3wondersha ) // same as 3wondersh except for program roms
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "b01.22",      0x00000, 0x40000, CRC(8eb6b675) SHA1(835a777af57579e80d0800b5e86bed01ee5168a3) )
	ROM_LOAD16_BYTE( "b01.26",      0x00001, 0x40000, CRC(ab2d0699) SHA1(f2d7bb4b94fba398d3d896683264fc6828d1de5c) )
	ROM_LOAD16_BYTE( "b01.23",      0x80000, 0x40000, CRC(74db820f) SHA1(5980998ad3d25e417bb74020a1867207aaa6a0b1) )
	ROM_LOAD16_BYTE( "b01.27",      0x80001, 0x40000, CRC(c75e807b) SHA1(9baacd6183e66c4c655c9e32d1858898434f2b87) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "16.bin",    0x000000, 0x40000, CRC(c997bca2) SHA1(6b6cd9c2fc56690c42a3368cd5e6c98d6bff5b5b) , ROM_SKIP(7) )
	ROMX_LOAD( "6.bin",     0x000001, 0x40000, CRC(3eea321a) SHA1(4368aaf8a532c29f4b950adb2daedd3069d84cf1) , ROM_SKIP(7) )
	ROMX_LOAD( "18.bin",    0x000002, 0x40000, CRC(98acdfd4) SHA1(910dfd6742e166530388c700c0797e692e501f97) , ROM_SKIP(7) )
	ROMX_LOAD( "8.bin",     0x000003, 0x40000, CRC(dc9ca6f9) SHA1(77549e9a128d1b7ca0c4547cdc56f43450d426e0) , ROM_SKIP(7) )
	ROMX_LOAD( "12.bin",    0x000004, 0x40000, CRC(0d8a6007) SHA1(48d61cbd91df01ba4b2f0e80e60375a50ddb065e) , ROM_SKIP(7) )
	ROMX_LOAD( "2.bin",     0x000005, 0x40000, CRC(d75563b9) SHA1(7b7b105b84dc5d7b17838961fdd8be5bac90cbc6) , ROM_SKIP(7) )
	ROMX_LOAD( "14.bin",    0x000006, 0x40000, CRC(84369a28) SHA1(3877186371fe289522133fd99be034b141a974ca) , ROM_SKIP(7) )
	ROMX_LOAD( "4.bin",     0x000007, 0x40000, CRC(d4831578) SHA1(9ff5860f22976e9e4c023946f35e24fde84fe8ea) , ROM_SKIP(7) )
	ROMX_LOAD( "17.bin",    0x200000, 0x40000, CRC(040edff5) SHA1(9747d67b980cc357c6fa732300a84ae55150bc51) , ROM_SKIP(7) )
	ROMX_LOAD( "7.bin",     0x200001, 0x40000, CRC(c7c0468c) SHA1(e7a14cf579b023e8954b7e06aa2337db4f53bedc) , ROM_SKIP(7) )
	ROMX_LOAD( "19.bin",    0x200002, 0x40000, CRC(9fef114f) SHA1(394afb083ce7c46d9a39097d0040f9e18aaab508) , ROM_SKIP(7) )
	ROMX_LOAD( "9.bin",     0x200003, 0x40000, CRC(48cbfba5) SHA1(74047433e50795e29d8299526ae2c424610f0a5e) , ROM_SKIP(7) )
	ROMX_LOAD( "13.bin",    0x200004, 0x40000, CRC(8fc3d7d1) SHA1(e2784e0fccfe062ea8dc440e4a884fc665f4a846) , ROM_SKIP(7) )
	ROMX_LOAD( "3.bin",     0x200005, 0x40000, CRC(c65e9a86) SHA1(359ab1e2dd0fcf38ed9815a6a50294cbeca8223c) , ROM_SKIP(7) )
	ROMX_LOAD( "15.bin",    0x200006, 0x40000, CRC(f239341a) SHA1(b1858f5f7a5d210c5327b84a797ed7e898250596) , ROM_SKIP(7) )
	ROMX_LOAD( "5.bin",     0x200007, 0x40000, CRC(947ac944) SHA1(d962f49ba532fc60209bb3957ff8a456855ef67f) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "rt_9.12b",   0x00000, 0x08000, CRC(abfca165) SHA1(428069d3bdc45775854cd0e8abe447f134fe5492) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "rt_18.11c",  0x00000, 0x20000, CRC(26b211ab) SHA1(0ea03fdd9edff41eacfc52aa9e0421c10968356b) )
	ROM_LOAD( "rt_19.12c",  0x20000, 0x20000, CRC(dbe64ad0) SHA1(09f2ad522fe75d7bcca094b8c6696c3733b539d5) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "3wonders.key", 0x00, 0x80, CRC(4ff53ff9) SHA1(95e1d3a9e69c6f11a11b3eebeccd4ce2d237e350) )
ROM_END

ROM_START( captcoud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP("captcoud.23", 0x000000, 0x80000, CRC(1d338c25) SHA1(4aba7e5a78bf20d887b3493e0d2a83098f877f9f) )
	ROM_LOAD16_WORD_SWAP("captcoud.22", 0x080000, 0x80000, CRC(c5310f13) SHA1(97a3751630f10cf67515200ce435c34fda1d9a52) )
	ROM_LOAD16_BYTE( "ccu_24b.9e",      0x100000, 0x20000, CRC(84ff99b2) SHA1(5b02c91f3d0f8fb46db9596136b683f5a22dc15f) )
	ROM_LOAD16_BYTE( "ccu_28b.9f",      0x100001, 0x20000, CRC(fbcec223) SHA1(daf484baece5b3a11f3dcabb758b8bdd736a1fb6) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "captcoud.key", 0x00, 0x80, CRC(6a4c8ad9) SHA1(56912fc3387cf977e602d3e8dad31b64dadc6b4a) )
ROM_END

ROM_START( captcocn )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_23cn.8f", 0x000000, 0x80000, CRC(a5e73e49) SHA1(7bb75fa0e1122a85a421c50607c0ad57a387783e) )
	ROM_LOAD16_WORD_SWAP( "cc_22cn.7f", 0x080000, 0x80000, CRC(919777c5) SHA1(2bd9b1527e8486ae89ddcdb0694c63c5859080b6) )
	ROM_LOAD16_BYTE( "cc_24cn.9e", 0x100000, 0x20000, CRC(f3d6f147) SHA1(937822148c0f6f295d468024ce7887ee0353e669) )
	ROM_LOAD16_BYTE( "cc_28cn.9f", 0x100001, 0x20000, CRC(f1c9bf8a) SHA1(545f494106ccce6ccbbe6fa042cf0ee6df03e8dc) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",     0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",     0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",     0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",     0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6mcn.7a",   0x200000, 0x80000, CRC(e4282bc0) SHA1(fe6012a8afcaec5747194bedfa73284bb28300a4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8mcn.9a",   0x200002, 0x80000, CRC(8b0ef34c) SHA1(13a696856432b2f345cd2b2059e95179c78bd70a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2mcn.8a",   0x200004, 0x80000, CRC(2d7bee50) SHA1(a25bcfa99c4dda52469f7dc8fec24287c97deb84) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4mcn.10a",   0x200006, 0x80000, CRC(0106bf6a) SHA1(8e23418c58c4ffb8dd4dac93b92b23c406d60a62) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",    0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",    0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",    0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( daimakaib )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "dmjb2.bin", 0x00000, 0x80000, CRC(7d5f9f84) SHA1(b334b3af610892ef4efe4764017659b8541a10c6) )
	ROM_LOAD16_BYTE( "dmjb1.bin", 0x00001, 0x80000, CRC(9b945cc4) SHA1(dfdfabfd8ef06cee6be27350f79c5db4c6ace611) )

	ROM_REGION( 0x300000, "gfx", 0 )
	ROMX_LOAD( "dm_02.4b",  0x000000, 0x20000, CRC(8b98dc48) SHA1(e827881e2ba5cccd907d1692a1945c1b75d46f12) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_01.4a",  0x000001, 0x20000, CRC(80896c33) SHA1(20ffc427c596828005e34cdd8e4efa0d332262e9) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_10.9b",  0x000002, 0x20000, CRC(c2e7d9ef) SHA1(52aae6cf373f8c7150833047be28b74dd5eb5af6) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_09.9a",  0x000003, 0x20000, CRC(c9c4afa5) SHA1(34571e3e49c86b87fa34eefbc5f9fe258aba5f1a) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_18.5e",  0x000004, 0x20000, CRC(1aa0db99) SHA1(69ac302b2f6f0b96f78cb57b0b4cdae464086262) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_17.5c",  0x000005, 0x20000, CRC(dc6ed8ad) SHA1(1ffc4a48a7ff9b542ab6f63a60bea3c1a7a6e63b) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_30.8h",  0x000006, 0x20000, CRC(d9d3f8bd) SHA1(6c6853a384f8d60ca46a0607fd47c76a83700fba) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_29.8f",  0x000007, 0x20000, CRC(49a48796) SHA1(76c18c684dba4aa91ee6caae0f38fe3e1cc50832) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_04.5b",  0x100000, 0x20000, CRC(a4f4f8f0) SHA1(edca0f61b40a18afe279f7007c233064130cfb4f) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_03.5a",  0x100001, 0x20000, CRC(b1033e62) SHA1(547fc281dd9e7a74ac86c3692508c7bde9b6167b) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_12.10b", 0x100002, 0x20000, CRC(10fdd76a) SHA1(aee774d6323292799dff7a30ef9559c92fe5507a) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_11.10a", 0x100003, 0x20000, CRC(9040cb04) SHA1(b32e9056fc20a5162868eade10f3ef5efc167a28) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_20.7e",  0x100004, 0x20000, CRC(281d0b3e) SHA1(70e1813de184ad0ec164145b7b843b5e387494e3) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_19.7c",  0x100005, 0x20000, CRC(2623b52f) SHA1(fc4200924452bfbff687934782398ed345dc0aa0) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_32.9h",  0x100006, 0x20000, CRC(99692344) SHA1(67dc70618568b7c0adcb00a612aaf5501f6c8c0f) , ROM_SKIP(7) )
	ROMX_LOAD( "dm_31.9f",  0x100007, 0x20000, CRC(54acb729) SHA1(d1fca43db36253fd19db4337c49272a6cadff597) , ROM_SKIP(7) )
	ROMX_LOAD( "09.4a",     0x200000, 0x10000, CRC(ae24bb19) SHA1(aa91c6ffe657b878e10e4e930457b530f7bb529b) , ROM_SKIP(7) )
	ROMX_LOAD( "18.7a",     0x200001, 0x10000, CRC(d34e271a) SHA1(55211fc2861dce32951f41624c9c99c09bf3b184) , ROM_SKIP(7) )
	ROMX_LOAD( "13.4e",     0x200002, 0x10000, CRC(3f70dd37) SHA1(9ecb4dec9d131e9fca15ded7d71986a9fcb62c19) , ROM_SKIP(7) )
	ROMX_LOAD( "22.7e",     0x200003, 0x10000, CRC(7e69e2e6) SHA1(4e0b4d2474beaa5c869c8f1a91893c79ac6e7f39) , ROM_SKIP(7) )
	ROMX_LOAD( "11.4c",     0x200004, 0x10000, CRC(37c9b6c6) SHA1(b2bb82537e335339846dbf9588cfacfdbdd75ee6) , ROM_SKIP(7) )
	ROMX_LOAD( "20.7c",     0x200005, 0x10000, CRC(2f1345b4) SHA1(14c450abcf9defa29c6f48e5ffd0b9d1e4a66a1d) , ROM_SKIP(7) )
	ROMX_LOAD( "15.4g",     0x200006, 0x10000, CRC(3c2a212a) SHA1(f8fa0e0e2d09ea37c54d1c2493752b4e97e3f534) , ROM_SKIP(7) )
	ROMX_LOAD( "24.7g",     0x200007, 0x10000, CRC(889aac05) SHA1(9301dcecee699e7f7672bb498122e1f4831ce536) , ROM_SKIP(7) )
	ROMX_LOAD( "10.4b",     0x280000, 0x10000, CRC(bcc0f28c) SHA1(02f587aa4ae71631f27b0e3aaf1829cdded1bdc2) , ROM_SKIP(7) )
	ROMX_LOAD( "19.7b",     0x280001, 0x10000, CRC(2a40166a) SHA1(dc4e75d7ed87ae5386d721a09113bba364740465) , ROM_SKIP(7) )
	ROMX_LOAD( "14.4f",     0x280002, 0x10000, CRC(20f85c03) SHA1(86385139a9b42270aade758bfe338525936f5671) , ROM_SKIP(7) )
	ROMX_LOAD( "23.7f",     0x280003, 0x10000, CRC(8426144b) SHA1(2dbf9625413b302fcdad5bef8733a9dfbfaead52) , ROM_SKIP(7) )
	ROMX_LOAD( "12.4d",     0x280004, 0x10000, CRC(da088d61) SHA1(67229eff2827a42af97a60ceb252e132e7f307bc) , ROM_SKIP(7) )
	ROMX_LOAD( "21.7d",     0x280005, 0x10000, CRC(17e11df0) SHA1(42fb15e9300b07fc5f4bc21744484869859b130c) , ROM_SKIP(7) )
	ROMX_LOAD( "16.4h",     0x280006, 0x10000, CRC(f187ba1c) SHA1(6d9441d04ecef2a9d9c7a2cc7781acd7904c2061) , ROM_SKIP(7) )
	ROMX_LOAD( "25.7h",     0x280007, 0x10000, CRC(29f79c78) SHA1(26000a58454a06c3016f99ebc3a79c52911a7070) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "26.10a",     0x00000, 0x08000, CRC(3692f6e5) SHA1(61b8438d60a39b4cf5062dff0a53228e8a4e4b5f) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", ROMREGION_ERASEFF ) // to keep validation quiet

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "daimakb.key", 0x00, 0x80, CRC(c72cad61) SHA1(9036e06c84ff9189a83acd50a703fb6560ce5e98) )
ROM_END

ROM_START( dinoh ) //dino99p
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cda_23h.rom",  0x000000, 0x80000, CRC(8e2a9cf0) SHA1(01111582e579bd3b43b52d0e0c445c32fe5e053b) )
	ROM_LOAD16_WORD_SWAP( "cda_22h.rom",  0x080000, 0x80000, CRC(f72cd219) SHA1(a3f580bd328b54d2546ae7e94262c1a706d27172) )
	ROM_LOAD16_WORD_SWAP( "cda_21h.rom",  0x100000, 0x80000, CRC(bc275b76) SHA1(1f7f7533b4ccb511dc479f531d9d6740d3ca6712) )
	ROM_LOAD16_WORD_SWAP( "cda_20h.rom",  0x180000, 0x80000, CRC(8987c975) SHA1(3fd856805d627f855f72acc7aacc2e8ecf0f12bd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",   0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",   0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",   0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",   0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",   0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",   0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",   0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a",  0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

ROM_START( dinoha )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "kl2-r1.800",  0x080000, 0x080000, CRC(4c70dca7) SHA1(2e7a10c90924e0f87903eddb04313f61233a998f) )
	ROM_CONTINUE(               0x000000, 0x080000 )
	ROM_LOAD16_WORD_SWAP( "kl2-l2.800",  0x180000, 0x080000, CRC(c6ae7338) SHA1(4b8543cf1ac89ae95fe63e6d81c87d2bda52da69) )
	ROM_CONTINUE(               0x100000, 0x080000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-a.160",   0x000000, 0x80000, CRC(7e4f9fb3) SHA1(b985d925e0fb799cdf0a671e4800961d9872cd8f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "cd-b.160",   0x000002, 0x80000, CRC(89532d85) SHA1(6743c4d9b4407421416c13878b8a1fae097dd7a7), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

ROM_START( dinotpic )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cd-d.800",  0x000000, 0x100000, CRC(2a7b2915) SHA1(817d24c5206a60c4d93affffc9bd5a72abccbb01) )
	ROM_LOAD16_WORD_SWAP( "cd-e.800",  0x100000, 0x100000, CRC(e8370226) SHA1(9c6915ad9e48ccd2020fcad58ec56e6f7cd0c25c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-a.160",   0x000000, 0x80000, CRC(7e4f9fb3) SHA1(b985d925e0fb799cdf0a671e4800961d9872cd8f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "cd-b.160",   0x000002, 0x80000, CRC(89532d85) SHA1(6743c4d9b4407421416c13878b8a1fae097dd7a7), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinob.key", 0x00, 0x80, CRC(171140c4) SHA1(d1db4e37e22fa6ae03c2bca4fdb698399d98c15f) )
ROM_END

ROM_START( dinohc )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "hc.23",  0x000000, 0x80000, CRC(cecf4b12) SHA1(75f13fe91442b7c044e58a37d6e7b5bf05150be5) )
	ROM_LOAD16_WORD_SWAP( "hc.22",  0x080000, 0x80000, CRC(07eeb238) SHA1(b217625839108b826b3955ad675ab8ccd3aa424c) )
	ROM_LOAD16_WORD_SWAP( "hc.21",  0x100000, 0x80000, CRC(3bc3d57a) SHA1(cca8101d6171472f4f4c506aa0e3d789e5cbe785) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",   0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",   0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",   0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",   0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",   0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",   0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",   0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a",  0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(              0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",     0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",     0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinoh.key", 0x00, 0x80, CRC(67862673) SHA1(9ae7446231da7fd6355e1f22ac3fb974c3775600) )
ROM_END

ROM_START( dinopic4 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "cad_28",   0x000000, 0x040000, CRC(97dc3d86) SHA1(8dbe9dab5682933b3ea2bfcd066f5f4503aad009) )
	ROM_LOAD16_BYTE( "cad_32",   0x000001, 0x040000, CRC(200a594f) SHA1(125bbf0f1cdc8740293cc3b73ac4bf82af24c0d5) )
	ROM_LOAD16_BYTE( "cad_29",   0x080000, 0x040000, CRC(302303c4) SHA1(42427215357f670d2943a8f09a2288cd4aacd14b) )
	ROM_LOAD16_BYTE( "cad_33",   0x080001, 0x040000, CRC(5bf6deda) SHA1(278f56a10db0f5975ac9ecc7b6e121c2f1dbfc94) )
	ROM_LOAD16_BYTE( "cad_31",   0x100000, 0x020000, CRC(f0110c8a) SHA1(eee714439a3802168c2cece91ed0e1e6ab630652) )
	ROM_LOAD16_BYTE( "cad_35",   0x100001, 0x020000, CRC(fbcf4314) SHA1(a59a1d867abea5216367220d8c9d005f451c9d88) )
	ROM_LOAD16_BYTE( "cad_30",   0x140000, 0x020000, CRC(bbcafc3b) SHA1(52ff5928b1da862813ef150ea77ac59cff82df5b) )
	ROM_LOAD16_BYTE( "cad_34",   0x140001, 0x020000, CRC(481369b8) SHA1(065b5f6b3d2f337def183c3ab5f0ef8c21d0c849) )
	ROM_FILL(0xbb3b8,1,0x4e) // kill protection
	ROM_FILL(0xbb3b9,1,0x71)

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cad_24",   0x000000, 0x040000, CRC(e59e0066) SHA1(de8868ac7c9323c9ce4a22d610f25e8932e09218), ROM_SKIP(7) )
	ROMX_LOAD( "cad_14",   0x000001, 0x040000, CRC(79b60fc5) SHA1(12519904ca235661a103f01918b8e713abbfb6f4), ROM_SKIP(7) )
	ROMX_LOAD( "cad_26",   0x000002, 0x040000, CRC(2db8cb57) SHA1(e4acc9e94067e3567e4a4b6c8439d5cc51cfbae0), ROM_SKIP(7) )
	ROMX_LOAD( "cad_16",   0x000003, 0x040000, CRC(569e5cf0) SHA1(c4b61d8c79d5d1dfd4079e57f444f7ac89a26422), ROM_SKIP(7) )
	ROMX_LOAD( "cad_20",   0x000004, 0x040000, CRC(779bffb2) SHA1(e591845761bf637d36764d84f7af84b1e3594f7b), ROM_SKIP(7) )
	ROMX_LOAD( "cad_10",   0x000005, 0x040000, CRC(9d5b2ed4) SHA1(4958fc59ca6dd45e82a1a9ea68ae40450f67badc), ROM_SKIP(7) )
	ROMX_LOAD( "cad_22",   0x000006, 0x040000, CRC(b58c4246) SHA1(fc3e705d025372edb3ded8840ff0157398897b8d), ROM_SKIP(7) )
	ROMX_LOAD( "cad_12",   0x000007, 0x040000, CRC(33ed501d) SHA1(f6f80e802444101bfcb38b1a27ed6a9b9e32ba3c), ROM_SKIP(7) )
	ROMX_LOAD( "cad_25",   0x200000, 0x040000, CRC(900b82b7) SHA1(c9b422daccaf793cd8fae5e3f88cbdfc757cc00b), ROM_SKIP(7) )
	ROMX_LOAD( "cad_15",   0x200001, 0x040000, CRC(aa54f07c) SHA1(b1a71d2efefec4fdf1eff61404d385d9f7d31468), ROM_SKIP(7) )
	ROMX_LOAD( "cad_27",   0x200002, 0x040000, CRC(27492fde) SHA1(2befbf43c316db072f63d771202c8e77b6e228ff), ROM_SKIP(7) )
	ROMX_LOAD( "cad_17",   0x200003, 0x040000, CRC(920df2fd) SHA1(7ad467e6ecf59a6b737ee5369ffcc4a5d203ea48), ROM_SKIP(7) )
	ROMX_LOAD( "cad_21",   0x200004, 0x040000, CRC(d65ee299) SHA1(bfad1473a05f4152dedefb5b8d10e7d27b4dc18a), ROM_SKIP(7) )
	ROMX_LOAD( "cad_11",   0x200005, 0x040000, CRC(8594b5e8) SHA1(10aca27488652da3c8421a8ea5acdfa7ec596e93), ROM_SKIP(7) )
	ROMX_LOAD( "cad_23",   0x200006, 0x040000, CRC(f07c16f2) SHA1(422ae1bcfe0a6704e374800d2af8cda69bd03138), ROM_SKIP(7) )
	ROMX_LOAD( "cad_13",   0x200007, 0x040000, CRC(07a564b4) SHA1(7be9f1a52eaa523a386d91d12ec0ddca716c363c), ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 ) // first and 2nd half identical
	ROM_LOAD( "cad_09",    0x00000, 0x08000, CRC(46546432) SHA1(c37527f663713464f837295625345d485855122e) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cad_18",    0x00000, 0x20000, CRC(bd12c2ce) SHA1(4bb4d854be7aff2516241ba56f431a5464854be2) )
	ROM_LOAD( "cad_19",    0x20000, 0x20000, CRC(9233de5a) SHA1(c20f596648963ddf62a4452741cc9ad8b11f2ca2) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinod )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23d.23",    0x000000, 0x80000, CRC(c871b733) SHA1(0c2030a9ca0be8b14edbc4f2ae44184ab81b5e03) )
	ROM_LOAD16_WORD_SWAP( "cde_22d.22",    0x080000, 0x80000, CRC(b503e1ad) SHA1(73e53061b01940a9deb13c0ff5d874b4a8380f15) )
	ROM_LOAD16_WORD_SWAP( "cde_21a.6f",   0x100000, 0x80000, CRC(66d23de2) SHA1(19b8a365f630411d524d055459020f4c8cf930f1) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",   0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",   0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",   0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",   0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",   0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",   0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",   0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a",   0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",       0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",      0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",      0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",      0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",      0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dinod.key", 0x00, 0x80, CRC(6c097c88) SHA1(a8170ace800e96ec29fbef22f5fdc45c7f5b516b) )
ROM_END

ROM_START( mercscn )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "so2_36cn.12f", 0x00000, 0x20000, CRC(d4d34a1f) SHA1(c1543578f45e45d35fd761ae1abf3f8e5afc8e9b) )
	ROM_LOAD16_BYTE( "so2_42cn.12h", 0x00001, 0x20000, CRC(184d7739) SHA1(c70f5613336535b3ed7efe7120fd167865ca54cc) )
	ROM_LOAD16_BYTE( "so2_31e.12f", 0x40000, 0x20000, CRC(51204d36) SHA1(af288fc369d092f38ea73be967705aacade06f28) )
	ROM_LOAD16_BYTE( "so2_36e.12h", 0x40001, 0x20000, CRC(9cfba8b4) SHA1(df8ee5e3a68f056f68f096c46fdb548f63d29446) )
	ROM_LOAD16_BYTE( "so2_34.10f", 0x80000, 0x20000, CRC(b8dae95f) SHA1(2db4a20afd40b772a16f1bee999a0b82d3379ac7) )
	ROM_LOAD16_BYTE( "so2_40.10h", 0x80001, 0x20000, CRC(de37771c) SHA1(45e1e2ef4e46dbe8881e809d700fdd3d06a03c92) )
	ROM_LOAD16_BYTE( "so2_35cn.11f", 0xc0000, 0x20000, CRC(1e84d605) SHA1(9b1cdcc998d0624a158e14270c2785c5bfb250e4) )
	ROM_LOAD16_BYTE( "so2_41cn.11h", 0xc0001, 0x20000, CRC(831496b2) SHA1(811e3f300aa0f93a89a07e5ee9e419a73cba7395) )

	ROM_REGION( 0x300000, "gfx", 0 )
	ROMX_LOAD( "so2_09cn.4b",  0x000000, 0x20000, CRC(855d7524) SHA1(47b7a1aaa0833da56a4ce3f2e7101b998532f797) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_01cn.4a",  0x000001, 0x20000, CRC(a44d4196) SHA1(0e722802aacbd872eb94b1f1136e83b2d738b6e3) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_13cn.9b",  0x000002, 0x20000, CRC(8ba956f0) SHA1(9101ea35734cf4ebad3f7f862c4212d5e19ffc6f) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_05cn.9a",  0x000003, 0x20000, CRC(dfc0ccaa) SHA1(bffbef3575871174ca619a55b7eb83e5f06864fd) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_24cn.5e",  0x000004, 0x20000, CRC(94e7a3f2) SHA1(78ae47ba736665388a3f2fe073068872794d14a6) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_17cn.5c",  0x000005, 0x20000, CRC(723bd58b) SHA1(f8e772acba8421ac0f89b88a529b68c950d80901) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_38cn.8h",  0x000006, 0x20000, CRC(3e5d7dd0) SHA1(f8b138ad295229327f8198e5b42fe784349c8f2c) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_32cn.8f",  0x000007, 0x20000, CRC(fea1e81c) SHA1(6bb5096b42898991326075ddd71861d3b7fefdab) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_10.5b",  0x100000, 0x20000, CRC(2f871714) SHA1(8a39f120e3f50fc9a7e6cee659260b2f823fb0e0) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_02.5a",  0x100001, 0x20000, CRC(b4b2a0b7) SHA1(ee42ed3de9021e8d08d6c7115f2de73476b93452) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_14.10b", 0x100002, 0x20000, CRC(737a744b) SHA1(8e1477a67862f7c0c598d3d1a1f633946e7ab31b) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_06.10a", 0x100003, 0x20000, CRC(9d756f51) SHA1(4e9773ee25f6a952fb4f541d37e5e46e4089fd07) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_25.7e",  0x100004, 0x20000, CRC(6d0e05d6) SHA1(47cbec235bd4b250db007218dc357101ae453d1a) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_18.7c",  0x100005, 0x20000, CRC(96f61f4e) SHA1(954334bd8c2d2b02175de60d6a181a23e723d040) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_39.9h",  0x100006, 0x20000, CRC(d52ba336) SHA1(49550d316e575a4e64ea6a5f769f3cd716be6df5) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_33.9f",  0x100007, 0x20000, CRC(39b90d25) SHA1(1089cca168a4abeb398fa93eddd4d9fff70d5db5) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_11cn.7b",  0x200000, 0x20000, CRC(89322061) SHA1(da6f684125c0a3803aa83ffb08e984df90161848) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_03cn.7a",  0x200001, 0x20000, CRC(55ab0bde) SHA1(96f4df896f4500e7dab59956ad3deae91601241e) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_15cn.11b", 0x200002, 0x20000, CRC(542ecd0e) SHA1(f76e07eb19e1bda0dd3e079167d9f6afb0e6f34b) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_07cn.11a", 0x200003, 0x20000, CRC(db87495b) SHA1(49d67ea8995d0ed0d22e4df206505ebed5b72909) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_26cn.8e",  0x200004, 0x20000, CRC(7b07ea2a) SHA1(3c0f3a7302d32dc1dabd3d66df1d5de2f3d767dc) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_19cn.8c",  0x200005, 0x20000, CRC(690310cc) SHA1(bf8d68fd375bb3ca14114d44911bf962e490babb) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_28cn.10e", 0x200006, 0x20000, CRC(323e586e) SHA1(4ff383f28be69fccbe77aa8f928ac5b31089780d) , ROM_SKIP(7) )
	ROMX_LOAD( "so2_21cn.10c", 0x200007, 0x20000, CRC(cb355a66) SHA1(84fc6b3815bed89a1d029a38d0cae0029025447c) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "so2_09.12b",  0x00000, 0x08000, CRC(d09d7c7a) SHA1(8e8532be08818c855d9c3ce45716eb07cfab5767) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "so2_18.11c",  0x00000, 0x20000, CRC(bbea1643) SHA1(d43d68a120550067bf0b181f88687ad230cd7908) )
	ROM_LOAD( "so2_19.12c",  0x20000, 0x20000, CRC(ac58aa71) SHA1(93102272e358bc49d3936302efdc5bb68df84d68) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "mercs.key", 0x00, 0x80, CRC(b0f59dee) SHA1(744e4239ddbfdc6d1b53dc1bd49a34df422c8886) )
ROM_END

ROM_START( pnicku )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pnij_36.12f",  0x00000, 0x20000, CRC(2d4ffb2b) SHA1(6e49cf89a36834fd1de8b4b860fe66f3d7d67a84) )
	ROM_LOAD16_BYTE( "pnicku.42",    0x00001, 0x20000, CRC(22d20227) SHA1(a103c9b1f6134c529405bd258da9f601c1459c47) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "pnij_09.4b",  0x000000, 0x20000, CRC(48177b0a) SHA1(eba5de6cd9bb0c4ad76a13bddc9cdeb2e4380122) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_01.4a",  0x000001, 0x20000, CRC(01a0f311) SHA1(9bcd8716f90ccd410543ffcdc5c2916077b8d4c3) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_13.9b",  0x000002, 0x20000, CRC(406451b0) SHA1(5a7a7fecba7de8b8cf4a284b2ae7adae901623f6) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_05.9a",  0x000003, 0x20000, CRC(8c515dc0) SHA1(aa1e13cf9e7cf0458bb5c4332b1ea73034f9a874) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_26.5e",  0x000004, 0x20000, CRC(e2af981e) SHA1(3c2b28b4a4d457aa94a760dfca0181a9f050c319) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_18.5c",  0x000005, 0x20000, CRC(f17a0e56) SHA1(7c89aca230f176e12f995892f9d1bce22c57fbdf) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_38.8h",  0x000006, 0x20000, CRC(eb75bd8c) SHA1(2129460e06eb64019fc5f7eab6334ff43229b995) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_32.8f",  0x000007, 0x20000, CRC(84560bef) SHA1(9e94ae434b50ecf82781080e11d0c4741e992d0d) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_10.5b",  0x100000, 0x20000, CRC(c2acc171) SHA1(7c86db3f2acca1252d403c5f12c871d0357fa109) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_02.5a",  0x100001, 0x20000, CRC(0e21fc33) SHA1(c4a29d45c4257c8871038d3c9b13140e874db0c1) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_14.10b", 0x100002, 0x20000, CRC(7fe59b19) SHA1(a273b8b8fbfd5d31d25479a9ede09ce35e1cc873) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_06.10a", 0x100003, 0x20000, CRC(79f4bfe3) SHA1(bc17cc1c8535e3d202588893713926b6c06f92fd) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_27.7e",  0x100004, 0x20000, CRC(83d5cb0e) SHA1(44c93fa5eedcafc8dc6d88ee827c6cadc9c671f0) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_19.7c",  0x100005, 0x20000, CRC(af08b230) SHA1(a3b5b3013012efa1860699648518f8d8031c5f30) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_39.9h",  0x100006, 0x20000, CRC(70fbe579) SHA1(b5b7ed5588ecd884b20dd50bfc5385a9af03c5d8) , ROM_SKIP(7) )
	ROMX_LOAD( "pnij_33.9f",  0x100007, 0x20000, CRC(3ed2c680) SHA1(0afe84d8d89f8d45afc79f6172337e622e29a8a2) , ROM_SKIP(7) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "pnij_17.13b",  0x00000, 0x08000, CRC(e86f787a) SHA1(de04cbe89c655faf04afe169bfd9913049ccc4a8) )
	ROM_CONTINUE(             0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "pnij_24.12c",  0x00000, 0x20000, CRC(5092257d) SHA1(95dc9d10940653b2fb37baf5c1ed27145b02104e) )
	ROM_LOAD( "pnij_25.13c",  0x20000, 0x20000, CRC(22109aaa) SHA1(cf21e75674d81b2daae2083d02f9f4b6e52722c6) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "pnickj.key", 0x00, 0x80, CRC(38afadc4) SHA1(05b49635f99e7cb97a99b9666239d68154cb3641) )
ROM_END

ROM_START( punisherud1 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE ( "psud1_26.11e", 0x000000, 0x20000, CRC(f820e620) SHA1(7c2e55b4dc7aaf27badceafd7bde483f33676351) )
	ROM_LOAD16_BYTE ( "psud1_30.11f", 0x000001, 0x20000, CRC(90afc70a) SHA1(73d5325a482becf46ef75456134242db7f1a31f8) )
	ROM_LOAD16_BYTE ( "psu_27.12e",   0x040000, 0x20000, CRC(61c960a1) SHA1(f8fe651283cc1f138d013cab65b833505de6df9f) )
	ROM_LOAD16_BYTE ( "psud1_31.12f", 0x040001, 0x20000, CRC(e1239351) SHA1(7437a5e93ed72b8a52292aeb71c678e1462c8578) )
	ROM_LOAD16_BYTE ( "psud1_24.9e",  0x080000, 0x20000, CRC(22ef4de9) SHA1(358acdce233182280e5eb77da178ec0f08beca7f) )
	ROM_LOAD16_BYTE ( "psud1_28.9f",  0x080001, 0x20000, CRC(e45f5b6d) SHA1(daf25f24f8955387086acd337b19dfea5507adb8) )
	ROM_LOAD16_BYTE ( "psu_25.10e",   0x0c0000, 0x20000, CRC(c51acc94) SHA1(34ffd6392914e3e67d7d0804215bd1193846b554) )
	ROM_LOAD16_BYTE ( "psu_29.10f",   0x0c0001, 0x20000, CRC(52dce1ca) SHA1(45277abe34feacdcaedaec56f513b7437d4260e9) )
	ROM_LOAD16_WORD_SWAP( "ps_21.6f", 0x100000, 0x80000, CRC(8affa5a9) SHA1(268760b83b1723ff50a019ec51ef7af2e49935bf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m.3a",  0x000000, 0x80000, CRC(77b7ccab) SHA1(e08e5d55a79e4c0c8ca819d6d7d2a14f753c6ec3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m.5a",  0x000002, 0x80000, CRC(0122720b) SHA1(5f0d3097e097f64106048156fbb0d343fe78fffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m.4a",  0x000004, 0x80000, CRC(64fa58d4) SHA1(d4a774285ed15273195b6b26d2965ce370e54e73) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m.6a",  0x000006, 0x80000, CRC(60da42c8) SHA1(95eec4a58d9628a2d9764951dd8dc11e4860a899) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisherud1.key", 0x00, 0x80, CRC(c22c07f9) SHA1(b726dfed90c288ee71ab6d6035b0efcba1f18f6a) )
ROM_END

ROM_START( punisherud2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "psud2.23", 0x000000, 0x80000, CRC(019efb28) SHA1(1790db51ce7cd1281932359de6e4e1e046db0369) )
	ROM_LOAD16_WORD_SWAP( "psud2.22", 0x080000, 0x80000, CRC(c0110a4e) SHA1(43f6086634c332a58d95b0b51995ba1ab8ed1367) )
	ROM_LOAD16_WORD_SWAP( "ps_21.6f", 0x100000, 0x80000, CRC(8affa5a9) SHA1(268760b83b1723ff50a019ec51ef7af2e49935bf) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m.3a",  0x000000, 0x80000, CRC(77b7ccab) SHA1(e08e5d55a79e4c0c8ca819d6d7d2a14f753c6ec3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m.5a",  0x000002, 0x80000, CRC(0122720b) SHA1(5f0d3097e097f64106048156fbb0d343fe78fffa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m.4a",  0x000004, 0x80000, CRC(64fa58d4) SHA1(d4a774285ed15273195b6b26d2965ce370e54e73) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m.6a",  0x000006, 0x80000, CRC(60da42c8) SHA1(95eec4a58d9628a2d9764951dd8dc11e4860a899) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m.7a",  0x200000, 0x80000, CRC(c54ea839) SHA1(0733f37329edd9d0cace1319a7544b40aa7ecb0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m.9a",  0x200002, 0x80000, CRC(04c5acbd) SHA1(fddc94b0f36d4d22d7c357856ae15b7514c342d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m.8a",  0x200004, 0x80000, CRC(a544f4cc) SHA1(9552df8934ba25f19a22f2e07783712d8c8ef03c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m.10a", 0x200006, 0x80000, CRC(8f02f436) SHA1(a2f0ebb7e9593469c7b843f8962a66f3d77f79e5) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisherud1.key", 0x00, 0x80, CRC(c22c07f9) SHA1(b726dfed90c288ee71ab6d6035b0efcba1f18f6a) )
ROM_END

ROM_START( punisherb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "3.bin",  0x000001, 0x80000, CRC(8c2593ac) SHA1(4261bc72b96c3a5690df35c5d8b71524765693d9) )
	ROM_LOAD16_BYTE( "5.bin",  0x000000, 0x80000, CRC(c3151563) SHA1(61d3a20c25fea8a94ae6e473a87c21968867cba0) )
	ROM_LOAD16_BYTE( "2.bin",  0x100001, 0x80000, CRC(d7b13f39) SHA1(eb7cd92b44fdef3b72672b0be6786c526421b627) )
	ROM_LOAD16_BYTE( "4.bin",  0x100000, 0x80000, CRC(665a5485) SHA1(c07920d110ca9c35f6cbff94a6a889c17300f994) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "9.bin",   0x000000, 0x40000, CRC(9b9a887a) SHA1(8805b36fc18837bd7c64c751b435d72b763b2235), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x000004, 0x40000 )
	ROMX_LOAD( "8.bin",   0x000001, 0x40000, CRC(2b94287a) SHA1(815d88e66f537e17550fc0483616f02f7126bfb1), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x000005, 0x40000 )
	ROMX_LOAD( "7.bin",   0x000002, 0x40000, CRC(e9bd74f5) SHA1(8ed7098c69d1c70093c99956bf82e532bd6fc7ac), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x000006, 0x40000 )
	ROMX_LOAD( "6.bin",   0x000003, 0x40000, CRC(a5e1c8a4) SHA1(3596265a45cf6bbf16c623f0fce7cdc65f9338ad), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x000007, 0x40000 )
	ROMX_LOAD( "13.bin",  0x200000, 0x40000, CRC(6d75a193) SHA1(6c5a89517926d7ba4a925a3df800d4bdb8a6938d), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x200004, 0x40000 )
	ROMX_LOAD( "12.bin",  0x200001, 0x40000, CRC(a3c205c1) SHA1(6317cc49434dbbb9a249ddd4b50bd791803b3ebe), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x200005, 0x40000 )
	ROMX_LOAD( "11.bin",  0x200002, 0x40000, CRC(22f2ec92) SHA1(9186bfc5db71dc5b099c9a985e8fdd5710772d1c), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x200006, 0x40000 )
	ROMX_LOAD( "10.bin",  0x200003, 0x40000, CRC(763974c9) SHA1(f9b93c7cf0cb8c212fc21c57c85459b7d2e4e2fd), ROM_GROUPBYTE | ROM_SKIP(7) )
	ROM_CONTINUE(              0x200007, 0x40000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",       0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",      0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",      0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",      0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",      0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisherb.key", 0x00, 0x80, CRC(e1219963) SHA1(ba508a09095e9a37018a5a8c3a624713d7684582) )
ROM_END

ROM_START( sf2mega2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf3a-1.040", 0x000000, 0x80000, CRC(9e6d058a) SHA1(8c9adca7b65dc929c325c0a62304d24dc0902c08) )
	ROM_LOAD16_BYTE( "sf3a-3.040", 0x000001, 0x80000, CRC(518d8404) SHA1(635d8ac07126caf3c623d1f28aad38c5bc4c4bae) )
	ROM_LOAD16_BYTE( "sf3a-2", 0x100000, 0x20000, CRC(fca4fc1e) SHA1(2b05d67443af099f95ef50f5e25d7a74b957e7a5) )
	ROM_LOAD16_BYTE( "sf3a-4", 0x100001, 0x20000, CRC(cfdd6f54) SHA1(2aa3f5a7b36930185382c64712cc0cfceb6f1ab3) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2amf5 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sfu9-1.040", 0x000000, 0x80000, CRC(95306baf) SHA1(471d1578607ae1090aa46cb111a8c2745d1fd47b) )
	ROM_LOAD16_BYTE( "sfu9-3.040", 0x000001, 0x80000, CRC(21024d5f) SHA1(986b3910ce749f4ad42e1f86537a8fc3f0f3f867) )
	ROM_LOAD16_BYTE( "t-4.u54", 0x100000, 0x40000, CRC(0b3fe5dd) SHA1(9b66cb867da61595f53d1c9e6b48c6bb7e06e1e0) )
	ROM_LOAD16_BYTE( "t-3.u38", 0x100001, 0x40000, CRC(dbee7b18) SHA1(e56af12fc9d30e92d37e688ff621ea09abb94b53) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2cejabl )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sfu7-1.040", 0x000000, 0x80000, CRC(866a9b31) SHA1(92f89084293b69a9d5cd8d282ffaaca0739f1b03) )
	ROM_LOAD16_BYTE( "sfu7-3.040", 0x000001, 0x80000, CRC(f3a45593) SHA1(0ba0d05f904ac17cd34c0a7c9dd0a20759ff4e78) )
	ROM_LOAD16_BYTE( "u221.1m", 0x100000, 0x20000, CRC(d1707134) SHA1(5bfdf7bc57bdb85183647ebb175346070dd102ee) )
	ROM_LOAD16_BYTE( "u195.1m", 0x100001, 0x20000, CRC(cd1d5666) SHA1(8befd2c324eb29bdad6fc8fb2554cdfaf9808f9b) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2h11.key", 0x00, 0x80, CRC(822729a2) SHA1(acaadef38fd97dba215c13688061cee87d877c19) )
ROM_END

ROM_START( sf2m12 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sfu8-1.040", 0x000000, 0x80000, CRC(10ec67fe) SHA1(9eb30a0f64bf29028f89f9af74cb9d840ed197e2) )
	ROM_LOAD16_BYTE( "sfu8-3.040", 0x000001, 0x80000, CRC(92eb3a1c) SHA1(0ee294c8b82b100f98da697562f9644b71cabcdd) )
	ROM_LOAD16_BYTE( "u221t.1m", 0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "sfu8-4.010", 0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2h11.key", 0x00, 0x80, CRC(822729a2) SHA1(acaadef38fd97dba215c13688061cee87d877c19) )
ROM_END

ROM_START( sf2m13 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "222-040.13",   0x000000, 0x80000, CRC(ec6f5cb3) SHA1(24b3fc88a08a721985b053120997090bc394bc8e) )
	ROM_LOAD16_BYTE( "196-040.13",   0x000001, 0x80000, CRC(0e9ac52b) SHA1(2c5faf7d8b598f2110f389aefa1a02e2281382ee) )
	ROM_LOAD16_BYTE( "221-010.13",   0x100000, 0x20000, CRC(8226c11c) SHA1(9588bd64e338901394805aca8a234f880674dc60) )
	ROM_LOAD16_BYTE( "sfu8-4.010",   0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s2t_10.bin",   0x400000, 0x80000, CRC(3c042686) SHA1(307e1ca8ad0b11f3265b7e5467ba4c90f90ec97f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s2t_11.bin",   0x400002, 0x80000, CRC(8b7e7183) SHA1(c8eaedfbddbf0b83311d2dbb9e19a1efef0dffa9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s2t_12.bin",   0x400004, 0x80000, CRC(293c888c) SHA1(5992ea9aa90fdd8b9dacca9d2a1fdaf25ac2cb65) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s2t_13.bin",   0x400006, 0x80000, CRC(842b35a4) SHA1(35864a140a0c8d76501e69b2e01bc4ad76f27909) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2rbpr )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD( "sf2rbpr.23",       0x000000, 0x80000, CRC(450532b0) SHA1(14d5ff44ce97247ef4c42147157856d16c5fb4b8) )
	ROM_LOAD16_WORD( "sf2rbpr.22",       0x080000, 0x80000, CRC(20fd1382) SHA1(7b32b295ac4e61a7f7ae395d9dfc10d80747d833) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2amf6 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "u222",         0x000000, 0x80000, CRC(03991fba) SHA1(6c42bf15248640fdb3e98fb01b0a870649deb410) )
	ROM_LOAD16_BYTE( "4.amf",        0x000001, 0x80000, CRC(39f15a1e) SHA1(901c4fea76bf5bff7330ed07ffde54cdccdaa680) )
	ROM_LOAD16_BYTE( "u221.rom",     0x100000, 0x20000, CRC(64e6e091) SHA1(32ec05db955e538d4ada26d19ee50926f74b684f) )
	ROM_LOAD16_BYTE( "u195.rom",     0x100001, 0x20000, CRC(c95e4443) SHA1(28417dee9ccdfa65b0f4a92aa29b90279fe8cd85) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )
	// These map over 0x400000 to 0x4FFFFF
	ROMX_LOAD( "stf2th-10",  0x400000, 0x20000, CRC(84427d1b) SHA1(f988a2b53c8cc46eeb8032084f24966a539b3734) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-12",  0x400002, 0x20000, CRC(55bc790c) SHA1(a1114b89f6fa4487210477676984c77ad94b5ef8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-9",   0x400004, 0x20000, CRC(f8725add) SHA1(fa3fcf6637ee4dd7667bd89766074b3c6ba4f166) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-11",  0x400006, 0x20000, CRC(c2a5373e) SHA1(602b32e5ecc7007efe9ad30751040ee52b81f59a) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2amf7 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "t-2.u52", 0x000000, 0x80000, CRC(0d305e8b) SHA1(7094160abbf24c119a575d93e3fe1ab84b537de0) )
	ROM_LOAD16_BYTE( "t-1.u36", 0x000001, 0x80000, CRC(137d8665) SHA1(cf4805a11ab614ce5b7e1302ac14ba50fb01e5f4) )
	ROM_LOAD16_BYTE( "t-4.u54", 0x100000, 0x40000, CRC(0b3fe5dd) SHA1(9b66cb867da61595f53d1c9e6b48c6bb7e06e1e0) )
	ROM_LOAD16_BYTE( "t-3.u38", 0x100001, 0x40000, CRC(dbee7b18) SHA1(e56af12fc9d30e92d37e688ff621ea09abb94b53) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",  0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",  0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",  0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",  0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",  0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )
	// These map over 0x400000 to 0x4FFFFF
	ROMX_LOAD( "stf2th-10",   0x400000, 0x20000, CRC(84427d1b) SHA1(f988a2b53c8cc46eeb8032084f24966a539b3734) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-12",   0x400002, 0x20000, CRC(55bc790c) SHA1(a1114b89f6fa4487210477676984c77ad94b5ef8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-9",    0x400004, 0x20000, CRC(f8725add) SHA1(fa3fcf6637ee4dd7667bd89766074b3c6ba4f166) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "stf2th-11",   0x400006, 0x20000, CRC(c2a5373e) SHA1(602b32e5ecc7007efe9ad30751040ee52b81f59a) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2tlona )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "tl4mt.1",   0x000000, 0x80000, CRC(158635ca) SHA1(878b56064861993ac92fbd88eb1117d3680fe7d7) )
	ROM_LOAD16_BYTE( "tl4m.2",    0x000001, 0x80000, CRC(882cd1c4) SHA1(0cb971756352b1022ecd309b1bc3688c1f1acbd8) )
	ROM_LOAD16_BYTE( "u221t.1m",  0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "u195t.1m",  0x100001, 0x20000, CRC(db7e1f72) SHA1(1ca99a3b425ac137f3c104cf4deb50d9431dacdd) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2tlonb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "tl4m.1",   0x000000, 0x80000, CRC(afc7bd18) SHA1(ef7af7fb3563073b96563274ec48783feb2be757) )
	ROM_LOAD16_BYTE( "tl4m.2",   0x000001, 0x80000, CRC(882cd1c4) SHA1(0cb971756352b1022ecd309b1bc3688c1f1acbd8) )
	ROM_LOAD16_BYTE( "u221.1m",  0x100000, 0x20000, CRC(d1707134) SHA1(5bfdf7bc57bdb85183647ebb175346070dd102ee) )
	ROM_LOAD16_BYTE( "u195.1m",  0x100001, 0x20000, CRC(cd1d5666) SHA1(8befd2c324eb29bdad6fc8fb2554cdfaf9808f9b) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2tlonc )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "tl4m.1",  0x000000, 0x80000, CRC(afc7bd18) SHA1(ef7af7fb3563073b96563274ec48783feb2be757) )
	ROM_LOAD16_BYTE( "tl4m.2",  0x000001, 0x80000, CRC(882cd1c4) SHA1(0cb971756352b1022ecd309b1bc3688c1f1acbd8) )
	ROM_LOAD16_BYTE( "sf11-2.010",  0x100000, 0x20000, CRC(f8a5cd53) SHA1(f474e6d24f25ca9a126bd68b02089a0161e2cc0d) )
	ROM_LOAD16_BYTE( "u195t.1m",  0x100001, 0x20000, CRC(db7e1f72) SHA1(1ca99a3b425ac137f3c104cf4deb50d9431dacdd) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2yyc3d5 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf3d5-1040", 0x000000, 0x80000, CRC(bcdd2c3a) SHA1(eff98e425f283afc69064e8bc73f769e0aab93ed) )
	ROM_LOAD16_BYTE( "sf3d5-3040", 0x000001, 0x80000, CRC(01965987) SHA1(42abce3aa983ac4143490c0ab2e772a154905860) )
	ROM_LOAD16_BYTE( "sf3d5-2010", 0x100000, 0x20000, CRC(dd2e1d31) SHA1(22b341a7365ba4a52c9ee2244d68409c5e86bcf0) )
	ROM_RELOAD(                 0x140000, 0x20000 )
	ROM_LOAD16_BYTE( "u195.rom", 0x100001, 0x20000, CRC(c95e4443) SHA1(28417dee9ccdfa65b0f4a92aa29b90279fe8cd85) )
	ROM_RELOAD(                 0x140001, 0x20000 )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2yyc3g )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf3g-1040", 0x000000, 0x80000, CRC(c90559a5) SHA1(f45563c79cf5ce610f92ca84c96d337cf6c9a979) )
	ROM_LOAD16_BYTE( "sf3g-3040", 0x000001, 0x80000, CRC(81f36682) SHA1(53776084c973c0b7aafb203e8efcfd5f5c659c93) )
	ROM_LOAD16_BYTE( "sf3g-2010", 0x100000, 0x20000, CRC(9eee20a1) SHA1(a6769744094dc0e65f9f34ef36929e7e8ae6155b) )
	ROM_RELOAD(                 0x140000, 0x20000 )
	ROM_LOAD16_BYTE( "sf3g-4010", 0x100001, 0x20000, CRC(6ac3d875) SHA1(ab4384d7a9194b2628836013d3d9f275d55c77bb) )
	ROM_RELOAD(                 0x140001, 0x20000 )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2yyc6 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf6-1040", 0x000000, 0x80000, CRC(ccd74822) SHA1(5f64585335ccc0fb1a97339532a6694076e2b6f2) )
	ROM_LOAD16_BYTE( "sf6-3040", 0x000001, 0x80000, CRC(2a48b557) SHA1(2e74925a925f86619d4f8e633af718a5eaa8c585) )
	ROM_LOAD16_BYTE( "u221.rom", 0x100000, 0x20000, CRC(64e6e091) SHA1(32ec05db955e538d4ada26d19ee50926f74b684f) )
	ROM_RELOAD(                 0x140000, 0x20000 )
	ROM_LOAD16_BYTE( "u195.rom", 0x100001, 0x20000, CRC(c95e4443) SHA1(28417dee9ccdfa65b0f4a92aa29b90279fe8cd85) )
	ROM_RELOAD(                 0x140001, 0x20000 )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2th.key", 0x00, 0x80, CRC(67e80fca) SHA1(e937bc4cf0e05ba93c32bc47d65c5b027bc2b48e) )
ROM_END

ROM_START( sf2ceeabl )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "joe-922",              0x000000, 0x80000, CRC(e927556c) SHA1(3878ed3cfb10888a3c99001c3d6076c54d61999f) )
	ROM_LOAD16_BYTE( "joe-921",              0x000001, 0x80000, CRC(8632e786) SHA1(56d4faf986a4791ae608b066659bd365d47bbe01) )
	ROM_LOAD16_BYTE( "u221t.1m",             0x100000, 0x20000, CRC(1073b7b6) SHA1(81ca1eab65ceac69520584bb23a684ccb9d92f89) )
	ROM_LOAD16_BYTE( "sfu8-4.010",           0x100001, 0x20000, CRC(924c6ce2) SHA1(676a912652bd75da5087f0c7eae047b7681a993c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "tat-01.bin",    0x000000, 0x40000, CRC(a887f7d4) SHA1(d7e0c46b3ab1c6352f45033cb9e610d9c34d51fb), ROM_SKIP(7) )
	ROM_CONTINUE(          0x000004, 0x40000)
	ROMX_LOAD( "tat-05.bin",    0x000001, 0x40000, CRC(9390ff23) SHA1(b234169615aa952e3b15c7b0dfb495e499ba49ef), ROM_SKIP(7) )
	ROM_CONTINUE(          0x000005, 0x40000)
	ROMX_LOAD( "tat-02.bin",    0x000002, 0x40000, CRC(afb3b589) SHA1(9721fa705d62814e416c38a6c3e698efb9385a98), ROM_SKIP(7) )
	ROM_CONTINUE(          0x000006, 0x40000)
	ROMX_LOAD( "tat-06.bin",    0x000003, 0x40000, CRC(90f2053e) SHA1(a78710421e702b410650c45c3dec21bf16799fb4), ROM_SKIP(7) )
	ROM_CONTINUE(          0x000007, 0x40000)

	ROMX_LOAD( "tat-03.bin",    0x200000, 0x40000, CRC(79fa8bf0) SHA1(9f8f7b8dc54a75226beb017b9ca9fd62a9e42f6b), ROM_SKIP(7) )
	ROM_CONTINUE(          0x200004, 0x40000)
	ROMX_LOAD( "tat-07.bin",    0x200001, 0x40000, CRC(6a5f153c) SHA1(f3d82ad01e2e4bdb2039815747fa14399c69753a), ROM_SKIP(7) )
	ROM_CONTINUE(          0x200005, 0x40000)
	ROMX_LOAD( "tat-04.bin",    0x200002, 0x40000, CRC(32518120) SHA1(56ffa5fffb714cff8be8be5a3675b8a5fa29b2bc), ROM_SKIP(7) )
	ROM_CONTINUE(          0x200006, 0x40000)
	ROMX_LOAD( "tat-08.bin",    0x200003, 0x40000, CRC(c16579ae) SHA1(42c9d6df9f3b015f5d1ad4fa2b34ea90bb37bcae), ROM_SKIP(7) )
	ROM_CONTINUE(          0x200007, 0x40000)

	ROMX_LOAD( "tat-09.bin",    0x400000, 0x40000, CRC(169d85a6) SHA1(dd98c8807e80465858b2eac10825e598c37e1a93), ROM_SKIP(7) )
	ROM_CONTINUE(          0x400004, 0x40000)
	ROMX_LOAD( "tat-11.bin",    0x400001, 0x40000, CRC(32a3a841) SHA1(6f9a13b8828998d194dd3933b032c75efed9cab3), ROM_SKIP(7) )
	ROM_CONTINUE(          0x400005, 0x40000)
	ROMX_LOAD( "tat-10.bin",    0x400002, 0x40000, CRC(0c638630) SHA1(709d183d181a0509c7ed839c59214851468d2bb8), ROM_SKIP(7) )
	ROM_CONTINUE(          0x400006, 0x40000)
	ROMX_LOAD( "tat-12.bin",    0x400003, 0x40000, CRC(6ee19b94) SHA1(c45119d04879b6ca23a3f7749175c56b381b43f2), ROM_SKIP(7) )
	ROM_CONTINUE(          0x400007, 0x40000)

	ROM_REGION( 0x18000, "audiocpu", 0 ) 
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "27020.2",    0x00000, 0x40000, CRC(6cfffb11) SHA1(995526183ffd35f92e9096500a3fe6237faaa2dd) )

	ROM_REGION( 0x00c8d, "pld", 0 ) 
	ROM_LOAD_OPTIONAL( "gal20v8.68kadd",    0x00000, 0x00c8d, CRC(27cdd376) SHA1(9fb5844b33002bec80fb92d3e5d1bbc779087300) )//68k address decoder

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cejab2 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sfu7-1.040", 0x000000, 0x80000, CRC(866a9b31) SHA1(92f89084293b69a9d5cd8d282ffaaca0739f1b03) )
	ROM_LOAD16_BYTE( "sfu7-5.040", 0x000001, 0x80000, CRC(49b15fcd) SHA1(4edc998e559568730e0fcc122162beefac541337) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2h11.key", 0x00, 0x80, CRC(822729a2) SHA1(acaadef38fd97dba215c13688061cee87d877c19) )
ROM_END

ROM_START( sf2cebr )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92_23a_po10.8f", 0x000000, 0x80000, CRC(74e848ee) SHA1(6dce8d0c7d439e6d1d08c8169a3ecdf178e82c16) )
	ROM_LOAD16_WORD_SWAP( "s92_22a_po10.7f",  0x080000, 0x80000, CRC(c3c49626) SHA1(d0fae1d2758360b56e6e583feb4bdf7d4e2e1eba) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92br_10.bin", 0x400000, 0x80000, CRC(b3e1dd5f) SHA1(714BF1519CED85567D3D35FDF4AA9E4268CC9F0F) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92br_11.bin", 0x400002, 0x80000, CRC(f13af812) SHA1(E3711CBAA3169D0F48DF420953F1AFD0AB76EE08) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92br_12.bin", 0x400004, 0x80000, CRC(10ce42af) SHA1(530B2A6E2D13B2694BD611B31B056B7458FD1571) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92br_13.bin", 0x400006, 0x80000, CRC(32cf5af3) SHA1(43972C07F5CCF01B0CE0727541590C3C6B97C300) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2h11 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sfu7-1.040", 0x000000, 0x80000, CRC(866a9b31) SHA1(92f89084293b69a9d5cd8d282ffaaca0739f1b03) )
	ROM_LOAD16_BYTE( "sfu7-3.040", 0x000001, 0x80000, CRC(f3a45593) SHA1(0ba0d05f904ac17cd34c0a7c9dd0a20759ff4e78) )
	ROM_LOAD16_BYTE( "u221.1m", 0x100000, 0x20000, CRC(d1707134) SHA1(5bfdf7bc57bdb85183647ebb175346070dd102ee) )
	ROM_LOAD16_BYTE( "u195.1m", 0x100001, 0x20000, CRC(cd1d5666) SHA1(8befd2c324eb29bdad6fc8fb2554cdfaf9808f9b) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",   0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",   0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",   0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",   0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",   0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",   0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",   0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a",   0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c",   0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c",   0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c",   0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c",   0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",    0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(              0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",    0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",    0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2h11.key", 0x00, 0x80, CRC(822729a2) SHA1(acaadef38fd97dba215c13688061cee87d877c19) )
ROM_END

ROM_START( sf2ceh )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "s92_23ah.8f", 0x000000, 0x80000, CRC(25dc14c8) SHA1(fc7b5de3a50d7d9ee977091bab5f82f824e386f2) )
	ROM_LOAD16_WORD_SWAP( "s92_22ah.7f",  0x080000, 0x80000, CRC(1c9dd91c) SHA1(66fbd10958d3b9f027bc3ba85c99b649cf866ab7) )
	ROM_LOAD16_WORD_SWAP( "s92_21a.6f",  0x100000, 0x80000, CRC(925a7877) SHA1(1960dca35f0ca6f2b399a9fccfbc0132ac6425d1) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "s92-1m.3a",  0x000000, 0x80000, CRC(03b0d852) SHA1(f370f25c96ad2b94f8c53d6b7139100285a25bef) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-3m.5a",  0x000002, 0x80000, CRC(840289ec) SHA1(2fb42a242f60ba7e74009b5a90eb26e035ba1e82) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-2m.4a",  0x000004, 0x80000, CRC(cdb5f027) SHA1(4c7d944fef200fdfcaf57758b901b5511188ed2e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-4m.6a",  0x000006, 0x80000, CRC(e2799472) SHA1(27d3796429338d82a8de246a0ea06dd487a87768) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-5m.7a",  0x200000, 0x80000, CRC(ba8a2761) SHA1(4b696d66c51611e43522bed752654314e76d33b6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-7m.9a",  0x200002, 0x80000, CRC(e584bfb5) SHA1(ebdf1f5e2638eed3a65dda82b1ed9151a355f4c9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-6m.8a",  0x200004, 0x80000, CRC(21e3f87d) SHA1(4a4961bb68c3a1ce15f9d393d9c03ecb2466cc29) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-8m.10a", 0x200006, 0x80000, CRC(befc47df) SHA1(520390420da3a0271ba90b0a933e65143265e5cf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-10m.3c", 0x400000, 0x80000, CRC(960687d5) SHA1(2868c31121b1c7564e9767b9a19cdbf655c7ed1d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-12m.5c", 0x400002, 0x80000, CRC(978ecd18) SHA1(648a59706b93c84b4206a968ecbdc3e834c476f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-11m.4c", 0x400004, 0x80000, CRC(d6ec9a0a) SHA1(ed6143f8737013b6ef1684e37c05e037e7a80dae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "s92-13m.6c", 0x400006, 0x80000, CRC(ed2c67f6) SHA1(0083c0ffaf6fe7659ff0cf822be4346cd6e61329) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "s92_09.11a",  0x00000, 0x08000, CRC(08f6b60e) SHA1(8258fcaca4ac419312531eec67079b97f471179c) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "s92_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "s92_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2ce.key", 0x00, 0x80, CRC(35b37429) SHA1(b372cce106c0900554735c207fb333ac93554ec2) )
ROM_END

ROM_START( sf2cn )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "sf2j_30", 0x00000, 0x20000, CRC(70813e5e) SHA1(39219a98d368dcb67cbd0a756f3e1fab7b9352f4) )
	ROM_LOAD16_BYTE( "sf2j_37", 0x00001, 0x20000, CRC(d0659611) SHA1(1368228cc2c41a361f0e8eb516610522a38394b2) )
	ROM_LOAD16_BYTE( "sf2j31.bin", 0x40000, 0x20000, CRC(fe15cb39) SHA1(383478524881ea70d9e04c9b6143b8735b637eee) )
	ROM_LOAD16_BYTE( "sf2j38.bin", 0x40001, 0x20000, CRC(38614d70) SHA1(39c58096f3a8e01fb439639b742b83102bbaa7f6) )
	ROM_LOAD16_BYTE( "sf2j_28", 0x80000, 0x20000, CRC(2d4a1b8a) SHA1(9dce74c32fa9c63f38d33a03327b22e74d2118c1) )
	ROM_LOAD16_BYTE( "sf2j_35", 0x80001, 0x20000, CRC(5f622bdb) SHA1(4fe5797acc2645a1bd27d247457b6f24bfd60f96) )
	ROM_LOAD16_BYTE( "sf2_29b.10e", 0xc0000, 0x20000, CRC(bb4af315) SHA1(75f0827f4f7e9f292add46467f8d4fe19b2514c9) )
	ROM_LOAD16_BYTE( "sf2_36b.10f", 0xc0001, 0x20000, CRC(c02a13eb) SHA1(b807cc495bff3f95d03b061fc629c95f965cb6d8) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2_06",  0x000000, 0x80000, CRC(d3aab35d) SHA1(bc90464bc38b326b46f0da97008116ee639e2598) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_08",  0x000002, 0x80000, CRC(f6a68d56) SHA1(4ef2668a245fb207c599f0e72e979f8c0191df25) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_05",  0x000004, 0x80000, CRC(1ddcda55) SHA1(494338ac59e4253177b731bd6ad116a63f7ded8c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_07",  0x000006, 0x80000, CRC(d3274004) SHA1(a278e0740806cf8098058d1c33eb0964cc130ded) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_15",  0x200000, 0x80000, CRC(f8710c69) SHA1(a298117a7869b0891220c229d0dceba7ac6bf594) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_17",  0x200002, 0x80000, CRC(dd376567) SHA1(a817c999098b0274ed2c052b96c562bed407b7b1) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_14",  0x200004, 0x80000, CRC(c754e2c4) SHA1(7936eaa669c84742c1511768bb9039c26b2fb3c3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_16",  0x200006, 0x80000, CRC(0d4799bd) SHA1(5e63e889cabc4436c2a49997c9d0a47529d264ad) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_25",  0x400000, 0x80000, CRC(a6671144) SHA1(f4017ad15784078c00ef76220f4e5bdba61a6495) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_27",  0x400002, 0x80000, CRC(008b2bdd) SHA1(a048a70fe3c752b79e14eadf2369f068fc831439) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_24",  0x400004, 0x80000, CRC(0f8a9ec4) SHA1(cde0013df78333ebfbaacb9a9e212fbc0b2e04d3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_26",  0x400006, 0x80000, CRC(0fb4241e) SHA1(f749daa6ecf018542ecf0f3711491eb85fac91b3) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",   0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(            0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sf2c.key", 0x00, 0x80, CRC(fdc05d86) SHA1(f828e6171a271bc12a5c9ab5be237562e263ccdb) )
ROM_END

// There is something special about this version but I don't remember what. The region can be
// selected via the dipswitches: Region DIP: 7-8 On On ETC, Off Off JPN, Off On USA
// Tested: stays in Japan region
ROM_START( sf2ly )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sf2r3.23", 0x00000, 0x80000, CRC(ca331c3c) SHA1(e6ff34f76256c2eff9a7677051d3e7279dc83550) )
	ROM_LOAD16_WORD_SWAP( "sf2r3.22", 0x80000, 0x80000, CRC(e446d96a) SHA1(68e39c6c1f89ce223366d37268041c5f1f56531c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "sf2-5m.4a",  0x000000, 0x80000, CRC(22c9cc8e) SHA1(b9194fb337b30502c1c9501cd6c64ae4035544d4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-7m.6a",  0x000002, 0x80000, CRC(57213be8) SHA1(3759b851ac0904ec79cbb67a2264d384b6f2f9f9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-1m.3a",  0x000004, 0x80000, CRC(ba529b4f) SHA1(520840d727161cf09ca784919fa37bc9b54cc3ce) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-3m.5a",  0x000006, 0x80000, CRC(4b1b33a8) SHA1(2360cff890551f76775739e2d6563858bff80e41) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-6m.4c",  0x200000, 0x80000, CRC(2c7e2229) SHA1(357c2275af9133fd0bd6fbb1fa9ad5e0b490b3a2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-8m.6c",  0x200002, 0x80000, CRC(b5548f17) SHA1(baa92b91cf616bc9e2a8a66adc777ffbf962a51b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-2m.3c",  0x200004, 0x80000, CRC(14b84312) SHA1(2eea16673e60ba7a10bd4d8f6c217bb2441a5b0e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2-4m.5c",  0x200006, 0x80000, CRC(5e9cd89a) SHA1(f787aab98668d4c2c54fc4ba677c0cb808e4f31e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_25_hack01.8d",  0x400000, 0x80000, CRC(4267b696) SHA1(af65e3b2cc3b7a7f39d5e7e598da7f4c9d351eea) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_27_hack01.10d", 0x400002, 0x80000, CRC(df9b9146) SHA1(2029aa59c1646af0fd7fa06f353edcbf7f7792de) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_24_hack01.7d",  0x400004, 0x80000, CRC(a08a9786) SHA1(80a79e45c003fbc95cc5cd0d037b55f2f7fec64c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "sf2_26_hack01.9d",  0x400006, 0x80000, CRC(80feac31) SHA1(f16ce88634d2328eae93f8128423bb311cac88e6) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sf2_9.12a",  0x00000, 0x08000, CRC(a4823a1b) SHA1(7b6bf59dfd578bfbbdb64c27988796783442d659) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sf2_18.11c",  0x00000, 0x20000, CRC(7f162009) SHA1(346bf42992b4c36c593e21901e22c87ae4a7d86d) )
	ROM_LOAD( "sf2_19.12c",  0x20000, 0x20000, CRC(beade53f) SHA1(277c397dc12752719ec6b47d2224750bd1c07f79) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sf2.key",  0x00, 0x80, CRC(3cf6f06f) SHA1(7512a185d461f2b37edfc19e31a45d53600fbe44) )
ROM_END

ROM_START( slammastud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "mbu_23ed.8f", 0x000000, 0x80000, CRC(7697273f) SHA1(d42ce6414b42db14305f0497fb760e8a3e868b9d) )
	ROM_LOAD16_BYTE( "mbe_24b.9e",      0x080000, 0x20000, CRC(95d5e729) SHA1(df3be896e55c92eb50887a4317178a3d11048433) )
	ROM_LOAD16_BYTE( "mbe_28b.9f",      0x080001, 0x20000, CRC(b1c7cbcb) SHA1(cf5ad72be4a055db876e7347b1826325b9bf81d9) )
	ROM_LOAD16_BYTE( "mbe_25b.10e",     0x0c0000, 0x20000, CRC(a50d3fd4) SHA1(dc3d108c3bc27f45b8b2e11919ba2a86e05b41d1) )
	ROM_LOAD16_BYTE( "mbe_29b.10f",     0x0c0001, 0x20000, CRC(08e32e56) SHA1(70ad78b079f777ec02089f0df20ce2baad7adce5) )
	ROM_LOAD16_WORD_SWAP( "mbe_21a.6f", 0x100000, 0x80000, CRC(d5007b05) SHA1(c55e55908aeda40ca2318c76ccbc05d333676875) )
	ROM_LOAD16_WORD_SWAP( "mbu_20a.5f", 0x180000, 0x80000, CRC(fc848af5) SHA1(cd3f6e50779b89ee57a9d08bfa1d58dea286457c) )

	ROM_REGION( 0x600000, "gfx", 0 )
	ROMX_LOAD( "mb-1m.3a",  0x000000, 0x80000, CRC(41468e06) SHA1(fb365798f2889a20eebaea2393c9c2c8827003c4) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-3m.5a",  0x000002, 0x80000, CRC(f453aa9e) SHA1(24a103dc6f0dc96f8d0f6164ad732909c9cd2d6a) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-2m.4a",  0x000004, 0x80000, CRC(2ffbfea8) SHA1(13e30133664a009686e1114c92b558bdbb91ea32) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-4m.6a",  0x000006, 0x80000, CRC(1eb9841d) SHA1(685da3e011a96b36be9f639a241b2f8f27da4629) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-5m.7a",  0x200000, 0x80000, CRC(506b9dc9) SHA1(933bf2fb9bcc1a408f961f0e7052da80144bddad) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-7m.9a",  0x200002, 0x80000, CRC(aff8c2fb) SHA1(ce37a6d5b1eb58c2d74f23f84ec824c214c93217) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-6m.8a",  0x200004, 0x80000, CRC(b76c70e9) SHA1(c21e255815ec9a985919dbd760ed266c28bd47cd) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-8m.10a", 0x200006, 0x80000, CRC(e60c9556) SHA1(b91c14092aa8dbb0922d96998123ef1970a658f6) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-10m.3c", 0x400000, 0x80000, CRC(97976ff5) SHA1(ec9d3460816ab971a02fbce42960283091777e47) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-12m.5c", 0x400002, 0x80000, CRC(b350a840) SHA1(2b8b996cd08051e7e8e134bff5448775d78058a0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-11m.4c", 0x400004, 0x80000, CRC(8fb94743) SHA1(294f6182c8a41b640d1f57cb5e3a2abce3b06482) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "mb-13m.6c", 0x400006, 0x80000, CRC(da810d5f) SHA1(392bbd405244b8c99024c9228cfec6a7ef0accdb) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "mb_qa.5k",   0x00000, 0x08000, CRC(e21a03c4) SHA1(98c03fd2c9b6bf8a4fc25a4edca87fff7c3c3819) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x8000, "user1", 0 )
	ROM_COPY( "audiocpu", 0x00000, 0x00000, 0x8000 )

	ROM_REGION( 0x400000, "qsound", 0 )
	ROM_LOAD( "mb-q1.1k",   0x000000, 0x80000, CRC(0630c3ce) SHA1(520fc74c5c3638f611fa2f1b5efb08b91747e29b) )
	ROM_LOAD( "mb-q2.2k",   0x080000, 0x80000, CRC(354f9c21) SHA1(1dc6b39791fd0f760697f409a6b62361a7bf62e9) )
	ROM_LOAD( "mb-q3.3k",   0x100000, 0x80000, CRC(7838487c) SHA1(056b7da05cfca46873edacd674ca25c70855c6db) )
	ROM_LOAD( "mb-q4.4k",   0x180000, 0x80000, CRC(ab66e087) SHA1(066ea69a0157e8647eea3c44d0a1843898860678) )
	ROM_LOAD( "mb-q5.1m",   0x200000, 0x80000, CRC(c789fef2) SHA1(10d1e3d92288fccd4e064a3716a788a165efc3c9) )
	ROM_LOAD( "mb-q6.2m",   0x280000, 0x80000, CRC(ecb81b61) SHA1(e339f21ae47de4782f3b338befcdac659c3503f6) )
	ROM_LOAD( "mb-q7.3m",   0x300000, 0x80000, CRC(041e49ba) SHA1(3220b033a5c0cfbbe75c0c113cf2db39fb093a7e) )
	ROM_LOAD( "mb-q8.4m",   0x380000, 0x80000, CRC(59fe702a) SHA1(807178dfc6d864e49fd7aabb5c4895835cf0e85b) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "slammastud.key", 0x00, 0x80, CRC(ade2c2a3) SHA1(8d7a4249cf221ac24c4c66f7151a9edd7f263de5) )
ROM_END

ROM_START( wofh )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "sgyx.800",  0x000000, 0x100000, CRC(3703a650) SHA1(6cb8d6f99df5e2e5cf04aee8737bb585f9328ffd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD("sgyx-1.160",    0x000000, 0x80000, CRC(a60be9f6) SHA1(2298a4b6a2c83b76dc106a1efa19606b298d378a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD("sgyx-2.160",    0x000002, 0x80000, CRC(6ad9d048) SHA1(d47212d28d0a1ce349e4c59e5d0d99c541b3458e), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(                0x8000, 0x10000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sgyxz_snd1.bin", 0x00000, 0x40000,  CRC(c15ac0f2) SHA1(8d9e5519d9820e4ac4f70555088c80e64d052c9d) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sk2h101.key",    0x00, 0x80, CRC(679300a3) SHA1(f3e8197955f6b2b54493a449386b804b0d5e15ed) ) // OK
ROM_END

ROM_START( wofha )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "fg-c.040",  0x000000, 0x80000, CRC(d046fc86) SHA1(0ae0b9310e3a122cb69df4bb23672149794242f0) )
	ROM_LOAD16_BYTE( "fg-a.040",  0x000001, 0x80000, CRC(f176ee8f) SHA1(fba357c31774aeecef88f70df4294514585df3a0) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD("sgyx-1.160",    0x000000, 0x80000, CRC(a60be9f6) SHA1(2298a4b6a2c83b76dc106a1efa19606b298d378a), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD("sgyx-2.160",    0x000002, 0x80000, CRC(6ad9d048) SHA1(d47212d28d0a1ce349e4c59e5d0d99c541b3458e), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(           0x8000, 0x10000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "sgyxz_snd1.bin", 0x00000, 0x40000,  CRC(c15ac0f2) SHA1(8d9e5519d9820e4ac4f70555088c80e64d052c9d) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "sk2h101.key",     0x00, 0x80, CRC(679300a3) SHA1(f3e8197955f6b2b54493a449386b804b0d5e15ed) ) // OK
ROM_END

ROM_START( wofah )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "htk2a_23b.rom",  0x000000, 0x80000, CRC(1b17fc85) SHA1(d8c2bd31474dce2330adb05b859ce3fd13040d23) )
	ROM_LOAD16_WORD_SWAP( "tk2a_22c.7f",  0x080000, 0x80000, CRC(900ad4cd) SHA1(988007447f93f3467029b9c29fd9670a7ecadaa3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",   0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",   0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",   0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a",   0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wofaha )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "htk2ah_23b.rom", 0x000000, 0x80000, CRC(6e3ff382) SHA1(14ef2c708da134f925efa0c3886a104c3ef9e5d7) )
	ROM_LOAD16_WORD_SWAP( "tk2a_22c.7f",  0x080000, 0x80000, CRC(900ad4cd) SHA1(988007447f93f3467029b9c29fd9670a7ecadaa3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",   0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",   0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",   0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a",   0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wofahb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2ah_23b.rom",  0x000000, 0x80000, CRC(48fd83c6) SHA1(8f33124979d7ca4c2af10f2a98b524e5463458cc) )
	ROM_LOAD16_WORD_SWAP( "tk2a_22c.7f",  0x080000, 0x80000, CRC(900ad4cd) SHA1(988007447f93f3467029b9c29fd9670a7ecadaa3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",   0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",   0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",   0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a",   0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

ROM_START( wof3js )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3js_23.rom",  0x000000, 0x80000, CRC(1ebb76da) SHA1(a3d9643a03e964477abd5164202566fe4a11b902) )
	ROM_LOAD16_WORD_SWAP( "3js_22.rom",  0x080000, 0x80000, CRC(f41d6153) SHA1(a2cafea8402ab58e8022020242397e7cdce57aff) )
	ROM_LOAD16_BYTE( "3js_24.rom",       0x0c0000, 0x20000, CRC(06ead409) SHA1(7289afd15fecd185350d2705476d74baa6909782) )
	ROM_LOAD16_BYTE( "3js_28.rom",       0x0c0001, 0x20000, CRC(8ba934e6) SHA1(b9fb1d000a90cf2dbe2113130939c146f16a776e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3js_gfx5.rom",   0x200000, 0x80000, CRC(94b58f82) SHA1(937e7bb74e47f7ed670f63cdf7e502cf6ffe09c8), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3js_gfx7.rom",   0x200002, 0x80000, CRC(df4fb386) SHA1(4eece42595084dbab1fa2c603f231fc67efb292d), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3js_gfx6.rom",   0x200004, 0x80000, CRC(c22c5bd8) SHA1(4dd3598ca9cbbceabfb28b1b0d8a4879fcdb9a13), ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "3js_gfx8.rom",   0x200006, 0x80000, CRC(f9cfd08b) SHA1(cd55ef014705d8b07c3eb9dafdbf2a831ea25b7c), ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "3js_09.rom",     0x00000, 0x08000, CRC(21ce044c) SHA1(425fd8d33d54f35ef90d68a7530db7a0eafb600d) )
	ROM_CONTINUE(               0x10000, 0x08000 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "3js_18.rom",     0x000000, 0x20000, CRC(ac6e307d) SHA1(b490ce625bb7ce0904b0fd121fbfbd5252790f7a) )
	ROM_LOAD( "3js_19.rom",     0x020000, 0x20000, CRC(068741db) SHA1(ab48aff639a7ac218b7d5304145e10e92d61fd9f) )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h21.key", 0x00, 0x80, CRC(287d8a40) SHA1(46aa717f599f88d32afb5ecc0bf43c2cbe6892d0) )
ROM_END

ROM_START( wof3jsa )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "cx2.040", 0x00000, 0x20000, CRC(c01a6d2f) SHA1(c1e69e075bb01141c026bf0722a64659e1802184) )
	ROM_CONTINUE(               0x80000, 0x20000 )
	ROM_CONTINUE(               0x40000, 0x20000 )
	ROM_CONTINUE(               0xc0000, 0x20000 )
	ROM_LOAD16_BYTE( "cx1.040", 0x00001, 0x20000, CRC(fd95e677) SHA1(42a10e73bd30498dc39cd66abf73680799ebe8b0) )
	ROM_CONTINUE(               0x80001, 0x20000 )
	ROM_CONTINUE(               0x40001, 0x20000 )
	ROM_CONTINUE(               0xc0001, 0x20000 )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tx-a.160", 0x000000, 0x80000, CRC(ae348da2) SHA1(e86ab38e75c46ff2a4fa974fbbd3c2d2f67cef36), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(          0x000004, 0x80000 )
	ROM_CONTINUE(          0x200000, 0x80000 )
	ROM_CONTINUE(          0x200004, 0x80000 )
	ROMX_LOAD( "tx-b.160", 0x000002, 0x80000, CRC(384a6db0) SHA1(57273edce545a7fb4026cb4c705d97d71f24ea6f), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(          0x000006, 0x80000 )
	ROM_CONTINUE(          0x200002, 0x80000 )
	ROM_CONTINUE(          0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wof3sj )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "k6b.040",  0x000000, 0x80000, CRC(7b365108) SHA1(e4ef6e7267ecf36d8b15c7df0351b38777cd559d) )
	ROM_LOAD16_BYTE( "k6a.040",  0x000001, 0x80000, CRC(10488a51) SHA1(061d5139f4289cbca9e0a743954d9c65a9384c06) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "k6a.160",   0x000000, 0x80000, CRC(a121180d) SHA1(9501399479a5892db0c818637459f77540794b85), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "k6b.160",   0x000002, 0x80000, CRC(a4db96c4) SHA1(6798c0cbd9a1f8f4704c5cb9e19e8873149d3c33), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wof3sja )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3js.800",  0x000000, 0x100000, CRC(812f9200) SHA1(ddf4261c21762e8168d83393a59aa1450762a89a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "k6a.160",   0x000000, 0x80000, CRC(a121180d) SHA1(9501399479a5892db0c818637459f77540794b85), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000004, 0x80000 )
	ROM_CONTINUE(              0x200000, 0x80000 )
	ROM_CONTINUE(              0x200004, 0x80000 )
	ROMX_LOAD( "k6b.160",   0x000002, 0x80000, CRC(a4db96c4) SHA1(6798c0cbd9a1f8f4704c5cb9e19e8873149d3c33), ROM_GROUPWORD | ROM_SKIP(6) )
	ROM_CONTINUE(              0x000006, 0x80000 )
	ROM_CONTINUE(              0x200002, 0x80000 )
	ROM_CONTINUE(              0x200006, 0x80000 )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wofsj )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "c-c47b.040",  0x000000, 0x80000, CRC(b1809761) SHA1(99a17ed193654f61622eb721e20b69894c96d3d8) )
	ROM_LOAD16_BYTE( "a-2402.040",  0x000001, 0x80000, CRC(4fab4232) SHA1(d8ffd06cce73e1c4bc6abb69a2e81277ce901563) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wofsja )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "one.800",  0x000000, 0x100000, CRC(0507584d) SHA1(5a9df64b7c2c54c5aa0d4c9486c7404157c6119e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "9",              0x00000, 0x08000, CRC(86fe8a97) SHA1(cab82bcd0f49bcb40201b439cfdd10266f46752a) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wofsjb )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "c-d140.040",  0x000000, 0x80000, CRC(e6d933a6) SHA1(c1f08bbbfc855bbc96b844eed7b1e4f9a0a07fbf) )
	ROM_LOAD16_BYTE( "a-0050.040",  0x000001, 0x80000, CRC(403eaead) SHA1(ce6d061e5ee91de779c8d0c19bed273dc4769900) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",   0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",   0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",   0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",   0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",   0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",   0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",   0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a",   0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h21.key", 0x00, 0x80, CRC(287d8a40) SHA1(46aa717f599f88d32afb5ecc0bf43c2cbe6892d0) )
ROM_END

ROM_START( wofsjc )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cx2s43.040",  0x000000, 0x100000, CRC(cb28807e) SHA1(78312081ad95273ea04f1e16dc097bf5b54f88b3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "sgyxz_snd2.bin", 0x00000, 0x10000,  CRC(210c376f) SHA1(0d937c86078d0a106f5636b7daf5fc0266c2c2ec) )
	ROM_RELOAD(                0x8000, 0x10000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "18",             0x00000, 0x20000, CRC(c04be720) SHA1(2e544e0a0358b6afbdf826d35d9c4c59e4787a93) )
	ROM_LOAD( "19",             0x20000, 0x20000, CRC(fbb8d8c1) SHA1(8a7689bb7ed56243333133cbacf01a0ae825201e) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "sk2h31.key", 0x00, 0x80, CRC(6c1c5a58) SHA1(7b2cb9884bfff824691d258dd919b723c85ef323) )
ROM_END

ROM_START( wofjd )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2j_23jd.8f", 0x000000, 0x80000, CRC(08631657) SHA1(2d2e0f302dbd64bb8a37577171e6e2194524abdf) )
	ROM_LOAD16_WORD_SWAP( "tk2j_22c.7f",  0x080000, 0x80000, CRC(b74b09ac) SHA1(3a44d6db5f51e1b5d2b43ef0ad1191da21e48427) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a", 0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a", 0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a", 0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a", 0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_05.7a", 0x200000, 0x80000, CRC(e4a44d53) SHA1(b747679f4d63e5e62d9fd81b3120fba0401fadfb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_06.8a", 0x200002, 0x80000, CRC(58066ba8) SHA1(c93af968e21094d020e4b2002e0c6fc0d746af0b) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_07.9a", 0x200004, 0x80000, CRC(d706568e) SHA1(7886414dc86c42e35d24b85c4bfa41a9f0c167ac) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2_08.10a", 0x200006, 0x80000, CRC(d4a19a02) SHA1(ff396b1d33d9b4842140f2c6d085fe05748e3244) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",     0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(               0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",     0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",     0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",     0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",     0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

// same as wofu except first rom
ROM_START( wofud )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "wofud.23",    0x000000, 0x80000, CRC(9bab998f) SHA1(6afe212d7816bde23aecb92f57d075c3e411d4c6) )
	ROM_LOAD16_WORD_SWAP( "tk2u_22c.7f", 0x080000, 0x80000, CRC(f5af4774) SHA1(f6d53cf5b330e6d68f84da3e8c831a475585b93e) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-5m.7a",  0x200000, 0x80000, CRC(291f0f0b) SHA1(094baf0f960f25fc2525b3b1cc378a49d9a0955d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-7m.9a",  0x200002, 0x80000, CRC(3edeb949) SHA1(c155698dd9ee9eb24bbc97a21118ef2e897ea82f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-6m.8a",  0x200004, 0x80000, CRC(1abd14d6) SHA1(dffff3126f102b4ec028a81405fc5b9bd7bb65b3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-8m.10a", 0x200006, 0x80000, CRC(b27948e3) SHA1(870d5d23f56798831c641e877ea94217058b2ddc) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "wofch.key", 0x00, 0x80, CRC(23f2d0bb) SHA1(48ba9300bc2136e9583754a51d5ab2532eca85c6) )
ROM_END

/*    YEAR    NAME           PARENT     MACHINE     INPUT                  INIT             MONITOR COMPANY       FULLNAME FLAGS */
GAME( 1991, 3wondrud,        3wonders, cps1_10MHz, 3wonders, cps_state, init_cps1,     ROT0,   "bootleg",         "Three Wonders (US 910520 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, 3wondersha,      3wonders, cps1_10MHz, 3wonders, cps_state, init_cps1,     ROT0,   "bootleg",         "Three Wonders (bootleg set 3, 910520 etc)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, captcoud,        captcomm, cps1_10MHz, captcomm, cps_state, init_cps1,     ROT0,   "bootleg",         "Captain Commando (US 910928 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, captcocn,        captcomm, cps1_10MHz, captcomm, cps_state, init_cps1,     ROT0,   "bootleg",         "Captain Commando (Chineese Translation 911014)", MACHINE_SUPPORTS_SAVE )
GAME( 1988, daimakaib,       ghouls,   daimakb,    daimakai, cps_state, init_cps1,     ROT0,   "bootleg",         "Dai Makai-Mura (bootleg, Japan)" , MACHINE_SUPPORTS_SAVE )
GAME( 1993, dinoh,           dino,     qsound,     dinohz,   cps_state, init_dinoh,    ROT0,   "bootleg",         "Cadillacs and Dinosaurs (bootleg set 3, 930223 Asia TW)" , MACHINE_SUPPORTS_SAVE )
GAME( 1993, dinoha,          dino,     qsound,     dinohz,   cps_state, init_dinoh,    ROT0,   "bootleg",         "Cadillacs and Dinosaurs (bootleg set 1, 930223 Asia TW)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, dinotpic,        dino,     qsound,     dinohz,   cps_state, init_dinohb,   ROT0,   "bootleg",         "Cadillacs and Dinosaurs (bootleg set 2, 930201 etc)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, dinohc,          dino,     qsound,     dinohz,   cps_state, init_dino,     ROT0,   "bootleg",         "Cadillacs and Dinosaurs (Chinese bootleg, 930223 Asia TW)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )
GAME( 1993, dinopic4,        dino,     qsound,     dinohz,   cps_state, init_dino,     ROT0,   "bootleg",         "Cadillacs and Dinosaurs (bootleg with PIC16C57, set 4)", MACHINE_NO_SOUND | MACHINE_SUPPORTS_SAVE )
GAME( 1993, dinod,           dino,     qsound,     dinohz,   cps_state, init_dinoeh,   ROT0,   "bootleg",         "Cadillacs and Dinosaurs (World 930201 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, mercscn,         mercs,    cps1_10MHz, mercs,    cps_state, init_cps1,     ROT270, "bootleg",         "Senjou no Ookami II (Chineese 900302)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, pnicku,          pnickj,   cps1_10MHz, pnicku,   cps_state, init_cps1,     ROT0,   "bootleg",         "Pnickies Loca Test Version (US 940608)", MACHINE_SUPPORTS_SAVE )
GAME( 1993, punisherud1,     punisher, qsound,     punisher, cps_state, init_punisher, ROT0,   "bootleg",         "The Punisher (US 930422 Phoenix Edition (8b/32p))", MACHINE_SUPPORTS_SAVE )
GAME( 1993, punisherud2,     punisher, qsound,     punisher, cps_state, init_punisher, ROT0,   "bootleg",         "The Punisher (US 930422 Phoenix Edition (16b/40p))", MACHINE_SUPPORTS_SAVE )
GAME( 1993, punisherb,       punisher, qsound,     punisher, cps_state, init_punisherb,ROT0,   "bootleg",         "The Punisher (Bootleg)", MACHINE_SUPPORTS_SAVE)
GAME( 1992, sf2mega2,        sf2ce,    cps1_12MHz, sf2,      cps_state, init_sf2h9,    ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Mega Co bootleg set 2, 920313 etc)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2amf5,         sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Alpha Magic-F bootleg set 3, 920313 etc)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2cejabl,       sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (920322 Japan bootleg set 1)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2m12,          sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (M12, bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2m13,          sf2ce,    cps1_12MHz, sf2j,     cps_state, init_sf2h13,   ROT0,   "bootleg",         "Street Fighter II' Turbo: Hyper Fighting (M13, bootleg)", MACHINE_SUPPORTS_SAVE ) // bad tile for Blanka on player select screen
GAME( 2021, sf2rbpr,         sf2ce,    cps1_12MHz, sf2rb,    cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Rainbow, bootleg, set 1, protection removed)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2amf6,         sf2ce,    cps1_12MHz, sf2hack,  cps_state, init_sf2hack,  ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Alpha Magic-F bootleg set 4, 920313 etc)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2amf7,         sf2ce,    cps1_12MHz, sf2hack,  cps_state, init_sf2hack,  ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Alpha Magic-F bootleg set 5, 920313 etc)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2tlona,        sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Tu Long bootleg set 1, 811102 001)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2tlonb,        sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Tu Long bootleg set 2, 811102 001)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2tlonc,        sf2ce,    cps1_12MHz, sf2hack,  cps_state, init_sf2hack,  ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Tu Long bootleg set 3, 811102 001)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2yyc3d5,       sf2ce,    cps1_12MHz, sf2hack,  cps_state, init_sf2hack,  ROT0,   "bootleg",         "Street Fighter II': Champion Edition (YYC, bootleg, 3D5)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2yyc3g,        sf2ce,    cps1_12MHz, sf2hack,  cps_state, init_sf2hack,  ROT0,   "bootleg",         "Street Fighter II': Champion Edition (YYC, bootleg, 3G)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2yyc6,         sf2ce,    cps1_12MHz, sf2hack,  cps_state, init_sf2hack,  ROT0,   "bootleg",         "Street Fighter II': Champion Edition (YYC, bootleg, 6)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2ceeabl,       sf2ce,    sf2m1,      sf2,      cps_state, init_sf2m1,    ROT0,   "bootleg",         "Street Fighter II': Champion Edition (920313 etc bootleg set 1)", MACHINE_IMPERFECT_GRAPHICS | MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2cejab2,       sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (920322 Japan bootleg set 2)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2cebr,         sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Brazil 920313)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2h11,          sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (M11, bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2ceh,          sf2ce,    cps1_12MHz, sf2,      cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': Champion Edition (Hispanic 990804)", MACHINE_SUPPORTS_SAVE )
GAME( 1991, sf2cn,           sf2,      cps1_10MHz, sf2j,     cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': The World Warrior (Chinese 911210)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, sf2ly,           sf2,      cps1_10MHz, sf2j,     cps_state, init_cps1,     ROT0,   "bootleg",         "Street Fighter II': The World Warrior (with bosses like Champion Edition, 910522 Japan, CPS-B-11)", MACHINE_SUPPORTS_SAVE )
GAME( 1994, slammastud,      slammast, qsound,     slammast, cps_state, init_slammast, ROT0,   "bootleg",         "Saturday Night Slam Masters (USA 930713 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofh,            wof,      sk2h3,      sk2h1,    cps_state, init_sk2h1,    ROT0,   "bootleg",         "Sangokushi II: Sanguo Yingxiong Zhuan (Chinese bootleg set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofha,           wof,      sk2h3,      sk2h1,    cps_state, init_sk2h1,    ROT0,   "bootleg",         "Sangokushi II: Sanguo Yingxiong Zhuan (Chinese bootleg set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofah,           wof,      qsound,     wof,      cps_state, init_wof,      ROT0,   "bootleg",         "Sangokushi II (hack set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofaha,          wof,      qsound,     wof,      cps_state, init_wof,      ROT0,   "bootleg",         "Sangokushi II (hack set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofahb,          wof,      qsound,     wof,      cps_state, init_wof,      ROT0,   "bootleg",         "Sangokushi II (hack set 3, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wof3js,          wof,      qsound,     sk2h21,   cps_state, init_sk2h21,   ROT0,   "bootleg",         "Sangokushi II: San Jian Sheng (Chinese bootleg set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wof3jsa,         wof,      sk2h3,      sk2h21,   cps_state, init_sk2h22,   ROT0,   "bootleg",         "Sangokushi II: San Jian Sheng (Chinese bootleg set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wof3sj,          wof,      sk2h31,     sk2h31,   cps_state, init_sk2h22,   ROT0,   "bootleg",         "Sangokushi II: San Sheng Jian (Chinese bootleg set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wof3sja,         wof,      sk2h31,     sk2h31,   cps_state, init_sk2h22,   ROT0,   "bootleg",         "Sangokushi II: San Sheng Jian (Chinese bootleg set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofsj,           wof,      sk2h31,     sk2h31,   cps_state, init_sk2h22,   ROT0,   "bootleg",         "Sangokushi II: Sheng Jian Sanguo (Chinese bootleg set 1, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofsja,          wof,      sk2h31,     sk2h31,   cps_state, init_sk2h22,   ROT0,   "bootleg",         "Sangokushi II: Sheng Jian Sanguo (Chinese bootleg set 2, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofsjb,          wof,      sk2h35,     wof,      cps_state, init_sk2h35,   ROT0,   "bootleg",         "Sangokushi II: Sheng Jian Sanguo (Chinese bootleg set 3, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofsjc,          wof,      sk2h31,     sk2h31,   cps_state, init_sk2h22,   ROT0,   "bootleg",         "Sangokushi II: Sheng Jian Sanguo (Chinese bootleg set 4, 921005 Asia)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofjd,           wof,      qsound,     wof,      cps_state, init_wof,      ROT0,   "bootleg",         "Tenchi wo Kurau II (Japan 921031 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )
GAME( 1992, wofud,           wof,      qsound,     wof,      cps_state, init_wof,      ROT0,   "bootleg",         "Warriors of Fate (USA 921031 Phoenix Edition)", MACHINE_SUPPORTS_SAVE )



/********************
  Hack And Homebrow
***********************/

ROM_START( captcommhc01 ) //captcommr1pmy
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hc01.10f", 0x000000, 0x3024FA, CRC(ea8bebca) SHA1(38bd9dfa307c4486ac19ca45b4c7b8552b9257c8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhc02 ) //captcommr1pmy
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hc02.10f", 0x000000, 0x3024FA, CRC(b9625397) SHA1(5763bd8da4857f481e773b628b49236d72a44c07) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m.3a",  0x000000, 0x80000, CRC(7261d8ba) SHA1(4b66292e42d20d0b79a756f0e445492ddb9c6bbc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m.5a",  0x000002, 0x80000, CRC(6a60f949) SHA1(87391ff92abaf3e451f70d789a938cffbd1fd222) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m.4a",  0x000004, 0x80000, CRC(00637302) SHA1(2c554b59cceec2de67a9a4bc6281fe846d3c8cd2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m.6a",  0x000006, 0x80000, CRC(cc87cf61) SHA1(7fb1f49494cc1a08aded20754bb0cefb1c323198) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m.7a",  0x200000, 0x80000, CRC(28718bed) SHA1(dfdc4dd14dc609783bad94d608a9e9b137dea944) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m.9a",  0x200002, 0x80000, CRC(d4acc53a) SHA1(d03282ebbde362e679cc97f772aa9baf163d7606) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m.8a",  0x200004, 0x80000, CRC(0c69f151) SHA1(a170b8e568439e4a26d84376d53560e4248e4e2f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m.10a", 0x200006, 0x80000, CRC(1f9ebb97) SHA1(023d00cb7b6a52d1b29e2052abe08ef34cb0c55c) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( captcommhc03 ) //captre
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cc_28d_hc03.10f", 0x000000, 0x200000, CRC(591ea997) SHA1(b1197d87a2913e1ed3759021cce697b02e387638) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cc-5m_hc03.3a",  0x000000, 0x80000, CRC(d78482a8) SHA1(f813b943d5af13be49e66573f6a203dc6c214511) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-7m_hc03.5a",  0x000002, 0x80000, CRC(fe4f474d) SHA1(38db56ec3a803569e833d355f1f010a9a942a436) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-1m_hc03.4a",  0x000004, 0x80000, CRC(e45c8021) SHA1(23105ff4310209b69823c6203da3072bf11391da) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-3m_hc03.6a",  0x000006, 0x80000, CRC(0d7f9314) SHA1(c3feab47c77fb6453164ef1881e58fd6a3be032d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-6m_hc03.7a",  0x200000, 0x80000, CRC(bd687ae8) SHA1(c8e410b7087b64732a641bf1adaa33a5b6b2e6ae) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-8m_hc03.9a",  0x200002, 0x80000, CRC(f222c02e) SHA1(407b31717207e59b11f72288e024049bc6c8d813) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-2m_hc03.8a",  0x200004, 0x80000, CRC(8296149a) SHA1(c3fea7a8f08940d1917a22299adda125af9dca9e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cc-4m_hc03.10a", 0x200006, 0x80000, CRC(a7b9288e) SHA1(e0fc0f2ca6f016ef41316380d8dd9bbab0988f0b) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "cc_09.11a",  0x00000, 0x08000, CRC(698e8b58) SHA1(b7a3d905a7ed2c430426ca2e185e3d7e75e752a1) )
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "cc_18.11c",  0x00000, 0x20000, CRC(6de2c2db) SHA1(9a1eaba8d104f59a5e61f89679bb5de0c0c64364) )
	ROM_LOAD( "cc_19.12c",  0x20000, 0x20000, CRC(b99091ae) SHA1(b19197c7ad3aeaf5f41c26bf853b0c9b502ecfca) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "captcomm.key", 0x00, 0x80, CRC(3bd9c940) SHA1(8964479f402ce7e000f1da8b3f6386e6915269e1) )
ROM_END

ROM_START( dinohc01 ) //dinoxlb2
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23_hc01.8f",  0x000000, 0x80000, CRC(f9b0a08b) SHA1(c7c5e83f2be67ecc9437b96b6089f5523c0bc7dc) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc01.7f",  0x080000, 0x80000, CRC(bcedf0b5) SHA1(c7cff6202ff5f18b03a6891f33de839705571ffb) )
	ROM_LOAD16_WORD_SWAP( "cde_21a.6f", 0x100000, 0x80000, CRC(66d23de2) SHA1(19b8a365f630411d524d055459020f4c8cf930f1) )
	ROM_LOAD16_WORD_SWAP( "cde_20_hc01.5f",  0x180000, 0x80000, CRC(36ce97ab) SHA1(c0b69a3d9e8d7d8458470caa1ae20d766b6c7972) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc02 ) //dinoext
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_28d_hc02.10f", 0x000000, 0x200000, CRC(a54b4c50) SHA1(be68456734de27d5fdba5d1e7fa63d355f6539c8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc03 ) //dinosdj
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23_hc03.8f",  0x000000, 0x80000, CRC(ca9b534f) SHA1(c22ed71ad4d6bfb825d060b5538d9d877e5c7895) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc03.7f",  0x080000, 0x80000, CRC(df3260c2) SHA1(7a328531c559e41fdc4da6c91a5c69294af02c54) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc03.6f",  0x100000, 0x80000, CRC(db855662) SHA1(cf5281ecb4925c74469623cec251702704cc7cfe) )
	ROM_LOAD16_WORD_SWAP( "cde_21_hc03.5f",  0x180000, 0x80000, CRC(e663b7a9) SHA1(cbc85bde140280b81e96152d327ca6b4e9c346fd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc04 ) //dinosj
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23_hc04.8f",  0x000000, 0x80000, CRC(312670f5) SHA1(ff504e07cc3f5d33894afcd7a7d2b70022e61aab) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc04.7f",  0x080000, 0x80000, CRC(f74b5ab9) SHA1(182847ec69849583ef513d72f82967fcb0b96312) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc04.6f",  0x100000, 0x80000, CRC(2f9132a4) SHA1(4f24d9e44e1ebf9d76ad258029d181464ea987a6) )
	ROM_LOAD16_WORD_SWAP( "cde_21_hc04.5f",  0x180000, 0x80000, CRC(75660aac) SHA1(6a521e1d2a632c26e53b83d2cc4b0edecfc1e68c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc05 ) //dinotj2022
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23_hc05.8f",  0x000000, 0x80000, CRC(c4a2bc60) SHA1(03a237aa54c52b4387936edb8f3f8ebe968e166a) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc05.7f",  0x080000, 0x80000, CRC(44f28f0d) SHA1(c219e8f6dad44b760c78f3eb6d6265d257e07406) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc05.6f",  0x100000, 0x80000, CRC(26769e22) SHA1(95d36da3aeeb99f6dd74ef878a6477b361e15c62) )
	ROM_LOAD16_WORD_SWAP( "cde_21_hc05.5f",  0x180000, 0x80000, CRC(4e655871) SHA1(4151440cf1c9b9ed84553a60276f9536887f61d8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc06 ) //dinosj
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23_hc06.8f",  0x000000, 0x80000, CRC(34a60e53) SHA1(77cc4879eeb7e344a12b0025925abdd4edac2dad) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc06.7f",  0x080000, 0x80000, CRC(8c28ca74) SHA1(d5e9c68888a8a7b1f4cfe8ac584e32015653f7f5) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc04.6f",  0x100000, 0x80000, CRC(2f9132a4) SHA1(4f24d9e44e1ebf9d76ad258029d181464ea987a6) )
	ROM_LOAD16_WORD_SWAP( "cde_21_hc04.5f",  0x180000, 0x80000, CRC(75660aac) SHA1(6a521e1d2a632c26e53b83d2cc4b0edecfc1e68c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc07 ) //dinore
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_28d_hc07.10f", 0x000000, 0x200000, CRC(9e75c12c) SHA1(ffef2132b2fea12530dd971b0217b05d53c2affb) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc08 ) //dinodrnb
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23_hc08.8f",  0x000000, 0x80000, CRC(4dff66ef) SHA1(d1ed4e0893322cb6f736406e4899158a614eb34e) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc08.7f",  0x080000, 0x80000, CRC(069fb2be) SHA1(a57a5b602d570d9ac9124bc8ae756ed1441fca3e) )
	ROM_LOAD16_WORD_SWAP( "cde_21_hc08.6f",  0x100000, 0x80000, CRC(57113f04) SHA1(2f90baf996dc6c0cda2fcaa35d058e71c66bbb10) )
	ROM_LOAD16_WORD_SWAP( "cde_20_hc08.5f",  0x180000, 0x80000, CRC(34c200c8) SHA1(0e7de58221927184b6d5ea22fefc362237b51efc) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc09 ) //dinosyn
	ROM_REGION( 0x400000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_28d_hc09.10f", 0x000000, 0x200000, CRC(8497004b) SHA1(ffba706a272926ac19a85b0403f6f1d4c622e89d) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( dinohc10 ) //dinotxj
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "cde_23_hc10.8f",  0x000000, 0x80000, CRC(94a5e1ca) SHA1(e99fff76db106e40676ea471bafc0b97290a7008) )
	ROM_LOAD16_WORD_SWAP( "cde_22_hc10.7f",  0x080000, 0x80000, CRC(388c3a5d) SHA1(397a22c23e43270e99d0fe4dd42b93ee1ae8d261) )
	ROM_LOAD16_WORD_SWAP( "cde_21_hc10.6f",  0x100000, 0x80000, CRC(3d0354e9) SHA1(170b7ef06eef480aa592e8c58f6ba485b03602d3) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "cd-1m.3a",  0x000000, 0x80000, CRC(8da4f917) SHA1(4f7b2304b7d9b545d6707d7ec921d3e28200699d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-3m.5a",  0x000002, 0x80000, CRC(6c40f603) SHA1(cdbd11dfcec08e87355d7e21e9fd39f7eacab016) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-2m.4a",  0x000004, 0x80000, CRC(09c8fc2d) SHA1(d0c0a1258ec5dd484ab6ec1c5663425431f929ee) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-4m.6a",  0x000006, 0x80000, CRC(637ff38f) SHA1(859926b33b9955b3ed67471c61faa442d42b9696) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-5m.7a",  0x200000, 0x80000, CRC(470befee) SHA1(a42e38319e9b7424381352512f11bd8edf0bbb96) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-7m.9a",  0x200002, 0x80000, CRC(22bfb7a3) SHA1(c44959bd3d42b9fc8ecb482dfaf63fbd469d2c3e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-6m.8a",  0x200004, 0x80000, CRC(e7599ac4) SHA1(0e788a38547a8701115d01190ddeaca64388db4d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "cd-8m.10a", 0x200006, 0x80000, CRC(211b4b15) SHA1(374f6b185faa0f14f5c45b9b1d60d0772d93fb17) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "cd_q.5k",    0x00000, 0x08000, CRC(605fdb0b) SHA1(9da90ddc6513aaaf2260f0c69719c6b0e585ba8c) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "cd-q1.1k",   0x000000, 0x80000, CRC(60927775) SHA1(f8599bc84c38573ebbe8685822c58b6a38b50462) )
	ROM_LOAD( "cd-q2.2k",   0x080000, 0x80000, CRC(770f4c47) SHA1(fec8ef00a6669d4d5e37787ecc7b58ee46709326) )
	ROM_LOAD( "cd-q3.3k",   0x100000, 0x80000, CRC(2f273ffc) SHA1(f0de462f6c4d251911258e0ebd886152c14d1586) )
	ROM_LOAD( "cd-q4.4k",   0x180000, 0x80000, CRC(2c67821d) SHA1(6e2528d0b22508300a6a142a796dd3bf53a66946) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "dino.key", 0x00, 0x80, CRC(230b6eb0) SHA1(240fdda90aecd62ce1f218e430b7ee6a464b8de8) )
ROM_END

ROM_START( forgottnhc01 )
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "lwu_11a_hc01.14f",    0x00000, 0x20000, CRC(1a822120) SHA1(9fe347e2efb76f47f68505c85e5848f389e1c6d5) )
	ROM_LOAD16_BYTE( "lwu_15a_hc01.14g",    0x00001, 0x20000, CRC(6f5c01e6) SHA1(6066daef1590262c67f266a9f18401c46e13ccec) )
	ROM_LOAD16_BYTE( "lwu_10a.13f",    0x40000, 0x20000, CRC(8cb38c81) SHA1(1d36cab7d17ff778ee7dfcd9606a3a87f6906f21) )
	ROM_LOAD16_BYTE( "lwu_14a.13g",    0x40001, 0x20000, CRC(d70ef9fd) SHA1(b393aa2a7bea440fdcf057ffc6ff233fc0d35d4b) )
	ROM_LOAD16_WORD_SWAP( "lw-07.13e", 0x80000, 0x80000, CRC(fd252a26) SHA1(5cfb097984912a5167a8c7ec4c2e119b642f9970) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "lw-01.9d",  0x000000, 0x80000, CRC(0318f298) SHA1(178ffd6da7bf845e30abf1bfc38a469cd319a73f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "lw-08.9f",  0x000002, 0x80000, CRC(25a8e43c) SHA1(d57cee1fc508db2677e84882fb814e4d9ad20543) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "lw-05.9e",  0x000004, 0x80000, CRC(e4552fd7) SHA1(11147afc475904848458425661473586dd6f60cc) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "lw-12.9g",  0x000006, 0x80000, CRC(8e6a832b) SHA1(d63a1331fda2365f090fa31950098f321a720ea8) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "lw-02.12d", 0x200000, 0x80000, CRC(43e6c5c8) SHA1(d3e6c971de0477ec4e178adc82508208dd8b397f) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "lw-09.12f", 0x200002, 0x80000, CRC(899cb4ad) SHA1(95e61af338945e690f2a82746feba3871ea224eb) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "lw-06.12e", 0x200004, 0x80000, CRC(5b9edffc) SHA1(6fd8f4a3ab070733b52365ab1945bf86acb2bf62) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "lw-13.12g", 0x200006, 0x80000, CRC(8e058ef5) SHA1(00f2c0050fd106276ea5398511c5861ebfbc0d10) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x8000, "stars", 0 )
	ROM_COPY( "gfx", 0x200000, 0x000000, 0x8000 )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "lwu_00.14a", 0x00000, 0x08000, CRC(59df2a63) SHA1(dfe1fffc7a17179a80a2ae623e93b30a7d6df20d) )    // == lw_00b.14a
	ROM_CONTINUE(           0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 ) /* Samples */
	ROM_LOAD( "lw-03u.14c", 0x00000, 0x20000, CRC(807d051f) SHA1(720e4733787b9b11f4d1cdce0892b69475802844) )
	ROM_LOAD( "lw-04u.13c", 0x20000, 0x20000, CRC(e6cd098e) SHA1(667f6e5736f76a1c4c450c4e2035574ea89d7910) )

	ROM_REGION( 0x0200, "aboardplds", 0 )
	ROM_LOAD( "buf1",         0x0000, 0x0117, CRC(eb122de7) SHA1(b26b5bfe258e3e184f069719f9fd008d6b8f6b9b) )
	ROM_LOAD( "ioa1",         0x0000, 0x0117, CRC(59c7ee3b) SHA1(fbb887c5b4f5cb8df77cec710eaac2985bc482a6) )
	ROM_LOAD( "prg1",         0x0000, 0x0117, CRC(f1129744) SHA1(a5300f301c1a08a7da768f0773fa0fe3f683b237) )
	ROM_LOAD( "rom1",         0x0000, 0x0117, CRC(41dc73b9) SHA1(7d4c9f1693c821fbf84e32dd6ef62ddf14967845) )
	ROM_LOAD( "sou1",         0x0000, 0x0117, CRC(84f4b2fe) SHA1(dcc9e86cc36316fe42eace02d6df75d08bc8bb6d) )

	ROM_REGION( 0x0200, "bboardplds", 0 )
	ROM_LOAD( "lwchr.3a",     0x0000, 0x0117, CRC(54ed4c39) SHA1(961309335dc1c84482ebe99ea938b32d3a6ae9a8) )
	ROM_LOAD( "lwio.15e",     0x0000, 0x0117, CRC(ad52b90c) SHA1(f0fd6aeea515ee449320fe15684e6b3ab7f97bf4) )
ROM_END

ROM_START( mswordhc01 ) //mswordr1
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "mse_30_hc01.11f", 0x00000, 0x20000, CRC(2d877bfc) SHA1(3f1bc58192fc7023aab00243313883fb68e09b9b) )
	ROM_LOAD16_BYTE( "mse_35_hc01.11h", 0x00001, 0x20000, CRC(112323cc) SHA1(a44f9f3d84ff5def1cdc59f27d6fd90222b17e2a) )
	ROM_LOAD16_BYTE( "mse_31_hc01.12f", 0x40000, 0x20000, CRC(028b1de0) SHA1(3cecbdcb9f7a3ad9817be7691572e54ea64d3a01) )
	ROM_LOAD16_BYTE( "mse_36_hc01.12h", 0x40001, 0x20000, CRC(7e5ba1c1) SHA1(9327868ea2b4015d075d849ba082a5e86b467012) )
	ROM_LOAD16_WORD_SWAP( "ms-32m.8h", 0x80000, 0x80000, CRC(2475ddfc) SHA1(cc34dfae8124aa781320be6870a1929495eee456) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "ms-5m.7a", 0x000000, 0x80000, CRC(c00fe7e2) SHA1(1ce82ea36996908620d3ac8aabd3650118d6c255) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ms-7m.9a", 0x000002, 0x80000, CRC(4ccacac5) SHA1(f2e30edf6ad100da411584bb0b828420256a9d5c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ms-1m.3a", 0x000004, 0x80000, CRC(0d2bbe00) SHA1(dca13fc7ff63ad7fb175a71ada1ee22d21a8811d) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ms-3m.5a", 0x000006, 0x80000, CRC(3a1a5bf4) SHA1(88a7cc0bf29b3516a97f661691500ff28e91a362) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "ms_09.12b", 0x00000, 0x08000, CRC(57b29519) SHA1(a6b4fc2b9595d1a49f2b93581f107b68d484d156) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "ms_18.11c", 0x00000, 0x20000, CRC(fb64e90d) SHA1(d1a596ce2f8ac14a80b34335b173369a14b45f55) )
	ROM_LOAD( "ms_19.12c", 0x20000, 0x20000, CRC(74f892b9) SHA1(bf48db5c438154e7b96fd31fde1be4aad5cf25eb) )

	ROM_REGION( 0x0200, "aboardplds", 0 )
	ROM_LOAD( "buf1",         0x0000, 0x0117, CRC(eb122de7) SHA1(b26b5bfe258e3e184f069719f9fd008d6b8f6b9b) )
	ROM_LOAD( "ioa1",         0x0000, 0x0117, CRC(59c7ee3b) SHA1(fbb887c5b4f5cb8df77cec710eaac2985bc482a6) )
	ROM_LOAD( "prg1",         0x0000, 0x0117, CRC(f1129744) SHA1(a5300f301c1a08a7da768f0773fa0fe3f683b237) )
	ROM_LOAD( "rom1",         0x0000, 0x0117, CRC(41dc73b9) SHA1(7d4c9f1693c821fbf84e32dd6ef62ddf14967845) )
	ROM_LOAD( "sou1",         0x0000, 0x0117, CRC(84f4b2fe) SHA1(dcc9e86cc36316fe42eace02d6df75d08bc8bb6d) )

	ROM_REGION( 0x0200, "bboardplds", 0 )
	ROM_LOAD( "ms24b.1a",     0x0000, 0x0117, CRC(636dbe6d) SHA1(6622a2294f82e70e9eb5ff24f84e0dc13e9168b5) )
	ROM_LOAD( "iob1.11e",     0x0000, 0x0117, CRC(3abc0700) SHA1(973043aa46ec6d5d1db20dc9d5937005a0f9f6ae) )
ROM_END

ROM_START( kodhc01 ) //kodlys
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kdu_hc01.10", 0x000000, 0x200000, CRC(f3ba8023) SHA1(0aa73e858f2cdc19c02153c5dabd1ba1579962a9) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_09.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

ROM_START( kodhc02 ) //koduyh
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kdu_hc02.10", 0x000000, 0x200000, CRC(bc291aec) SHA1(474aceabfec6f6da3eff1d2b85996a5dc27aefc7) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_09.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

ROM_START( kodhc03 ) //koduyh
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kdu_hc03.10", 0x000000, 0x200000, CRC(135a0284) SHA1(b523c8e74641bbb4c377b901c4707b09969802dd) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_09.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

ROM_START( kodhc04 ) //kodlys
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kdu_hc04.10", 0x000000, 0x200000, CRC(d6666c1c) SHA1(27244572097b6747f93d416ae3980c6ff8f25012) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_09.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

ROM_START( kodhc05 ) //kodlys
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kdu_hc05.10", 0x000000, 0x200000, CRC(e438011d) SHA1(2b998a49a69693dcec688ad89a590c49f6561d62) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_09.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

ROM_START( kodhc06 ) //koduyh
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kdu_hc06.10", 0x000000, 0x200000, CRC(14aaaf74) SHA1(2324ab08f9fc15a3a632ada7da6edac5d78a5264) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_09.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

ROM_START( kodhc07 ) //koduyh
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kdu_hc07.10", 0x000000, 0x200000, CRC(e6226702) SHA1(cfbaef465c7854bf086e14db438f58c6fc768923) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_09.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

ROM_START( kodhc08 ) //kodlys
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "kdu_hc08.10", 0x000000, 0x200000, CRC(c448de2e) SHA1(94da22f6bb1b29bf8d2a9b1b35eb213bf54ac4f8) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "kd-5m.4a", 0x000000, 0x80000, CRC(e45b8701) SHA1(604e39e455e81695ee4f899f102d0bcd789cedd0) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-7m.6a", 0x000002, 0x80000, CRC(a7750322) SHA1(3c583496a53cd64edf377db35f7f40f02b59b7e7) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-1m.3a", 0x000004, 0x80000, CRC(5f74bf78) SHA1(b7c43eea9bf77a0fb571dcd53f8be719e6655fd9) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-3m.5a", 0x000006, 0x80000, CRC(5e5303bf) SHA1(d9f90b898ffdf4398b2bbeb48247f06f728e7c00) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-6m.4c", 0x200000, 0x80000, CRC(113358f3) SHA1(9d98eafa74a046f65bf3847fe1d88ea1b0c82b0c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-8m.6c", 0x200002, 0x80000, CRC(38853c44) SHA1(a6e552fb0138a76a7878b90d202904e2b44ae7ec) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-2m.3c", 0x200004, 0x80000, CRC(9ef36604) SHA1(b42ca0a910b65e1e7bb6e7d734e853ce67e821bf) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "kd-4m.5c", 0x200006, 0x80000, CRC(402b9b4f) SHA1(4c11976976eadf1ad293b31b0a4d047d05032b06) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "kd_09.12a", 0x00000, 0x08000, CRC(bac6ec26) SHA1(6cbb6d55660150ae3f5270e023328275ee1bbf50) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "kd_18.11c", 0x00000, 0x20000, CRC(4c63181d) SHA1(270f27534a95cb0be3ff3f9ca71c502320d8090b) )
	ROM_LOAD( "kd_19.12c", 0x20000, 0x20000, CRC(92941b80) SHA1(5fa7c2793e6febee54a83042d118ddd4f2b7d127) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "kod.key", 0x00, 0x80, CRC(b79ea9b9) SHA1(cefded329a6ccc34d3b68e614c8f3a2c174e3fdd) )
ROM_END

ROM_START( punisherhc01 ) //punisherbs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26_hc01.11e",    0x000000, 0x20000, CRC(65fdd6d9) SHA1(873f6cffab1a05def1635c050dbdfc4e78837e56) )
	ROM_LOAD16_BYTE( "pse_30_hc01.11f",    0x000001, 0x20000, CRC(17642b39) SHA1(a695e45db650b0ed6b53b1649a9d0d312dae1346) )
	ROM_LOAD16_BYTE( "pse_27_hc01.12e",    0x040000, 0x20000, CRC(6001fc4e) SHA1(b40512c4377f26c587d73cdde5d5576ad7e43c10) )
	ROM_LOAD16_BYTE( "pse_31_hc01.12f",    0x040001, 0x20000, CRC(91cdffcc) SHA1(b29d6b84a83f1ff4555472fa03ff052af206cbdc) )
	ROM_LOAD16_BYTE( "pse_24_hc01.9e",     0x080000, 0x20000, CRC(98cbce17) SHA1(573f07056f4af359de4bf9e1bc1b61fdf0fd15c1) )
	ROM_LOAD16_BYTE( "pse_28_hc01.9f",     0x080001, 0x20000, CRC(0eb838ab) SHA1(90d4f22fc09fe68b5e1c62c94805d6f2773ea7cf) )
	ROM_LOAD16_BYTE( "pse_25_hc01.10e",    0x0c0000, 0x20000, CRC(0d44c406) SHA1(ac5f58cbb83d6abd8bf004be99063e85406c3518) )
	ROM_LOAD16_BYTE( "pse_29_hc01.10f",    0x0c0001, 0x20000, CRC(ed6ffd6d) SHA1(c808003cd47bb4f192e377b49dc4d1efee97f2b9) )
	ROM_LOAD16_WORD_SWAP( "ps_21_hc01.6f", 0x100000, 0x80000, CRC(9c0e870a) SHA1(7346d1515ae866f143ba0dd077128ca209add241) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hc01.3a",  0x000000, 0x80000, CRC(4d4111de) SHA1(f67002f6a9073f5aba33e31879fc7f4c1d60ffda) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hc01.5a",  0x000002, 0x80000, CRC(2d346b82) SHA1(dfd48382fdc8d1da5ece31a8ed99a0fa9f58c1ed) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hc01.4a",  0x000004, 0x80000, CRC(5e0c85a1) SHA1(3b2487d8ae60d2beabafd83007359a84d3d0079e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hc01.6a",  0x000006, 0x80000, CRC(4ccc5b41) SHA1(1176458dccd129f19952fbafb85a7629b29b1ee3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m_hc01.7a",  0x200000, 0x80000, CRC(ebb91780) SHA1(07a98ee8cde2fa0555baf6894312b8f2aba91ba3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m_hc01.9a",  0x200002, 0x80000, CRC(f0c1d356) SHA1(821810342f662fb06cbe304651e2a965d7ca452c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m_hc01.8a",  0x200004, 0x80000, CRC(51ca7a4b) SHA1(19a378e0b0f9e751902b86913e52188597dad940) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m_hc01.10a", 0x200006, 0x80000, CRC(4a4854f9) SHA1(315c9f6d1dc0dee522424f92d6df647cae9992e9) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhc02 ) //punisherbs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26_hc02.11e",    0x000000, 0x20000, CRC(cec66e5f) SHA1(9020758b5ab0801f40ef8bf72f68687f94e7730a) )
	ROM_LOAD16_BYTE( "pse_30_hc02.11f",    0x000001, 0x20000, CRC(4762bdd2) SHA1(2a3095a2452bf4885840172dadcbe77de72cb56a) )
	ROM_LOAD16_BYTE( "pse_27_hc01.12e",    0x040000, 0x20000, CRC(6001fc4e) SHA1(b40512c4377f26c587d73cdde5d5576ad7e43c10) )
	ROM_LOAD16_BYTE( "pse_31_hc01.12f",    0x040001, 0x20000, CRC(91cdffcc) SHA1(b29d6b84a83f1ff4555472fa03ff052af206cbdc) )
	ROM_LOAD16_BYTE( "pse_24_hc02.9e",     0x080000, 0x20000, CRC(358c4155) SHA1(5637c70f8bca8dc7e2d4fc4f7d2638c93ee02832) )
	ROM_LOAD16_BYTE( "pse_28_hc02.9f",     0x080001, 0x20000, CRC(4272ec19) SHA1(5d01c03617f2038807aee7e83514a8a08f6e94c7) )
	ROM_LOAD16_BYTE( "pse_25_hc02.10e",    0x0c0000, 0x20000, CRC(fdc61c32) SHA1(6009620f891b0f840707cca70f2a4e7d0e659624) )
	ROM_LOAD16_BYTE( "pse_29_hc02.10f",    0x0c0001, 0x20000, CRC(eb3d2a38) SHA1(58de626007dc489fe5a595e670444e4613c76ae2) )
	ROM_LOAD16_WORD_SWAP( "ps_21_hc02.6f", 0x100000, 0x80000, CRC(3d3d924e) SHA1(4dcc43ee447cd1932ef87f4c6e501cc96b2b5c6a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hc01.3a",  0x000000, 0x80000, CRC(4d4111de) SHA1(f67002f6a9073f5aba33e31879fc7f4c1d60ffda) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hc01.5a",  0x000002, 0x80000, CRC(2d346b82) SHA1(dfd48382fdc8d1da5ece31a8ed99a0fa9f58c1ed) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hc01.4a",  0x000004, 0x80000, CRC(5e0c85a1) SHA1(3b2487d8ae60d2beabafd83007359a84d3d0079e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hc01.6a",  0x000006, 0x80000, CRC(4ccc5b41) SHA1(1176458dccd129f19952fbafb85a7629b29b1ee3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m_hc01.7a",  0x200000, 0x80000, CRC(ebb91780) SHA1(07a98ee8cde2fa0555baf6894312b8f2aba91ba3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m_hc01.9a",  0x200002, 0x80000, CRC(f0c1d356) SHA1(821810342f662fb06cbe304651e2a965d7ca452c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m_hc01.8a",  0x200004, 0x80000, CRC(51ca7a4b) SHA1(19a378e0b0f9e751902b86913e52188597dad940) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m_hc01.10a", 0x200006, 0x80000, CRC(4a4854f9) SHA1(315c9f6d1dc0dee522424f92d6df647cae9992e9) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhc03 ) //punisherbs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26_hc03.11e",    0x000000, 0x20000, CRC(d7d34806) SHA1(bc1a92f412f2c60aa3158710c40aa253d2a838ff) )
	ROM_LOAD16_BYTE( "pse_30_hc03.11f",    0x000001, 0x20000, CRC(536727b7) SHA1(a83ed52903ea94ef540858b926822654038651e3) )
	ROM_LOAD16_BYTE( "pse_27_hc01.12e",    0x040000, 0x20000, CRC(6001fc4e) SHA1(b40512c4377f26c587d73cdde5d5576ad7e43c10) )
	ROM_LOAD16_BYTE( "pse_31_hc03.12f",    0x040001, 0x20000, CRC(b7c48b12) SHA1(9713a4c776d6cc77e1ea97e47046a547b49ce78c) )
	ROM_LOAD16_BYTE( "pse_24_hc03.9e",     0x080000, 0x20000, CRC(b91ad6db) SHA1(33e62ea6e36815a101749b7aa4b63071f6edc90b) )
	ROM_LOAD16_BYTE( "pse_28_hc03.9f",     0x080001, 0x20000, CRC(c2e1f0e1) SHA1(3b3cb8cce9836094583de8b352d84ccff2e2e867) )
	ROM_LOAD16_BYTE( "pse_25_hc03.10e",    0x0c0000, 0x20000, CRC(229ade49) SHA1(029e59f1238209630057aea8458101dcbf4a1dde) )
	ROM_LOAD16_BYTE( "pse_29_hc03.10f",    0x0c0001, 0x20000, CRC(068191db) SHA1(ac5a52b34dce11affb758b8bf49436d38e81f5d3) )
	ROM_LOAD16_WORD_SWAP( "ps_21_hc02.6f", 0x100000, 0x80000, CRC(3d3d924e) SHA1(4dcc43ee447cd1932ef87f4c6e501cc96b2b5c6a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hc01.3a",  0x000000, 0x80000, CRC(4d4111de) SHA1(f67002f6a9073f5aba33e31879fc7f4c1d60ffda) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hc01.5a",  0x000002, 0x80000, CRC(2d346b82) SHA1(dfd48382fdc8d1da5ece31a8ed99a0fa9f58c1ed) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hc01.4a",  0x000004, 0x80000, CRC(5e0c85a1) SHA1(3b2487d8ae60d2beabafd83007359a84d3d0079e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hc01.6a",  0x000006, 0x80000, CRC(4ccc5b41) SHA1(1176458dccd129f19952fbafb85a7629b29b1ee3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m_hc01.7a",  0x200000, 0x80000, CRC(ebb91780) SHA1(07a98ee8cde2fa0555baf6894312b8f2aba91ba3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m_hc01.9a",  0x200002, 0x80000, CRC(f0c1d356) SHA1(821810342f662fb06cbe304651e2a965d7ca452c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m_hc01.8a",  0x200004, 0x80000, CRC(51ca7a4b) SHA1(19a378e0b0f9e751902b86913e52188597dad940) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m_hc01.10a", 0x200006, 0x80000, CRC(4a4854f9) SHA1(315c9f6d1dc0dee522424f92d6df647cae9992e9) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( punisherhc04 ) //punisherbs
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "pse_26_hc04.11e",    0x000000, 0x20000, CRC(6ff6c43c) SHA1(e9398f28a101966dd763752a0366f803a2e8125a) )
	ROM_LOAD16_BYTE( "pse_30_hc04.11f",    0x000001, 0x20000, CRC(7311ed93) SHA1(26c3c2c8589e512982354fb40a1e9371cadd04a0) )
	ROM_LOAD16_BYTE( "pse_27_hc01.12e",    0x040000, 0x20000, CRC(6001fc4e) SHA1(b40512c4377f26c587d73cdde5d5576ad7e43c10) )
	ROM_LOAD16_BYTE( "pse_31_hc04.12f",    0x040001, 0x20000, CRC(7edd39dc) SHA1(1715d3a7d73b8187e61fe70b26b242b22a9d39b5) )
	ROM_LOAD16_BYTE( "pse_24_hc03.9e",     0x080000, 0x20000, CRC(b91ad6db) SHA1(33e62ea6e36815a101749b7aa4b63071f6edc90b) )
	ROM_LOAD16_BYTE( "pse_28_hc04.9f",     0x080001, 0x20000, CRC(c34fe962) SHA1(e84a93b45f0ff00b7a2ebae21f74d90ac4c5b352) )
	ROM_LOAD16_BYTE( "pse_25_hc04.10e",    0x0c0000, 0x20000, CRC(a28b083f) SHA1(d458342504ff259e2e6090bcdb9fa08aa5bf6ff3) )
	ROM_LOAD16_BYTE( "pse_29_hc04.10f",    0x0c0001, 0x20000, CRC(41b7bff6) SHA1(c6ab99a77c99cedcca6169e4f864034f38073218) )
	ROM_LOAD16_WORD_SWAP( "ps_21_hc02.6f", 0x100000, 0x80000, CRC(3d3d924e) SHA1(4dcc43ee447cd1932ef87f4c6e501cc96b2b5c6a) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "ps-1m_hc01.3a",  0x000000, 0x80000, CRC(4d4111de) SHA1(f67002f6a9073f5aba33e31879fc7f4c1d60ffda) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-3m_hc01.5a",  0x000002, 0x80000, CRC(2d346b82) SHA1(dfd48382fdc8d1da5ece31a8ed99a0fa9f58c1ed) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-2m_hc01.4a",  0x000004, 0x80000, CRC(5e0c85a1) SHA1(3b2487d8ae60d2beabafd83007359a84d3d0079e) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-4m_hc01.6a",  0x000006, 0x80000, CRC(4ccc5b41) SHA1(1176458dccd129f19952fbafb85a7629b29b1ee3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-5m_hc01.7a",  0x200000, 0x80000, CRC(ebb91780) SHA1(07a98ee8cde2fa0555baf6894312b8f2aba91ba3) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-7m_hc01.9a",  0x200002, 0x80000, CRC(f0c1d356) SHA1(821810342f662fb06cbe304651e2a965d7ca452c) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-6m_hc01.8a",  0x200004, 0x80000, CRC(51ca7a4b) SHA1(19a378e0b0f9e751902b86913e52188597dad940) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "ps-8m_hc01.10a", 0x200006, 0x80000, CRC(4a4854f9) SHA1(315c9f6d1dc0dee522424f92d6df647cae9992e9) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "ps_q.5k",    0x00000, 0x08000, CRC(49ff4446) SHA1(87af12f87a940a6c5428b4574ad44a4b54867bc3) )
	ROM_CONTINUE(           0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "ps-q1.1k",   0x000000, 0x80000, CRC(31fd8726) SHA1(1d73a76682e9fb908db0c55b9a18163f7539fea1) )
	ROM_LOAD( "ps-q2.2k",   0x080000, 0x80000, CRC(980a9eef) SHA1(36571381f349bc726508a7e618ba1c635ec9d271) )
	ROM_LOAD( "ps-q3.3k",   0x100000, 0x80000, CRC(0dd44491) SHA1(903cea1d7f3120545ea3229d30fbd687d11ad68f) )
	ROM_LOAD( "ps-q4.4k",   0x180000, 0x80000, CRC(bed42f03) SHA1(21302f7e75f9c795392a3b34e16a959fc5f6e4e9) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD ( "punisher.key", 0x00, 0x80, CRC(8e992ffa) SHA1(4f09427600cef4feb49a8a488caadaaa7b327484) )
ROM_END

ROM_START( tk2hc01 ) //wofjdr
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc01.10f", 0x000000, 0x200000, CRC(edb36c36) SHA1(45bb34d3527602290045c3373aab7f6c44911553) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.7a",    0x200000, 0x80000, CRC(e3c8c198) SHA1(f31f9f5c41d94ff84d29ed787d9104ee3fc1a7aa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.8a",    0x200002, 0x80000, CRC(5e3c0642) SHA1(8ee6834b1d497c4e4724b1db48d61df558fd0e93) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.9a",    0x200004, 0x80000, CRC(d65a91d9) SHA1(4e1fa66c25fb4e28e49a458500089094cb54a308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.10a",   0x200006, 0x80000, CRC(675d490e) SHA1(180deb2aff5c2e35cc0eaaed8e6d5d490beaa5ea) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( tk2hc02 ) //wofjdr2020
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc02.8f",  0x000000, 0x80000, CRC(8a53c987) SHA1(132a2a1dd5c4dd4d37081b751114c8fab602a104) )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc02.7f",  0x080000, 0x80000, CRC(16405a96) SHA1(647b2a517b6937a2654039e932a98f636349670c) )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc02.6f",  0x100000, 0x80000, CRC(bb627bd9) SHA1(18f97eb3a0530d31d8ab7dd611f2c0ef500835d3) )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc02.5f",  0x180000, 0x80000, CRC(75660aac) SHA1(6a521e1d2a632c26e53b83d2cc4b0edecfc1e68c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.7a",    0x200000, 0x80000, CRC(e3c8c198) SHA1(f31f9f5c41d94ff84d29ed787d9104ee3fc1a7aa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.8a",    0x200002, 0x80000, CRC(5e3c0642) SHA1(8ee6834b1d497c4e4724b1db48d61df558fd0e93) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.9a",    0x200004, 0x80000, CRC(d65a91d9) SHA1(4e1fa66c25fb4e28e49a458500089094cb54a308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.10a",   0x200006, 0x80000, CRC(675d490e) SHA1(180deb2aff5c2e35cc0eaaed8e6d5d490beaa5ea) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( tk2hc03 ) //wofjdr2020
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc03.8f",  0x000000, 0x80000, CRC(9ce89a09) SHA1(e00df9ddacf28b16d420fb22eae4cf9065b9107f) )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc02.7f",  0x080000, 0x80000, CRC(16405a96) SHA1(647b2a517b6937a2654039e932a98f636349670c) )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc03.6f",  0x100000, 0x80000, CRC(9d14c411) SHA1(e4b3a6fc2a6674dc931e5e7b0862f5eb18eff7c9) )
	ROM_LOAD16_WORD_SWAP( "tk2h_hc02.5f",  0x180000, 0x80000, CRC(75660aac) SHA1(6a521e1d2a632c26e53b83d2cc4b0edecfc1e68c) )

	ROM_REGION( 0x400000, "gfx", 0 )
	ROMX_LOAD( "tk2-1m.3a",  0x000000, 0x80000, CRC(0d9cb9bf) SHA1(cc7140e9a01a14b252cb1090bcea32b0de461928) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-3m.5a",  0x000002, 0x80000, CRC(45227027) SHA1(b21afc593f0d4d8909dfa621d659cbb40507d1b2) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-2m.4a",  0x000004, 0x80000, CRC(c5ca2460) SHA1(cbe14867f7b94b638ca80db7c8e0c60881183469) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2-4m.6a",  0x000006, 0x80000, CRC(e349551c) SHA1(1d977bdf256accf750ad9930ec4a0a19bbf86964) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.7a",    0x200000, 0x80000, CRC(e3c8c198) SHA1(f31f9f5c41d94ff84d29ed787d9104ee3fc1a7aa) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.8a",    0x200002, 0x80000, CRC(5e3c0642) SHA1(8ee6834b1d497c4e4724b1db48d61df558fd0e93) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.9a",    0x200004, 0x80000, CRC(d65a91d9) SHA1(4e1fa66c25fb4e28e49a458500089094cb54a308) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "tk2h_hc01.10a",   0x200006, 0x80000, CRC(675d490e) SHA1(180deb2aff5c2e35cc0eaaed8e6d5d490beaa5ea) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x28000, "audiocpu", 0 )
	ROM_LOAD( "tk2_qa.5k",   0x00000, 0x08000, CRC(c9183a0d) SHA1(d8b1d41c572f08581f8ab9eb878de77d6ea8615d) )
	ROM_CONTINUE(            0x10000, 0x18000 )

	ROM_REGION( 0x200000, "qsound", 0 )
	ROM_LOAD( "tk2-q1.1k",   0x000000, 0x80000, CRC(611268cf) SHA1(83ab059f2110fb25fdcff928d56b790fc1f5c975) )
	ROM_LOAD( "tk2-q2.2k",   0x080000, 0x80000, CRC(20f55ca9) SHA1(90134e9a9c4749bb65c728b66ea4dac1fd4d88a4) )
	ROM_LOAD( "tk2-q3.3k",   0x100000, 0x80000, CRC(bfcf6f52) SHA1(2a85ff3fc89b4cbabd20779ec12da2e116333c7c) )
	ROM_LOAD( "tk2-q4.4k",   0x180000, 0x80000, CRC(36642e88) SHA1(8ab25b19e2b67215a5cb1f3aa81b9d26009cfeb8) )

	ROM_REGION( 0x80, "control", 0 )
	ROM_LOAD( "wof.key", 0x00, 0x80, CRC(ef8848dd) SHA1(e500a89ddb16abb31c7cb45f8dbea922d01fccc1) )
ROM_END

ROM_START( varthhc01 ) //varthr1
	ROM_REGION( CODE_SIZE, "maincpu", 0 )
	ROM_LOAD16_BYTE( "vae_30a_hc01.11f", 0x00000, 0x20000, CRC(214e4065) SHA1(2a6db38009a58baf10f2c297f585312852668267) )
	ROM_LOAD16_BYTE( "vae_35a_hc01.11h", 0x00001, 0x20000, CRC(5cd8eecd) SHA1(ca2ff59d940996b48c8a33b7b7b0556e682883ea) )
	ROM_LOAD16_BYTE( "vae_31b.12f", 0x40000, 0x20000, CRC(1749a71c) SHA1(bd9bfd5bbe2d426c94df755c977faa92a28f16ab) )
	ROM_LOAD16_BYTE( "vae_36b.12h", 0x40001, 0x20000, CRC(5f2e2450) SHA1(676e8d96406d81ceadd4a0a69959cdcb6d5d9ac8) )
	ROM_LOAD16_BYTE( "vae_28b.9f",  0x80000, 0x20000, CRC(e524ca50) SHA1(487d5ddabe852872f331362034c4fa16e0926e3d) )
	ROM_LOAD16_BYTE( "vae_33b.9h",  0x80001, 0x20000, CRC(c0bbf8c9) SHA1(447540b856776770af8022a291d46612c1bb5909) )
	ROM_LOAD16_BYTE( "vae_29b.10f", 0xc0000, 0x20000, CRC(6640996a) SHA1(3ed7bd947dc8224435680dedf4955ed6041c6028) )
	ROM_LOAD16_BYTE( "vae_34b.10h", 0xc0001, 0x20000, CRC(fa59be8a) SHA1(86a3d3a7126c021e2ca8ac20238695396367e098) )

	ROM_REGION( 0x200000, "gfx", 0 )
	ROMX_LOAD( "va-5m.7a", 0x000000, 0x80000, CRC(b1fb726e) SHA1(5ac0876b6c49d0a99710dda68653664f4d8c1167) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "va-7m.9a", 0x000002, 0x80000, CRC(4c6588cd) SHA1(d14e8cf051ac934ccc989d8c571c6cc9eed34af5) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "va-1m.3a", 0x000004, 0x80000, CRC(0b1ace37) SHA1(6f9493c22f667f683db2789972fd16bb94724679) , ROM_GROUPWORD | ROM_SKIP(6) )
	ROMX_LOAD( "va-3m.5a", 0x000006, 0x80000, CRC(44dfe706) SHA1(a013a434df3161a91aafbb35dc4e20dfb3f177f4) , ROM_GROUPWORD | ROM_SKIP(6) )

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "va_09.12b", 0x00000, 0x08000, CRC(7a99446e) SHA1(ca027f41e3e58be5abc33ad7380746658cb5380a) )
	ROM_CONTINUE(          0x10000, 0x08000 )

	ROM_REGION( 0x40000, "oki", 0 )
	ROM_LOAD( "va_18.11c", 0x00000, 0x20000, CRC(de30510e) SHA1(8e878696192606b76a3a0e53553e638d9621cff7) )
	ROM_LOAD( "va_19.12c", 0x20000, 0x20000, CRC(0610a4ac) SHA1(3da02ea6a7a56c85de898806d2a1cf6bc526c1b3) )

	ROM_LOAD ( "varth.key", 0x00, 0x80, CRC(9af7013d) SHA1(6182dfe656c25cc5ef009bfb1b5820ad3ce71c77) )
ROM_END

/*    YEAR  NAME         PARENT       MACHINE      INPUT                   INIT         MONITOR   COMPANY     FULLNAME FLAGS */
// Hack/Homebrow
GAME( 2022, captcommhc01, captcomm, cps1_10MHz,     captcomm, cps_state,   init_cps1,     ROT0,   "hack",      "Captain Commando (Nightmare Edition 2022-07-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, captcommhc02, captcomm, cps1_10MHz,     captcomm, cps_state,   init_cps1,     ROT0,   "hack",      "Captain Commando (Nightmare Edition 2022-07-18)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, captcommhc03, captcomm, cps1_10MHz,     captcomm, cps_state,   init_cps1,     ROT0,   "hack",      "Captain Commando (Adjusted Version 1.0 2022-08-01)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc01,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (Still Dagger Dragon Subduing Edition 2022-07-03)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc02,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (Fighting God Edition 2022-07-03)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc03,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (Triassic Edition 2020-07-14)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc04,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (Century Edition 2022-07-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc05,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (unknown description 2020-07-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc06,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (Century Edition 2022-07-20)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc07,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (Adjusted Version 1.2 2022-08-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc08,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (Master Boss 2022-05-09)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc09,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (30th Anniversary Edition 2022-09-04)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, dinohc10,     dino,     qsound,         dino,     cps_state,   init_dino,     ROT0,   "hack",      "Cadillacs and Dinosaurs (Dewar 2022-09-01)", MACHINE_SUPPORTS_SAVE )
GAME( 1988, forgottnhc01, forgottn, forgottn,       forgottn, cps_state,   init_cps1,     ROT0,   "hack",      "Forgotten Worlds (Unknown Description)", MACHINE_SUPPORTS_SAVE )
GAME( 1990, mswordhc01,   msword,   cps1_10MHz,     msword,   cps_state,   init_cps1,     ROT0,   "hack",      "Magic Sword: Heroic Fantasy (Unknown Description)", MACHINE_SUPPORTS_SAVE ) 
GAME( 2022, kodhc01,      kod,      cps1_10MHz,     kod,      cps_state,   init_cps1,     ROT0,   "hack",      "The King of Dragons (Dragon Slayer Edition 2022-06-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, kodhc02,      kod,      cps1_10MHz,     kod,      cps_state,   init_cps1,     ROT0,   "hack",      "The King of Dragons (Fireworks Edition 2022-06-28)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, kodhc03,      kod,      cps1_10MHz,     kod,      cps_state,   init_cps1,     ROT0,   "hack",      "The King of Dragons (Fireworks Edition 2022-07-07)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, kodhc04,      kod,      cps1_10MHz,     kod,      cps_state,   init_cps1,     ROT0,   "hack",      "The King of Dragons (Dragon Slayer Edition 2022-07-18)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, kodhc05,      kod,      cps1_10MHz,     kod,      cps_state,   init_cps1,     ROT0,   "hack",      "The King of Dragons (Dragon Slayer Edition 2022-07-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, kodhc06,      kod,      cps1_10MHz,     kod,      cps_state,   init_cps1,     ROT0,   "hack",      "The King of Dragons (Fireworks Edition 2022-08-16)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, kodhc07,      kod,      cps1_10MHz,     kod,      cps_state,   init_cps1,     ROT0,   "hack",      "The King of Dragons (Fireworks Edition 2022-08-22)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, kodhc08,      kod,      cps1_10MHz,     kod,      cps_state,   init_cps1,     ROT0,   "hack",      "The King of Dragons (Dragon Slayer Edition 2022-08-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, punisherhc01, punisher, qsound,         punisher, cps_state,   init_punisher, ROT0,   "hack",      "The Punisher (Framework Version 2020 Multi-Mode Enhancement 2022-07-24)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, punisherhc02, punisher, qsound,         punisher, cps_state,   init_punisher, ROT0,   "hack",      "The Punisher (Framework Version 2020 Multi-Mode Enhancement 2022-07-29)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, punisherhc03, punisher, qsound,         punisher, cps_state,   init_punisher, ROT0,   "hack",      "The Punisher (Framework Version 2020 Multi-Mode Enhancement 2022-08-12)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, punisherhc04, punisher, qsound,         punisher, cps_state,   init_punisher, ROT0,   "hack",      "The Punisher (Framework Version 2020 Multi-Mode Enhancement 2022-08-22)", MACHINE_SUPPORTS_SAVE )
GAME( 2020, tk2hc01,      wof,      qsound,         wof,      cps_state,   init_wof,      ROT0,   "hack",      "Tenchi wo Kurau II (Master Edition 2022-07-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, tk2hc02,      wof,      qsound,         wof,      cps_state,   init_wof,      ROT0,   "hack",      "Tenchi wo Kurau II (Unparalleled Edition 2022-07-10)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, tk2hc03,      wof,      qsound,         wof,      cps_state,   init_wof,      ROT0,   "hack",      "Tenchi wo Kurau II (Unparalleled Edition 2022-07-27)", MACHINE_SUPPORTS_SAVE )
GAME( 2022, varthhc01,    varth,    cps1_12MHz,     varth,    cps_state,   init_cps1,     ROT270, "hack",      "Varth: Operation Thunderstorm (Thunderbird's Wings)", MACHINE_SUPPORTS_SAVE )
