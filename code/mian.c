//最多手牌
#define HandCardMaxLen 20
//价值最小值
#define MinCardsValue -25
//价值最大值
#define MaxCardsValue 10
struct HandCardValue
{
	int SumValue;        //手牌总价值
	int NeedRound;       // 需要打几手牌
};

struct CardGroupData
{
	//枚举类型
	CardGroupType cgType=cgERROR;
	//该牌的价值
	int  nValue=0;
	//含牌的个数
	int  nCount=0;
	//牌中决定大小的牌值，用于对比
	int nMaxCard=0;
 
};

enum CardGroupType
{ 
	cgERROR = -1,						            //错误类型
	cgZERO = 0,						                //不出类型
    cgSINGLE = 1,									//单牌类型
    cgDOUBLE = 2,									//对牌类型
    cgTHREE	= 3,									//三条类型
    cgSINGLE_LINE = 4,								//单连类型
    cgDOUBLE_LINE = 5,								//对连类型
    cgTHREE_LINE = 6,								//三连类型
    cgTHREE_TAKE_ONE = 7,							//三带一单
    cgTHREE_TAKE_TWO = 8,							//三带一对
	cgTHREE_TAKE_ONE_LINE = 9,						//三带一单连
	cgTHREE_TAKE_TWO_LINE = 10,						//三带一对连
    cgFOUR_TAKE_ONE	= 11,							//四带两单
    cgFOUR_TAKE_TWO	= 12,							//四带两对
    cgBOMB_CARD	= 13,							    //炸弹类型
    cgKING_CARD	= 14								//王炸类型
};

//游戏全局类
class GameSituation 
{
public:
	//构造函数
	GameSituation::GameSituation()
	{
	}
	//析构函数
	virtual GameSituation::~GameSituation()
	{
	}
 
public:
 
 
	//地主玩家
	int nDiZhuID = -1;
	//本局叫分
	int nLandScore = 0;
 
	//当前地主玩家——还未确定
	int nNowDiZhuID = -1;
	//当前本局叫分——还未确定
	int nNowLandScore = 0;
 
	//三张底牌
	int DiPai[3] = { 0 };
	//已经打出的牌——状态记录，便于一些计算，值域为该index牌对应的数量0~4
	int value_aAllOutCardList[18] = { 0 };
	//三名玩家已经打出的手牌记录
	int value_aUnitOutCardList[3][18] = { 0 };
	//三名玩家已经剩余手牌个数
	int value_aUnitHandCardCount[3] = { 0 };
	//本局当前底分倍数
	int nMultiple = 0;
	//当前控手对象（用于区分是否可以自身任意出牌以及是否地主已经放弃出牌从而不去管队友）
	int nCardDroit = 0;
	//当前打出牌的类型数据，被动出牌时玩家根据这里做出筛选
	CardGroupData uctNowCardGroup;
	//本局游戏是否结束
	bool Over = false;
 
};

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

