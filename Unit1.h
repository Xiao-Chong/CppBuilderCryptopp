//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>

#ifdef __BORLANDC__
	#ifndef __clang__
		#pragma comment(lib, "cryptlib_bds.lib")
		#pragma comment(lib, "ws2_32.lib")
	#else
		#ifdef __ANDROID__
			//#pragma comment(lib, "libcryptlib_bds.a") // useless for android,
			// need manually add to project option with additional library
		#else
			#pragma comment(lib, "cryptlib_bds.a")
			#pragma comment(lib, "ws2_32.a")
		#endif
	#endif
#endif

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TMemo *Memo1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
