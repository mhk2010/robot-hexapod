/*
 * tools_string.c
 *
 * Created: 28/06/2011 15:55:05
 *  Author: berryer
 */ 


#include "tools_string.h"


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
//search un caractere dans une string
Int8U TlsStringSearchChar(Char* string, Char caract, Int8U end)
{
	Int8U index_caract = 0U;
	for ( Int8U loop_end = 0; loop_end < end ; loop_end ++)
	{
		if( string[ loop_end ] == caract )
		{
			index_caract = loop_end;
			break;		
		}
	}	
	return index_caract;
}

//converti un byte ASCII en byte hex  9 => '9' 250 => '250'
void TlsStringConvertByteToAscii(Int16U data_in ,Int16U *data_out)
{
	Int16U temp_data = data_in;
	if( (temp_data / 1000U) > 0U)
	{
		Int16U millier = temp_data / 1000U;
		*data_out = (Int16U)( millier << 12U);
		temp_data -= millier * 1000U;
	}
  
	if( (temp_data / 100U) > 0U)
	{
		Int16U centaine = temp_data / 100U;
		*data_out |= (Int16U)( centaine << 8U);
		temp_data -= centaine * 100U;
	}
  
	if((temp_data / 10U) > 0U)
	{
		Int16U dizaine = (Int8U)( temp_data / 10U );
		*data_out |= (Int16U)( dizaine << 4U);
		temp_data -= dizaine * 10U;
	}
  
	if(temp_data > 0U)
	{
		Int16U unite = temp_data;
		*data_out |= (Int16U) unite;
		temp_data -= unite;
	}
}

//converti un byte ASCII en byte hex  
Boolean TlsStringConvertAsciiToByte( Char i_caract, Char *o_caract )
{
  Boolean o_success = TRUE;
  
  //de '0' a '9'
  if(
     ( i_caract >= '0' ) &&
     ( i_caract <= '9' )
    )
  {
    *o_caract = i_caract - '0';
  }
  
  //de 'a' a 'f'
  else if(
           ( i_caract >= 'a' ) &&
           ( i_caract <= 'f' )
          )
  {
    *o_caract = ( i_caract - 'a' ) + 0x10U;
  }
  //de 'A' a 'B'
  else if(
           ( i_caract >= 'A' ) &&
           ( i_caract <= 'F' )
          )
  {
    *o_caract = ( i_caract - 'A' ) + 0x10U;
  }
  else
  {
    o_success = FALSE;
  }
  
  return o_success;
}