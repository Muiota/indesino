void GuiControls::drawCircularWave(uint8_t x, uint8_t y, uint8_t colorIndex, int8_t value)
{
	if (++currentRingIndex >= RING_BUFFER_LENGTH)
	{
		currentRingIndex -= RING_BUFFER_LENGTH;
	}	
	ringBuffer[currentRingIndex] = value;    
	int16_t positionX = x + RING_BUFFER_LENGTH;	
	int16_t positionY = y + 32;
	//const uint8_t lastElement = RING_BUFFER_LENGTH - 1;
	for (uint8_t i = 0; i < RING_BUFFER_LENGTH; i++)
	{
		//tft->drawLine(positionX - i, positionY - 31, positionX - i, positionY + 32, ILI9341_BLACK);
		int16_t index = currentRingIndex - i;
		if (index < 0)
		{
			index += RING_BUFFER_LENGTH;
		}
		uint8_t seriesIndex = i < 6 ? i + 1 : RING_BUFFER_LENGTH - i;
		if (seriesIndex > 6)
		{
			seriesIndex = 6;
		}
		uint8_t backgroundIndex = colorIndex;

		if (i % 16 == 8)
		{
			backgroundIndex++;
		}

		if (ringBuffer[index] > 0)
		{
			tft->drawLine(positionX - i, positionY - 1, positionX - i, positionY - ringBuffer[index], list_bright[colorIndex + seriesIndex]);
			tft->drawLine(positionX - i, positionY - 1 - ringBuffer[index], positionX - i, positionY - 31, list_bright[backgroundIndex]);			
			if (index == 0 || ringBuffer[index - 1] <= 0)
			{
				tft->drawLine(positionX - i, positionY + 1, positionX - i, positionY + 31, list_bright[backgroundIndex]);
			}
		}
		else if (ringBuffer[index] < 0)
		{
			tft->drawLine(positionX - i, positionY + 1, positionX - i, positionY - ringBuffer[index], list_bright[colorIndex + seriesIndex]);
			tft->drawLine(positionX - i, positionY + 1 - ringBuffer[index], positionX - i, positionY + 31, list_bright[backgroundIndex]);
			if (index == 0 || ringBuffer[index - 1] >= 0)
			{
				tft->drawLine(positionX - i, positionY - 1, positionX - i, positionY - 31, list_bright[backgroundIndex]);
			}
		}
		else
		{
			if (index ==0 || ringBuffer[index - 1] != 0)
			{
				tft->drawLine(positionX - i, positionY + 1, positionX - i, positionY + 31, list_bright[backgroundIndex]);
				tft->drawLine(positionX - i, positionY - 1, positionX - i, positionY - 31, list_bright[backgroundIndex]);
			}
		}

//		tft->drawLine(positionX - i, positionY+2, positionX - i, positionY+3 , foreColor);

//		tft->drawLine(positionX - i, positionY -2, positionX - i, positionY - 3, foreColor);
	}

	
}
