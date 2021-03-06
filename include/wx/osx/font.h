/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/font.h
// Purpose:     wxFont class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_FONT_H_
#define _WX_FONT_H_

// ----------------------------------------------------------------------------
// wxFont
// ----------------------------------------------------------------------------

// font styles
enum wxOSXSystemFont
{
    wxOSX_SYSTEM_FONT_NONE = 0,
    wxOSX_SYSTEM_FONT_NORMAL,
    wxOSX_SYSTEM_FONT_BOLD,
    wxOSX_SYSTEM_FONT_SMALL,
    wxOSX_SYSTEM_FONT_SMALL_BOLD,
    wxOSX_SYSTEM_FONT_MINI,
    wxOSX_SYSTEM_FONT_MINI_BOLD,
    wxOSX_SYSTEM_FONT_LABELS,
    wxOSX_SYSTEM_FONT_VIEWS
};


class WXDLLIMPEXP_CORE wxFont : public wxFontBase
{
public:
    // ctors and such
    wxFont() { }

    wxFont(const wxFontInfo& info)
    {
        Create(info.GetPointSize(),
               info.GetFamily(),
               info.GetStyle(),
               info.GetWeight(),
               info.IsUnderlined(),
               info.GetFaceName(),
               info.GetEncoding());

        if ( info.IsUsingSizeInPixels() )
            SetPixelSize(info.GetPixelSize());
    }

    wxFont( wxOSXSystemFont systemFont );

#if wxOSX_USE_COCOA
    wxFont(WX_NSFont nsfont);
#endif

    wxFont(int size,
           wxFontFamily family,
           wxFontStyle style,
           wxFontWeight weight,
           bool underlined = false,
           const wxString& face = wxEmptyString,
           wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
    {
        Create(size, family, style, weight, underlined, face, encoding);
    }

    wxFont(const wxSize& pixelSize,
           wxFontFamily family,
           wxFontStyle style,
           wxFontWeight weight,
           bool underlined = false,
           const wxString& face = wxEmptyString,
           wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
    {
        Create(10, family, style, weight, underlined, face, encoding);
        SetPixelSize(pixelSize);
    }

    bool Create(int size,
                wxFontFamily family,
                wxFontStyle style,
                wxFontWeight weight,
                bool underlined = false,
                const wxString& face = wxEmptyString,
                wxFontEncoding encoding = wxFONTENCODING_DEFAULT);

    wxFont(const wxNativeFontInfo& info)
    {
        (void)Create(info);
    }

    wxFont(const wxString& fontDesc);

    bool Create(const wxNativeFontInfo& info);

    virtual ~wxFont();

    // implement base class pure virtuals
    virtual int GetPointSize() const wxOVERRIDE;
    virtual wxSize GetPixelSize() const wxOVERRIDE;
    virtual wxFontStyle GetStyle() const wxOVERRIDE;
    virtual wxFontWeight GetWeight() const wxOVERRIDE;
    virtual bool GetUnderlined() const wxOVERRIDE;
    virtual bool GetStrikethrough() const wxOVERRIDE;
    virtual wxString GetFaceName() const wxOVERRIDE;
    virtual wxFontEncoding GetEncoding() const wxOVERRIDE;
    virtual const wxNativeFontInfo *GetNativeFontInfo() const wxOVERRIDE;

    virtual bool IsFixedWidth() const wxOVERRIDE;

    virtual void SetPointSize(int pointSize) wxOVERRIDE;
    virtual void SetFamily(wxFontFamily family) wxOVERRIDE;
    virtual void SetStyle(wxFontStyle style) wxOVERRIDE;
    virtual void SetWeight(wxFontWeight weight) wxOVERRIDE;
    virtual bool SetFaceName(const wxString& faceName) wxOVERRIDE;
    virtual void SetUnderlined(bool underlined) wxOVERRIDE;
    virtual void SetStrikethrough(bool strikethrough) wxOVERRIDE;
    virtual void SetEncoding(wxFontEncoding encoding) wxOVERRIDE;

    wxDECLARE_COMMON_FONT_METHODS();

    wxDEPRECATED_MSG("use wxFONT{FAMILY,STYLE,WEIGHT}_XXX constants")
    wxFont(int size,
           int family,
           int style,
           int weight,
           bool underlined = false,
           const wxString& face = wxEmptyString,
           wxFontEncoding encoding = wxFONTENCODING_DEFAULT);


    // implementation only from now on
    // -------------------------------

    virtual bool RealizeResource();

    // Mac-specific, risks to change, don't use in portable code

#if wxOSX_USE_CARBON && wxOSX_USE_ATSU_TEXT
    wxUint16 MacGetThemeFontID() const ;

    // 'old' Quickdraw accessors
    short MacGetFontNum() const;
    wxByte  MacGetFontStyle() const;
#endif

#if wxOSX_USE_COCOA_OR_CARBON
    CGFontRef OSXGetCGFont() const;
#endif

    CTFontRef OSXGetCTFont() const;

#if wxOSX_USE_ATSU_TEXT
    // Returns an ATSUStyle not ATSUStyle*
    void* MacGetATSUStyle() const ;
    void* OSXGetATSUStyle() const { return MacGetATSUStyle() ; }

    wxDEPRECATED( wxUint32 MacGetATSUFontID() const );
    wxDEPRECATED( wxUint32 MacGetATSUAdditionalQDStyles() const );
#endif

#if wxOSX_USE_COCOA
    WX_NSFont OSXGetNSFont() const;
    static WX_NSFont OSXCreateNSFont(wxOSXSystemFont font, wxNativeFontInfo* info);
    static WX_NSFont OSXCreateNSFont(const wxNativeFontInfo* info);
    static void SetNativeInfoFromNSFont(WX_NSFont nsfont, wxNativeFontInfo* info);
#endif

#if wxOSX_USE_IPHONE
    WX_UIFont OSXGetUIFont() const;
    static WX_UIFont OSXCreateUIFont(wxOSXSystemFont font, wxNativeFontInfo* info);
    static WX_UIFont OSXCreateUIFont(const wxNativeFontInfo* info);
#endif

protected:
    virtual void DoSetNativeFontInfo(const wxNativeFontInfo& info) wxOVERRIDE;
    virtual wxFontFamily DoGetFamily() const wxOVERRIDE;

    virtual wxGDIRefData *CreateGDIRefData() const wxOVERRIDE;
    virtual wxGDIRefData *CloneGDIRefData(const wxGDIRefData *data) const wxOVERRIDE;

private:

    wxDECLARE_DYNAMIC_CLASS(wxFont);
};

#endif // _WX_FONT_H_
