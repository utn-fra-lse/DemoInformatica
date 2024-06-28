#include <L2.h>
//------------------------------------------------------------------------
// Borra sector de flash
// Parametro: sector de inicio, sector de fin, frecuencia de clock mcu
// Devuelve: nada
//------------------------------------------------------------------------
uint32_t Erase_Sector(uint8_t sector_inicio, uint8_t sector_fin, uint32_t freq_bus){
	uint32_t resp;
	resp = IAP_PrepareSectorForWrite(sector_inicio, sector_fin);
	if( resp != kStatus_IAP_Success){
	  	return resp;
	}
	resp = IAP_EraseSector(sector_inicio,sector_fin,freq_bus);
	if(resp != kStatus_IAP_Success){
	  	return resp;
	}
	return resp;
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Borra sector de flash
// Parametro: sector de inicio, sector de fin, frecuencia de clock mcu
// Devuelve: nada
//------------------------------------------------------------------------
uint32_t Erase_Page(uint8_t page_inicio, uint8_t page_fin, uint32_t freq_bus){
	uint32_t resp, sector_i, sector_f;
	sector_i = page_inicio / PAGE_X_SECTOR;
	sector_f = page_fin / PAGE_X_SECTOR;

	resp = IAP_PrepareSectorForWrite(sector_i, sector_f);
	if( resp != kStatus_IAP_Success){
	  	return resp;
	}
	resp = IAP_ErasePage(page_inicio,page_fin,freq_bus);
	if(resp != kStatus_IAP_Success){
	  	return resp;
	}
	return resp;
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Escribe pagina de flash
// Parametro: direccion, buffer, cantidad de bytes, frecuencia de clock mcu
// Devuelve: nada
//------------------------------------------------------------------------
uint32_t Write_Page(uint32_t address, uint8_t *dat, uint8_t cant, uint32_t freq_bus){
	uint32_t resp, sector;
	sector = address / (PAGE_X_SECTOR * BYTES_X_PAGE);

	resp = IAP_PrepareSectorForWrite(sector, sector);
	if( resp != kStatus_IAP_Success){
	  	return resp;
	}
	resp = IAP_CopyRamToFlash(address, dat, cant,freq_bus);
	if(resp != kStatus_IAP_Success){
	  	return resp;
	}
	return resp;
}
//------------------------------------------------------------------------
