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

//converti un byte ASCII en byte hex  9 => '9' 
Boolean TlsStringConvertByteToAscii(Int8U data_in ,Int8U *data_out)
{
	if( ( data_in >= 0 ) && ( data_in <= 9 ) )
	{
		data_out[0U] = data_in + '0';	
		return TRUE;
	}
	return FALSE;
}

//converti un byte ASCII en bytes hex  9 => '9' hex  250 => '250' 
Boolean TlsStringConvertBytesToAscii(Int8U data_in ,Int8U data_out[4], Int8U *lenght)
{
	Int16U unit = 1000U;
	*lenght = 0;
	Int16U temp_data = data_in;
	
	if( data_in == 0 )
	{
		data_out[*lenght] = 0x30;
		*lenght +=1U;
	}
	else
	{
		for ( Int8U loop_end = 0; loop_end < 4U ; loop_end ++)
		{
			if(( (temp_data / unit) > 0U) || (*lenght > 0)) 
			{
				Int8U val = 0U;
				TlsStringConvertByteToAscii((temp_data / unit),&val);
				temp_data -= ((temp_data / unit) * unit);
				data_out[*lenght] = val;
				*lenght +=1U;
			
			}
			unit /=10;
		}
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

/*
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
*/