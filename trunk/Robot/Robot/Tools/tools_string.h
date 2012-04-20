/*
 * tools_string.h
 *
 * Created: 28/06/2011 15:55:05
 *  Author: berryer
 */ 


#ifndef TOOLS_STRING_H_
#define TOOLS_STRING_H_

#include "Tools/tools_typedefs.h"

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//************************************
// Method:    TlsStringSearchCaract
// FullName:  TlsStringSearchCaract
// Access:    public 
// Returns:   Int8U : index du caractere trouvé
// Qualifier: search un caractere dans une string
// Parameter: Char * string : chaine de caractere
// Parameter: Char caract : caractere a trouvé dans la chaine
// Parameter: Int8U end : limite oe fin de la chaine
//************************************
Int8U TlsStringSearchChar(Char* string, Char caract, Int8U end) ;


//************************************
// Method:    TlsStringConvertAsciiToByte
// FullName:  TlsStringConvertAsciiToByte
// Access:    public 
// Returns:   Boolean 
// Qualifier: converti un byte ASCII en byte hex  '0' => 0x00
// Parameter: Char i_caract : caractere a convertir
// Parameter: Char *o_caract : caractere converti
//************************************
Boolean TlsStringConvertAsciiToByte( Char i_caract, Char *o_caract ) ;

//************************************
// Method:    TlsStringConvertByteToAscii
// FullName:  TlsStringConvertByteToAscii
// Access:    public 
// Returns:   Boolean 
// Qualifier: converti un byte ASCII en byte hex  9 => '9' 250 => '250'
// Parameter: Char i_caract : caractere a convertir
// Parameter: Char *o_caract : caractere converti
//************************************
void TlsStringConvertByteToAscii(Int16U data_in ,Int16U *data_out) ;

#endif /* TOOLS_STRING_H_ */