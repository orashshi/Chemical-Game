class HandCardData
{
 
 
public:
	//构造函数
	HandCardData::HandCardData()
	{
	}
	//析构函数
	virtual HandCardData::~HandCardData()
	{

	}
 
public:
	  //手牌序列——无花色，值域3~17
    vector <int> value_nHandCardList;
 
	  //手牌序列——状态记录，便于一些计算，值域为该index牌对应的数量0~4
	int value_aHandCardList[18] = { 0 };
 
	  //手牌序列——有花色，按照从大到小的排列  56，52：大王小王……4~0：红3黑3方3花3
	vector <int> color_nHandCardList;
	  //手牌个数
	int nHandCardCount = 17 ;
	  //玩家角色地位       0：地主    1：农民——地主下家   2：农民——地主上家
	int nGameRole = -1;
	  //玩家座位ID 
	int nOwnIndex = -1;
	//玩家要打出去的牌类型
	CardGroupData uctPutCardType;
	//要打出去的牌——无花色
	vector <int> value_nPutCardList;
	//要打出去的牌——有花色
	vector <int> color_nPutCardList;
	HandCardValue uctHandCardValue;
};

//手牌数据类
class HandCardData
{
 
 
public:
	//构造函数
	HandCardData::HandCardData()
	{
	}
	//析构函数
	virtual HandCardData::~HandCardData()
	{
	}
 
public:
	  //手牌序列——无花色，值域3~17
    vector <int> value_nHandCardList;
 
	  //手牌序列——状态记录，便于一些计算，值域为该index牌对应的数量0~4
	int value_aHandCardList[18] = { 0 };
 
	  //手牌序列——有花色，按照从大到小的排列  56，52：大王小王……4~0：红3黑3方3花3
	vector <int> color_nHandCardList;
	  //手牌个数
	int nHandCardCount = 17 ;
	  //玩家角色地位       0：地主    1：农民——地主下家   2：农民——地主上家
	int nGameRole = -1;
	  //玩家座位ID 
	int nOwnIndex = -1;
	//玩家要打出去的牌类型
	CardGroupData uctPutCardType;
	//要打出去的牌——无花色
	vector <int> value_nPutCardList;
	//要打出去的牌——有花色
	vector <int> color_nPutCardList;
 
	HandCardValue uctHandCardValue;
public:
 
	//要打出的牌序列清空
	void ClearPutCardList();
 
	//手牌排序，大牌靠前
	void SortAsList(vector <int> &arr);
 
	//出一张牌，返回操作是否合法
	bool PutOneCard(int value_nCard, int &clear_nCard);
 
	//出一组牌，返回操作是否合法
	bool PutCards();
 
	//通过有花色手牌获取无花色手牌（包含两种结构）
	void get_valueHandCardList();
 
	//初始化
	void Init();
 
	//输出所有成员变量，用于测试
	void PrintAll();
 
};

void HandCardData::ClearPutCardList()
    {
    	color_nPutCardList.clear();
     
    	value_nPutCardList.clear();
     
    	uctPutCardType.cgType = cgERROR;
    	uctPutCardType.nCount = 0;
    	uctPutCardType.nMaxCard = -1;
    	uctPutCardType.nValue = 0;
     
    	return;
    }

void HandCardData::get_valueHandCardList()
{
	//清零
	value_nHandCardList.clear();
	memset(value_aHandCardList, 0,sizeof(value_aHandCardList));
	
	for (vector<int>::iterator iter = color_nHandCardList.begin(); iter != color_nHandCardList.end(); iter++)
	{
		value_nHandCardList.push_back((*iter / 4)+3);	
		value_aHandCardList[(*iter / 4) + 3]++;
	}
 
}

void HandCardData::Init()
{
	//根据花色手牌获取权值手牌
	get_valueHandCardList();
 
	//手牌 排序
	SortAsList(color_nHandCardList);
	SortAsList(value_nHandCardList);
	
	//当前手牌个数
	nHandCardCount = value_nHandCardList.size();
 
}

void HandCardData::PrintAll()
    {
     
     
    	cout << "color_nHandCardList:" << endl;
    	for (vector<int>::iterator iter = color_nHandCardList.begin(); iter != color_nHandCardList.end(); iter++)
    		cout << get_CardsName(*iter) << (iter == color_nHandCardList.end() - 1 ? '\n' : ',');
     
    	cout << endl;
    	/*
    	cout << "value_nHandCardList：" << endl;
    	for (vector<int>::iterator iter = value_nHandCardList.begin(); iter != value_nHandCardList.end(); iter++)
    		cout << *iter << (iter == value_nHandCardList.end() - 1 ? '\n' : ',');
    	cout << endl;
    	cout << "value_aHandCardList：" << endl;
    	for (int i = 0; i < 18; i++)
    	{
    		cout << value_aHandCardList[i] << (i == 17 ? '\n' : ',');
    	}
    	cout << endl;
    	cout << "nHandCardCount:" << nHandCardCount << endl;
    	cout << endl;
    	cout << "nGameRole:" << nGameRole << endl;
    	cout << endl;
    	*/
    }


bool  HandCardData::PutCards()
    {
    	for (vector<int>::iterator iter = value_nPutCardList.begin(); iter != value_nPutCardList.end(); iter++)
    	{
    		int color_nCard = -1;
    		if (PutOneCard(*iter, color_nCard))
    		{
    			color_nPutCardList.push_back(color_nCard);
    		}
    		else
    		{
    			return false;
    		}
    	}
     
    	nHandCardCount -= value_nPutCardList.size();
    	return true;
    }


bool  HandCardData::PutOneCard(int value_nCard, int &color_nCard)
{
	bool ret = false;
 
 
 
	//value状态数组处理
 
	value_aHandCardList[value_nCard]--;
 
	if (value_aHandCardList[value_nCard] < 0)
	{
		return false;
	}
 
 
	//value列表数组处理
	for (vector<int>::iterator iter = value_nHandCardList.begin(); iter != value_nHandCardList.end(); iter++)
	{
		if (*iter == value_nCard)
		{
			value_nHandCardList.erase(iter);
			ret = true;
			break;
		}
	}
 
 
	// color列表数组处理
 
	int k = (value_nCard - 3) * 4;      //数值转换
 
	for (vector<int>::iterator iter = color_nHandCardList.begin(); iter != color_nHandCardList.end(); iter++)
	{
 
		for (int i = k; i < k + 4; i++) 
		{
			if (*iter == i)
			{
				color_nCard = i;
				color_nHandCardList.erase(iter);
				return ret;
				
			}
		}
	}
	return false;
}