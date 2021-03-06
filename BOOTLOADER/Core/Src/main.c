/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/*Прошивка, которую поместим на адрес: 0x0800C000
 * Данная прошивка представляет собой обычный светодиодный blink с периодом 250мс
 *
 */

const char data[][BUFFER_SIZE] = {":020000040800F2",
":10C00000008001203DC7000815C7000817C70008B9",
":10C0100019C700081BC700081DC700080000000062",
":10C020000000000000000000000000001FC7000822",
":10C0300021C700080000000023C7000825C700082A",
":10C040008DC700088DC700088DC700088DC7000880",
":10C050008DC700088DC700088DC700088DC7000870",
":10C060008DC700088DC700088DC700088DC7000860",
":10C070008DC700088DC700088DC700088DC7000850",
":10C080008DC700088DC700088DC70008000000009C",
":10C090000000000000000000000000008DC7000844",
":10C0A0008DC700088DC700088DC700088DC7000820",
":10C0B0008DC700088DC700088DC700088DC7000810",
":10C0C0008DC700088DC700088DC700088DC7000800",
":10C0D0008DC700088DC700088DC70008000000004C",
":10C0E0008DC700088DC700088DC70008000000003C",
":10C0F0000000000000000000000000008DC70008E4",
":10C10000000000008DC700088DC700088DC700081B",
":10C11000000000000000000000000000000000001F",
":10C120008DC700088DC700088DC700088DC700089F",
":10C130008DC70008000000000000000000000000A3",
":10C140000000000000000000000000008DC7000893",
":10C150008DC700088DC700088DC700088DC700086F",
":10C160008DC700088DC70008000000000000000017",
":10C1700000000000000000000000000000000000BF",
":10C18000000000008DC70008000000000000000053",
":04C190008DC700084F",
":10C1940010B5054C237833B9044B13B10448AFF3FD",
":10C1A40000800123237010BD0C000020000000005B",
":10C1B40054D1000808B5034B1BB103490348AFF33E",
":10C1C400008008BD000000001000002054D10008C9",
":10C1D40053B94AB9002908BF00281CBF4FF0FF31EA",
":10C1E4004FF0FF3000F06EB9ADF1080C6DE904CEEC",
":10C1F40000F006F8DDF804E0DDE9022304B070473E",
":10C204002DE9F047089D04468C46002B40F08380BE",
":10C214008A42174647D9B2FA82F242B1C2F12000EB",
":10C2240024FA00F09140974040EA010C94404FEA10",
":10C234001748230CBCFBF8F61FFA87FE08FB16C14F",
":10C2440043EA014306FB0EF1994209D9FB1806F1B2",
":10C25400FF3080F01981994240F21681023E3B443E",
":10C264005B1AA4B2B3FBF8F008FB103344EA0344AE",
":10C2740000FB0EFEA64509D93C1900F1FF3380F0FE",
":10C284000581A64540F2028102383C4440EA06405A",
":10C29400A4EB0E0400261DB1D4400023C5E90043DD",
":10C2A4003146BDE8F08702B9FFDEB2FA82F2002A15",
":10C2B40050D1CB1B4FEA174E1FFA87F80126B3FB68",
":10C2C400FEFC210C0EFB1C3341EA034108FB0CF37A",
":10C2D4008B4207D979180CF1FF3002D28B4200F25D",
":10C2E400E9808446C91AA3B2B1FBFEF00EFB10111B",
":10C2F40043EA014408FB00F8A04507D93C1900F1C2",
":10C30400FF3302D2A04500F2D9801846A4EB0804FA",
":10C3140040EA0C40BFE78B4209D9002D00F0B18000",
":10C324000026C5E9000130463146BDE8F087B3FA7E",
":10C3340083F6002E4AD18B4202D3824200F2B880A7",
":10C34400841A61EB030101208C46002DA8D0C5E9B5",
":10C35400004CA5E7C2F1200320FA03F6974001FA46",
":10C3640002F04FEA174ED9403043030CB1FBFEF6FE",
":10C374001FFA87F80EFB161143EA014306FB08F186",
":10C38400994204FA02F409D9FB1806F1FF3C80F043",
":10C394008D80994240F28A80023E3B445B1A81B20E",
":10C3A400B3FBFEF00EFB103341EA034100FB08F33C",
":10C3B4008B4207D9791800F1FF3C73D28B4271D9B3",
":10C3C40002383944CB1A40EA064678E7C6F1200C15",
":10C3D40003FA06F422FA0CF31C4320FA0CF701FAD0",
":10C3E40006F34FEA144E21FA0CF11F433B0CB1FB48",
":10C3F400FEF91FFA84F80EFB191143EA014109FB07",
":10C4040008FA8A4502FA06F200FA06F308D9611816",
":10C4140009F1FF3048D28A4546D9A9F102092144DD",
":10C42400A1EB0A01BFB2B1FBFEF00EFB101147EA0B",
":10C43400014700FB08F8B84507D9E71900F1FF31B7",
":10C444002ED2B8452CD90238274440EA0940A7EB3C",
":10C454000807A0FB02894F45C64649461AD317D0A0",
":10C464005DB1B3EB0E0267EB010707FA0CFCF24077",
":10C474004CEA0202F740C5E9002700263146BDE830",
":10C48400F0872E4628460BE70646E9E61846FDE601",
":10C494004345E5D2B8EB020E69EB04010138DFE74E",
":10C4A4000846D2E760468DE78146B9E7664675E7F8",
":10C4B40030464AE7ACF1020C394413E702383C44F5",
":10C4C40024E700BF704700BF10B594B014220021C8",
":10C4D40009A800F035FE1422002103A800F030FE64",
":10C4E4001F4B00220192196C41F0805119641B6C9E",
":10C4F4001C4903F080530193019B02920B6823F4BF",
":10C50400404343F400430B600B6803F4404302933D",
":10C51400029B012110234FF4A870CDE90B13109353",
":10C524000423CDE911030224072308A8CDE90E4210",
":10C534000894139300F0BEFA08B172B6FEE70F2315",
":10C54400CDE903344FF48053CDE9063005902146FC",
":10C5540003A800F089FC08B172B6FEE714B010BD60",
":10C56400003802400070004000B58BB072B6374B03",
":10C57400374A9A6062B600F02DF9FFF7A5FF14223E",
":10C5840000210DEB020000F0DBFD0024314B01948F",
":10C594001A6B314842F004021A631A6B02F0040267",
":10C5A4000192019A02941A6B42F080021A631A6B88",
":10C5B40002F080020292029A03941A6B42F0010282",
":10C5C4001A631A6B02F001020392039A04941A6B21",
":10C5D40042F002021A631B6B03F002030493224627",
":10C5E4002021049B00F058FA4FF400524FF4041336",
":10C5F4001A48079405A9CDE9052300F085F901231C",
":10C604002021CDE90513144805A9CDE9074400F01C",
":10C614007BF91348DFF84CC004614FF4E133C0E9FF",
":10C6240000C30C23C0E90244C0E90534C46100F02E",
":10C6340035FD40B9084C2046202100F032FAC820CC",
":10C6440000F0F4F8F7E772B6FEE700BF00ED00E093",
":10C6540000C0000800380240000002400008024008",
":10C66400280000200044004082B00D4B00210091BE",
":10C674005A6C42F480425A645A6C02F4804200922A",
":10C68400009A01911A6C42F080521A641B6C03F0F8",
":10C6940080530193019B072002B000F0DBB800BF78",
":10C6A4000038024010B5044688B01422002103A8C3",
":10C6B40000F046FD2268144B9A4222D103F5FA3366",
":10C6C40000220192196C114841F400311964196C6B",
":10C6D40001F40031019101990292196B41F00101B9",
":10C6E40019631B6B03F0010302930C21029B0223C9",
":10C6F400CDE90313072303A9CDE90522079300F02D",
":10C7040003F908B010BD00BF00440040000002401F",
":10C71400FEE7FEE7FEE7FEE7FEE770477047704777",
":10C7240000F072B8034AD2F8883043F47003C2F8B8",
":10C734008830704700ED00E0DFF834D00D480E4932",
":10C744000E4A002302E0D458C4500433C4188C4267",
":10C75400F9D30B4A0B4C002301E013600432A242CC",
":10C76400FBD3FFF7DFFF00F0C7FCFFF7FDFE7047C8",
":10C7740000800120000000200C00002094D100085B",
":10C784000C00002070000020FEE7000038B50E4ABF",
":10C794000E4B054618784FF47A73B3FBF0F3106828",
":10C7A400B0FBF3F000F09AF8044658B90F2D09D8FD",
":10C7B400024629464FF0FF3000F05EF8044B204655",
":10C7C4001D6038BD0120FCE70000002004000020AB",
":10C7D4000800002008B50B4B1A6842F400721A6076",
":10C7E4001A6842F480621A601A6842F480721A600D",
":10C7F400032000F02FF80020FFF7C8FFFFF734FFF5",
":10C80400002008BD003C0240034A044B11681B7819",
":10C814000B441360704700BF6C000020040000202C",
":10C82400014B1868704700BF6C00002038B50446FF",
":10C83400FFF7F6FF631C1CBF054B1B78054618BFAA",
":10C84400E418FFF7EDFF431BA342FAD338BD00BF42",
":10C85400040000200749CA6822F4E06203021204BB",
":10C8640003F4E063120C134343F0BF6343F4003357",
":10C87400CB60704700ED00E0164B30B5DC68C4F3C4",
":10C884000224C4F10705231D042D28BF0425062B0B",
":10C894004FF0FF338CBF033C002403FA05F521EA73",
":10C8A4000501A34022EA0302A140002841EA020351",
":10C8B400ACBF00F16040084A4FEA0313B8BF00F070",
":10C8C4000F00DBB2AABF00F56140135480F80033B7",
":10C8D40030BD00BF00ED00E014ED00E00138B0F120",
":10C8E400807F0AD2064B074A5860F02182F8231051",
":10C8F4000020072298601A6070470120704700BF2B",
":10C9040010E000E000ED00E02DE9F74FDFF884913E",
":10C914005E4A00230D6801249C4004EA050CAC43E4",
":10C9240040F0A5804D6805F003044FEA4308032650",
":10C93400671E06FA08F6012F6FEA060634D88768E0",
":10C9440007EA060ECF6807FA08F747EA0E0787607A",
":10C95400476827EA0C0EC5F300179F4047EA0E0705",
":10C964004760C76807EA060E8F6807FA08F747EAC0",
":10C974000E07022CC76019D14FEAD30A00EB8A0ACA",
":10C9840003F0070BDAF820704FEA8B0B4FF00F0E11",
":10C994000EFA0BFE27EA0E0E0F6907FA0BF747EAA9",
":10C9A4000E07CAF8207001E0032CDAD1076804FAF4",
":10C9B40008F43E40264315F4403F066057D04FF03C",
":10C9C400000ACDF804A0D9F84460314C46F48046FE",
":10C9D400C9F84460D9F8446006F480460196019E83",
":10C9E40023F0030606F1804606F59C3603F0030E99",
":10C9F400D6F808804FEA8E0E0F2707FA0EF7A042EA",
":10CA040028EA07073AD004F58064A04238D004F538",
":10CA14008064A04236D004F58064A04234D004F58A",
":10CA24008064A0420CBF0424072404FA0EF43C439F",
":10CA3400B46014686FEA0C06EF0354BF34404CEA48",
":10CA4400040414605468AF0354BF34404CEA040433",
":10CA540054609468EF0254BF34404CEA0404946078",
":10CA6400D468AD0254BF34404CEA0404D4600133AA",
":10CA7400102B7FF44FAF03B0BDE8F08F5446D4E7DA",
":10CA84000124D2E70224D0E70324CEE7003C01408E",
":10CA940000000240003802400AB181617047090475",
":10CAA400FBE7436901EA030221EA030141EA024187",
":10CAB400816170472DE9F341044640B30368DD0703",
":10CAC40010D4236898075ED423681A0700F1A08065",
":10CAD40023685B0700F1BE80A069002840F01F8135",
":10CAE40000202BE0A64B9A6802F00C02042A07D01F",
":10CAF4009A6802F00C02082A0BD15A68510208D530",
":10CB04009F4B1B689A03DCD56368002BD9D10120A5",
":10CB140014E06268B2F5803F13D11A6842F480329F",
":10CB24001A60FFF77DFE964E054633689B03C8D412",
":10CB3400FFF776FE401B6428F7D9032002B0BDE856",
":10CB4400F0818F4DB2F5A02F2B6807D143F48023D9",
":10CB54002B602B6843F480332B60E2E723F48033AB",
":10CB64002B602B6823F480232B60002AD9D1FFF794",
":10CB740057FE06462B689F03A3D5FFF751FE801B83",
":10CB84006428F7D9D9E77E4B9A6812F00C0F07D0C6",
":10CB94009A6802F00C02082A11D15B685E020ED476",
":10CBA400774B1A68950702D5E268012AAFD11A6853",
":10CBB400216922F0F80242EAC1021A6084E7E268BD",
":10CBC400704BB2B101221A60FFF72AFE6C4D064683",
":10CBD4002B68980707D52B68226923F0F80343EAEA",
":10CBE400C2032B6070E7FFF71BFE801B0228EFD9FE",
":10CBF400A3E71A60FFF714FE614E054633689907F0",
":10CC04007FF562AFFFF70CFE401B0228F6D994E7CC",
":10CC140062695D4B7AB101221A60FFF701FE584E3A",
":10CC24000546736F9F073FF553AFFFF7F9FD401BB0",
":10CC34000228F6D981E71A60FFF7F2FD504E054647",
":10CC4400736F98077FF544AFFFF7EAFD401B022896",
":10CC5400F6D972E74A4B1A6C12F0805228D101922D",
":10CC64001A6C42F080521A641B6C03F080530193D7",
":10CC7400019B0127454D2B68D9051BD5A368404D61",
":10CC8400012B27D12B6F43F001032B67FFF7C8FD5E",
":10CC94003B4E054641F28838336F9B0739D5002F48",
":10CCA4003FF41AAF364A136C23F08053136413E72E",
":10CCB4000027DFE72B6843F480732B60FFF7B0FD98",
":10CCC40006462B68DA05D9D4FFF7AAFD801B022893",
":10CCD400F7D932E7052B04D12B6F43F004032B67FC",
":10CCE400D0E72A6F22F001022A672A6F22F0040299",
":10CCF4002A67002BCAD1FFF793FD41F28838064614",
":10CD04002B6F9807CBD5FFF78BFD801B4045F7D9D8",
":10CD140013E7FFF785FD401B4045BDD90DE7184DCE",
":10CD2400AB6803F00C03082B47D0194E00230228EC",
":10CD3400336035D1FFF774FD07462B68990129D478",
":10CD4400D4E907321343626A43EA8213E26A43EA8C",
":10CD54000263A26A5208013A43EA02436B60012368",
":10CD64003360FFF75DFD064D04462B689A013FF5DD",
":10CD7400B7AEFFF755FD001B0228F6D9DDE600BF6C",
":10CD84000038024000004742800E474200700040D5",
":10CD940060004742FFF744FDC01B0228CDD9CCE612",
":10CDA400FFF73EFD04462B689B017FF599AEFFF724",
":10CDB40037FD001B0228F6D9BFE601283FF4BEAEBA",
":10CDC4006B68E26903F4800191427FF4A0AE216AAA",
":10CDD40003F03F028A427FF49AAE616A47F6C0725A",
":10CDE4001A40B2EB811F7FF492AEA26A520803F498",
":10CDF4004031013AB1EB024F7FF489AEE26A03F0AD",
":10CE04007063B3EB026F3FF46BAE80E6134908B571",
":10CE14008B6803F00C03042B1CD0082B1CD14A682C",
":10CE24004B68496813F4800314BF0D480D48C1F3DF",
":10CE3400881118BF002302F03F02A1FB0001FFF795",
":10CE4400C7F9064B5B68C3F3014301335B00B0FBD6",
":10CE5400F3F008BD0248FCE70248FAE70038024054",
":10CE640000127A000024F4002DE9F0410D46044636",
":10CE740010B90120BDE8F081444B1A6802F00702A2",
":10CE84008A4228D3226897072DD4D00741D43F4B38",
":10CE94001A6802F00702AA4266D8226851076CD4C5",
":10CEA400130707D53A4A2169936823F4604343EA98",
":10CEB400C1039360FFF7AAFF354B364A9B68C3F35F",
":10CEC4000313D35CD840344B1860344B1868FFF715",
":10CED4005DFC0020CEE7CAB21A701B6803F007039A",
":10CEE4008B42C6D1CEE72A4B12F0040F1EBF9968BD",
":10CEF40041F4E0519960160742BF996841F46041DA",
":10CF040099602349A0688B6823F0F00303438B6086",
":10CF1400BBE762681E4B012A1CD11B6813F4003F57",
":10CF2400A7D01B4EB36823F003031343B360FFF78A",
":10CF340077FC41F288380746B368626803F00C0353",
":10CF4400B3EB820FA3D0FFF76BFCC01B4045F3D9B2",
":10CF540003208FE7911E01291B6802D813F0007F7C",
":10CF6400DEE713F0020FDBE7EAB21A701B6803F086",
":10CF74000703AB427FF47DAF8FE70549E0688B6818",
":10CF840023F4E05303438B608AE700BF003C024074",
":10CF9400003802406CD10008000000200800002086",
":10CFA400044B054A9B68C3F38223D35C034A10688D",
":10CFB400D8407047003802407CD1000800000020AF",
":10CFC400044B054A9B68C3F34233D35C034A10689D",
":10CFD400D8407047003802407CD10008000000208F",
":10CFE4000268C16838B5136923F440530B431361D5",
":10CFF400054683680069D168034368690343E869A7",
":10D0040021F4164121F00C0103430B43D36053690F",
":10D01400A96923F440730B4353611F4B9A4203D015",
":10D0240003F580639A4224D1FFF7CAFFEA69192302",
":10D03400B2F5004FA0FB0301D5E900431CD11A4609",
":10D0440092184FF000035B41FFF7C2F86421B0FB74",
":10D05400F1F501FB1503DB003233B3FBF1F303F00D",
":10D0640007025B0002EB051203F4F8731344A36098",
":10D0740038BDFFF795FFD9E79A009B0FFFF7A8F893",
":10D084006422B0FBF2F102FB11031B013233B3FB48",
":10D09400F2F303EB0113EAE70010014010B5044674",
":10D0A40040B390F83D3003F0FF021BB980F83C20F8",
":10D0B400FFF7F8FA2268242384F83D30D36823F478",
":10D0C4000053D3602046FFF78BFF23681A6922F4CC",
":10D0D40090421A615A6922F02A025A61DA6842F4CB",
":10D0E4000052DA6000202023206484F83D3084F864",
":10D0F4003E3010BD0120FCE770B50D4D0D4C641B96",
":10D10400A4100026A64209D10B4D0C4C00F020F8C7",
":10D11400641BA4100026A64205D170BD55F8043B3B",
":10D1240098470136EEE755F8043B98470136F2E795",
":10D134008CD100088CD100088CD1000890D1000853",
":10D1440002440346934200D1704703F8011BF9E7F8",
":10D15400F8B500BFF8BC08BC9E467047F8B500BFE0",
":08D16400F8BC08BC9E467047B0",
":10D16C00000000000000000001020304060708098B",
":08D17C000000000001020304A1",
":08D1840080F0FF7F01000000B4",
":04D18C00B9C100081D",
":04D1900095C100083D",
":0CD194000024F400010000001000000066",
":040000050800C73DEB",
":00000001FF"};

volatile uint32_t address = 0x00000000;
uint8_t dataBuffer[BUFFER_SIZE] = {0};


volatile uint8_t menuItem = 0;
volatile _Bool interruptFlag = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */




  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (interruptFlag == 1 && menuItem == 1) {
		  interruptFlag = 0;
		  for(uint8_t i = 0;i<6;i++) {
			  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			  HAL_Delay(500);
		  }
		  programFlash(FLASH_SECTOR_3, data, (sizeof data / sizeof *data));
	  }
	  if (interruptFlag == 1 && menuItem == 2) {
	  		  interruptFlag = 0;
	  		  for(uint8_t i = 0;i<10;i++) {
	  			  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  			  HAL_Delay(300);
	  		  }
	  		  HAL_Delay(5000);
	  		startApplicationByAddress(APP_START_ADDRESS);
	  	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
/*функция преобразует ascii в hex*/


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_13) {
		interruptFlag = 1;
		menuItem++;
		if (menuItem == 3) {
			menuItem = 0;
		}

	} else __NOP();
	}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
	  for(uint8_t i = 0;i<6;i++) {
		  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		  HAL_Delay(250);
	  }
	  HAL_Delay(500);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
