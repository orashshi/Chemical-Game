void get_PutCardList_2_limit(GameSituation &clsGameSituation, HandCardData &clsHandCardData)
{
	clsHandCardData.ClearPutCardList();
 
 
	/*王炸——当前策略只处理王炸作为倒数第二手的优先出牌逻辑，后续版本会在此基础上优化*/
	if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
	{
 
		clsHandCardData.value_aHandCardList[17] --;
		clsHandCardData.value_aHandCardList[16] --;
		clsHandCardData.nHandCardCount -= 2;
		HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
		clsHandCardData.value_aHandCardList[16] ++;
		clsHandCardData.value_aHandCardList[17] ++;
		clsHandCardData.nHandCardCount += 2;
		if (tmpHandCardValue.NeedRound == 1)
		{
			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);
			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);
			return;
		}
	}
 
 
	//错误牌型  不出
	if (clsGameSituation.uctNowCardGroup.cgType == cgERROR)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgERROR, 0, 0);
		return;
	}
	//不出牌型，在被动出牌策略里也是错误数据 不出
	else if (clsGameSituation.uctNowCardGroup.cgType == cgZERO)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//单牌类型
	else if (clsGameSituation.uctNowCardGroup.cgType == cgSINGLE)
	{
	    //管不上
	    clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
		
	}
	//对牌类型
	else if (clsGameSituation.uctNowCardGroup.cgType == cgDOUBLE)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//三牌类型
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE)
	{
 
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//单连类型
	else if (clsGameSituation.uctNowCardGroup.cgType == cgSINGLE_LINE)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//对连类型
	else if (clsGameSituation.uctNowCardGroup.cgType == cgDOUBLE_LINE)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
 
	}
	//三连类型
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_LINE)
	{	
	//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//三带一单
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_ONE)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//三带一对
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_TWO)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//三带一单连
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_ONE_LINE)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//三带一对连
	else if (clsGameSituation.uctNowCardGroup.cgType == cgTHREE_TAKE_TWO_LINE)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//四带两单
	else if (clsGameSituation.uctNowCardGroup.cgType == cgFOUR_TAKE_ONE)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//四带两对
	else if (clsGameSituation.uctNowCardGroup.cgType == cgFOUR_TAKE_TWO)
	{
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//炸弹类型 
	else if (clsGameSituation.uctNowCardGroup.cgType == cgBOMB_CARD)
	{	
		//管不上
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;	
	}
	//王炸类型 人都王炸了你还出个毛
	else if (clsGameSituation.uctNowCardGroup.cgType == cgKING_CARD)
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
		return;
	}
	//异常处理 不出
	else
	{
		clsHandCardData.uctPutCardType = get_GroupData(cgZERO, 0, 0);
	}
	return;
}