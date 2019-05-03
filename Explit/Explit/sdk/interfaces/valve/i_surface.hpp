#pragma once
#include "../../sdk.hpp"

class color;
namespace vgui
{
	typedef unsigned long hfont;
	typedef unsigned int vpanel;
};

enum fontfeature
{
	font_feature_antialiased_fonts = 1,
	font_feature_dropshadow_fonts = 2,
	font_feature_outline_fonts = 6,
};

enum fontdrawtype
{
	font_draw_default = 0,
	font_draw_nonadditive,
	font_draw_additive,
	font_draw_type_count = 2,
};

enum fontflags
{
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

struct intrect
{
	int x0;
	int y0;
	int x1;
	int y1;
};

struct vertex_t
{
	vertex_t() {}
	vertex_t(const vector2d &pos, const vector2d &coord = vector2d(0, 0))
	{
		m_position = pos;
		m_texcoord = coord;
	}
	void init(const vector2d &pos, const vector2d &coord = vector2d(0, 0))
	{
		m_position = pos;
		m_texcoord = coord;
	}

	vector2d m_position;
	vector2d m_texcoord;
};

//-----------------------------------------------------------------------------
// purpose: wraps contextless windows system functions
//-----------------------------------------------------------------------------
class i_surface : public i_app_system
{
public:
	virtual void          runframe() = 0;
	virtual vgui::vpanel  getembeddedpanel() = 0;
	virtual void          setembeddedpanel(vgui::vpanel ppanel) = 0;
	virtual void          pushmakecurrent(vgui::vpanel panel, bool useinsets) = 0;
	virtual void          popmakecurrent(vgui::vpanel panel) = 0;
	virtual void          drawsetcolor(int r, int g, int b, int a) = 0;
	virtual void          drawsetcolor(color col) = 0;
	virtual void          drawfilledrect(int x0, int y0, int x1, int y1) = 0;
	virtual void          drawfilledrectarray(intrect *prects, int numrects) = 0;
	virtual void          drawoutlinedrect(int x0, int y0, int x1, int y1) = 0;
	virtual void          drawline(int x0, int y0, int x1, int y1) = 0;
	virtual void          drawpolyline(int *px, int *py, int numpoints) = 0;
	virtual void          drawsetapparentdepth(float f) = 0;
	virtual void          drawclearapparentdepth(void) = 0;
	virtual void          drawsettextfont(vgui::hfont font) = 0;
	virtual void          drawsettextcolor(int r, int g, int b, int a) = 0;
	virtual void          drawsettextcolor(color col) = 0;
	virtual void          drawsettextpos(int x, int y) = 0;
	virtual void          drawgettextpos(int& x, int& y) = 0;
	virtual void          drawprinttext(const wchar_t *text, int textlen, fontdrawtype drawtype = fontdrawtype::font_draw_default) = 0;
	virtual void          drawunicodechar(wchar_t wch, fontdrawtype drawtype = fontdrawtype::font_draw_default) = 0;
	virtual void          drawflushtext() = 0;
	virtual void*         createhtmlwindow(void *events, vgui::vpanel context) = 0;
	virtual void          painthtmlwindow(void *htmlwin) = 0;
	virtual void          deletehtmlwindow(void *htmlwin) = 0;
	virtual int           drawgettextureid(char const *filename) = 0;
	virtual bool          drawgettexturefile(int id, char *filename, int maxlen) = 0;
	virtual void          drawsettexturefile(int id, const char *filename, int hardwarefilter, bool forcereload) = 0;
	virtual void          drawsettexturergba(int id, const unsigned char *rgba, int wide, int tall) = 0;
	virtual void          drawsettexture(int id) = 0;
	virtual void          deletetexturebyid(int id) = 0;
	virtual void          drawgettexturesize(int id, int &wide, int &tall) = 0;
	virtual void          drawtexturedrect(int x0, int y0, int x1, int y1) = 0;
	virtual bool          istextureidvalid(int id) = 0;
	virtual int           createnewtextureid(bool procedural = false) = 0;
	virtual void          getscreensize(int &wide, int &tall) = 0;
	virtual void          setastopmost(vgui::vpanel panel, bool state) = 0;
	virtual void          bringtofront(vgui::vpanel panel) = 0;
	virtual void          setforegroundwindow(vgui::vpanel panel) = 0;
	virtual void          setpanelvisible(vgui::vpanel panel, bool state) = 0;
	virtual void          setminimized(vgui::vpanel panel, bool state) = 0;
	virtual bool          isminimized(vgui::vpanel panel) = 0;
	virtual void          flashwindow(vgui::vpanel panel, bool state) = 0;
	virtual void          settitle(vgui::vpanel panel, const wchar_t *title) = 0;
	virtual void          setastoolbar(vgui::vpanel panel, bool state) = 0;
	virtual void          createpopup(vgui::vpanel panel, bool minimised, bool showtaskbaricon = true, bool disabled = false, bool mouseinput = true, bool kbinput = true) = 0;
	virtual void          swapbuffers(vgui::vpanel panel) = 0;
	virtual void          invalidate(vgui::vpanel panel) = 0;
	virtual void          setcursor(unsigned long cursor) = 0;
	virtual bool          iscursorvisible() = 0;
	virtual void          applychanges() = 0;
	virtual bool          iswithin(int x, int y) = 0;
	virtual bool          hasfocus() = 0;
	virtual bool          supportsfeature(int /*surfacefeature_t*/ feature) = 0;
	virtual void          restrictpainttosinglepanel(vgui::vpanel panel, bool bforceallownonmodalsurface = false) = 0;
	virtual void          setmodalpanel(vgui::vpanel) = 0;
	virtual vgui::vpanel  getmodalpanel() = 0;
	virtual void          unlockcursor() = 0;
	virtual void          lockcursor() = 0;
	virtual void          settranslateextendedkeys(bool state) = 0;
	virtual vgui::vpanel  gettopmostpopup() = 0;
	virtual void          settoplevelfocus(vgui::vpanel panel) = 0;
	virtual vgui::hfont   createfont_() = 0;
	virtual bool          setfontglyphset(vgui::hfont font, const char *windowsfontname, int tall, int weight, int blur, int scanlines, int flags, int nrangemin = 0, int nrangemax = 0) = 0;
	virtual bool          addcustomfontfile(const char *fontfilename) = 0;
	virtual int           getfonttall(vgui::hfont font) = 0;
	virtual int           getfontascent(vgui::hfont font, wchar_t wch) = 0;
	virtual bool          isfontadditive(vgui::hfont font) = 0;
	virtual void          getcharabcwide(vgui::hfont font, int ch, int &a, int &b, int &c) = 0;
	virtual int           getcharacterwidth(vgui::hfont font, int ch) = 0;
	virtual void          gettextsize(vgui::hfont font, const wchar_t *text, int &wide, int &tall) = 0;
	virtual vgui::vpanel  getnotifypanel() = 0;
	virtual void          setnotifyicon(vgui::vpanel context, unsigned long icon, vgui::vpanel paneltoreceivemessages, const char *text) = 0;
	virtual void          playsound_(const char *filename) = 0;
	virtual int           getpopupcount() = 0;
	virtual vgui::vpanel  getpopup(int index) = 0;
	virtual bool          shouldpaintchildpanel(vgui::vpanel childpanel) = 0;
	virtual bool          recreatecontext(vgui::vpanel panel) = 0;
	virtual void          addpanel(vgui::vpanel panel) = 0;
	virtual void          releasepanel(vgui::vpanel panel) = 0;
	virtual void          movepopuptofront(vgui::vpanel panel) = 0;
	virtual void          movepopuptoback(vgui::vpanel panel) = 0;
	virtual void          solvetraverse(vgui::vpanel panel, bool forceapplyschemesettings = false) = 0;
	virtual void          painttraverse(vgui::vpanel panel) = 0;
	virtual void          enablemousecapture(vgui::vpanel panel, bool state) = 0;
	virtual void          getworkspacebounds(int &x, int &y, int &wide, int &tall) = 0;
	virtual void          getabsolutewindowbounds(int &x, int &y, int &wide, int &tall) = 0;
	virtual void          getproportionalbase(int &width, int &height) = 0;
	virtual void          calculatemousevisible() = 0;
	virtual bool          needkbinput() = 0;
	virtual bool          hascursorposfunctions() = 0;
	virtual void          surfacegetcursorpos(int &x, int &y) = 0;
	virtual void          surfacesetcursorpos(int x, int y) = 0;
	virtual void          drawtexturedline(const vertex_t &a, const vertex_t &b) = 0;
	virtual void          drawoutlinedcircle(int x, int y, int radius, int segments) = 0;
	virtual void          drawtexturedpolyline(const vertex_t *p, int n) = 0;
	virtual void          drawtexturedsubrect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
	virtual void          drawtexturedpolygon(int n, vertex_t *pvertice, bool bclipvertices = true) = 0;
};