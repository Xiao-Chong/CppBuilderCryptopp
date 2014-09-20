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
		//memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
   // memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    //
    // String and Sink setup
    //
		std::string plaintext = "Sam is Geek, andow is the time for all good men to come to the aide...";
		std::string ciphertext;
		std::string decryptedtext;

		this->Memo1->Lines->Add(plaintext.c_str());
    //
    // Dump Plain Text
    //
//    std::cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
//		std::cout << plaintext;
//		std::cout << std::endl << std::endl;

    //
    // Create Cipher Text
    //
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

		this->Memo1->Lines->Add(ciphertext.c_str());

		this->Memo1->Lines->Add("");
		this->Memo1->Lines->Add(TEncoding::ASCII->GetString(db2));
		this->Memo1->Lines->Add("");
    //
    // Dump Cipher Text
		//
//    std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;
//
//		for( int i = 0; i < ciphertext.size(); i++ ) {
//
//				std::cout << "0x" << std::hex << (0xFF & static_cast<byte>(ciphertext[i])) << " ";
//		}
//
//		std::cout << std::endl << std::endl;

    //
    // Decrypt
		//

		CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
		CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

		CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
		stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
		stfDecryptor.MessageEnd();

    //
    // Dump Decrypted Text
    //
//    std::cout << "Decrypted Text: " << std::endl;
//		std::cout << decryptedtext;
//		std::cout << std::endl << std::endl;

		this->Memo1->Lines->Add(decryptedtext.c_str());
}
//---------------------------------------------------------------------------
