//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"

#include "modes.h"
#include "aes.h"
#include "filters.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.NmXhdpiPh.fmx", _PLAT_ANDROID)

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
		//Key and IV setup
    //AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-
    //bit). This key is secretly exchanged between two parties before communication
		//begins. DEFAULT_KEYLENGTH= 16 bytes
		byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];

		std::string plaintext = "Welcome to C++ Builder Delphi Taiwan G+ Community\nhttps://plus.google.com/communities/118037201839816898111";
		std::string ciphertext;
		std::string decryptedtext;

		this->Memo1->Lines->Add(plaintext.c_str());

		CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
		CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

		CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
		stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1 );
		stfEncryptor.MessageEnd();

		DynamicArray<System::Byte> db, db2;
		int dl = ciphertext.length()+1;  // incl. null terminated
		db = BytesOf(ciphertext.c_str(), dl);
		db2.Length = (dl-1)*2+1; // note here
		BinToHex(db,0,db2,0,dl-1);

		//db[db.High] = 0;
		db2[db2.High] = 0;

		//this->Memo1->Lines->Add(ciphertext.c_str());

		this->Memo1->Lines->Add("");
		this->Memo1->Lines->Add(TEncoding::ASCII->GetString(db2));
		this->Memo1->Lines->Add("");

		CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
		CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

		CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
		stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
		stfDecryptor.MessageEnd();

		this->Memo1->Lines->Add(decryptedtext.c_str());
}
//---------------------------------------------------------------------------
