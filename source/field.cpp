#include "field.h"

#include"libs/scenemanager.h"
#include"save.h"
#include"player.h"
#include"selected.h"

namespace {
	static const int SPACE_LFNGTH = 1;// Field Chip 間の空き具合
}

Field::Field(Scene* sc)
	:Object			(sc)
	,field			()
	,hImage			(-1)
	,xShaftMaxNum	(10)
	,keystop		(false)
{}
Field::~Field() {
	if (hImage > 0)
		DeleteGraph(hImage);
}
void Field::Init() {
	field.clear();
	hImage = LoadGraph("data/texture/mapchip.png");
	assert(hImage > 0);

	//.csvからステージを読む
	Load();

	//無ければ生成
	if (!field.empty())
		return;

	for (int j = 0; j < xShaftMaxNum; j++) {
		for (int i = 0; i < 10; i++) {
			int index = IndexChange(i, j);

			if (i == 0 || j == 0 || i == 9 || j == 9) {
				field.emplace_back(1);
			}
			else {
				field.emplace_back(0);
			}

			if (i == 2 && j == 1)
				field[index] = static_cast<int>(FieldInsideNumber::playerStart	);
			if (i == 3 && j == 3)
				field[index] = static_cast<int>(FieldInsideNumber::boxStart		);
			if (i == 3 && j == 5)
				field[index] = static_cast<int>(FieldInsideNumber::boxStart		);
			if (i == 4 && j == 5)
				field[index] = static_cast<int>(FieldInsideNumber::gool_Green	);
		}
	}
}
void Field::Update() {
#ifdef _DEBUG

	//Ctrl + s で保存
	bool lControl	 = CheckHitKey(KEY_INPUT_LCONTROL)	;
	bool sKey		 = CheckHitKey(KEY_INPUT_S)			;
	bool saveKey	 = lControl && sKey					;
	if (saveKey && !keystop) 
		Save()											;

	keystop			 = saveKey							;
#endif
}
void Field::Draw() {
	using namespace PlayerConfig;
	int size		 = BODY_SIZE;
	int halfSize	 = 0;

#ifdef _DEBUG
	halfSize		 = size / 2;
	halfSize		-= SPACE_LFNGTH;
#else
	halfSize = size / 2;
	DrawBox(START_OFFSET_POSX - halfSize				, START_OFFSET_POSY - halfSize				,
			START_OFFSET_POSX - halfSize + 10 * size	, START_OFFSET_POSY - halfSize + 10 * size	,
			0x000000, true);
#endif
	for (int j = 0; j < xShaftMaxNum; j++) {//y
		for (int i = 0; i < 10; i++) {//x

			const int index			= IndexChange(i, j);
			const int x				= START_OFFSET_POSX + i * size;
			const int y				= START_OFFSET_POSY + j * size;
			const int fieldNumber	= field[index];
			bool full				= false;

			if (fieldNumber == 1)
				full = true;

#ifdef _DEBUG

			//四角
			Vec2 boxPos		= { x - halfSize ,y - halfSize };
			Vec2 boxPos2	= { x + halfSize ,y + halfSize };

			DrawBoxVec2(boxPos, boxPos2,0xffffff,full);

			if (i == 1 && j == 0) 
				printfDx("0 0 x:y  =  %d,%d\n", x, y);

			using ffInside	= Field::FieldInsideNumber;
			ffInside ffinSideNum = static_cast<ffInside>(fieldNumber);
			std::vector<unsigned int>color;
			color.emplace_back(0x888888);
			color.emplace_back(0xd6c6af);
			color.emplace_back(0xdddd22);
			color.emplace_back(0xdd2222);

			switch (ffinSideNum){
			case ffInside::normal:		DrawBoxVec2(boxPos,boxPos2,color.at(fieldNumber    ),true);break;
			case ffInside::playerStart:	DrawBoxVec2(boxPos,boxPos2,color.at(fieldNumber -1 ),true);break;
			case ffInside::boxStart:	DrawBoxVec2(boxPos,boxPos2,color.at(fieldNumber -1 ),true);break;
			case ffInside::gool_Bule:	DrawBoxVec2(boxPos,boxPos2,color.at(fieldNumber -1 ),true);break;
			default:break;
			}
#else
			Vec2 chip;
			chip			= ChipSelect(static_cast<FieldInsideNumber>(field[index]));
			int widthSize	= 256 / 8;
			int heightSize	= 160 / 5;

			DrawRectExtendGraph(x - halfSize, y - halfSize, x + halfSize, y + halfSize,
				widthSize * chip.x, heightSize * chip.y, widthSize, heightSize, hImage, true);
#endif
		}
	}
}

int Field::IndexChange(int _i, int _j, int _maxHorizontal, int _max) {
	const int index = _i + _maxHorizontal * _j;
	
	if (index < 0) {
		return 0;
	}
	else if (index > _max) {
		return _max;
	}

	return index;
}
int Field::IndexChange(Vec2 _pos, int _maxHorizontal, int _max) {
	const int index = _pos.x + _maxHorizontal * _pos.y;

	if (index < 0) {
		return 0;
	}
	else if (index > _max) {
		return _max;
	}

	return index;
}

int Field::GetfieldInside(const int _i, const int _j) {
	if (field.empty())
		return -1;

	int ansNum = field[IndexChange(_i, _j)];
	const int fieldMax = static_cast<int>(FieldInsideNumber::max);

	if (ansNum > fieldMax)
		ansNum = -1;
	if (ansNum >= fieldMax)
		assert(false);

	return ansNum;
}

int Field::GetfieldInside(const Vec2 _pos) {
	if (field.empty())
		return -1;

	int ansNum = field[IndexChange(_pos)];
	const int fieldMax = static_cast<int>(FieldInsideNumber::max);

	if (ansNum > fieldMax)
		ansNum = -1;
	if (ansNum >= fieldMax)
		assert(false);

	return ansNum;
}

int Field::GetClearColor(const Vec2 _pos) {
	const int index			= IndexChange(_pos);
	const int fieldGoolBlue = static_cast<int>(FieldInsideNumber::gool_Bule);
	int color				= field[index];

	color -= fieldGoolBlue;
	color /= 2;
	
	if (color < 0)
		color = 0;

	return color;
}

void Field::SetFieldInside(Vec2 _pos, int _chip) {
	if (field.empty())
		return;

	const int safetyIndex	= IndexChange(_pos);
	if (static_cast<unsigned int>(safetyIndex) > field.size())
		return;

	const int fieldMax		= static_cast<int>(FieldInsideNumber::max) - 1;
	if (_chip > fieldMax)
		return;

	field[safetyIndex] = _chip;
}

Vec2 Field::GetPlayerStart() {
	for (int i = 0; i < 10; i++) {//x
		for (int j = 0; j < xShaftMaxNum; j++) {//y

			const int fieldPlayerStart	= static_cast<int>(FieldInsideNumber::playerStart);
			const int insidenum			= field[IndexChange(i, j)];

			if (insidenum != fieldPlayerStart)
				continue;

			return{ i,j };
		}
	}
	return Vec2();
}

std::vector<Vec2> Field::GetBoxStart() {
	std::vector<Vec2> pos	;
	std::vector<int>boxPos	;
	pos.clear()				;
	boxPos.clear()			;

	boxPos.emplace_back(static_cast<int>(FieldInsideNumber::boxStart)				);
	boxPos.emplace_back(static_cast<int>(FieldInsideNumber::boxStartAndGool_Green)	);
	boxPos.emplace_back(static_cast<int>(FieldInsideNumber::boxStartAndGool_Bule)	);
	boxPos.emplace_back(static_cast<int>(FieldInsideNumber::boxStartAndGool_Red)	);
	boxPos.emplace_back(static_cast<int>(FieldInsideNumber::boxStartAndGool_Yellow)	);

	for (int j = 0; j < xShaftMaxNum; j++) {//y
		for (int i = 0; i < 10; i++) {//x
			const int insidenum = field[IndexChange(i, j)];
			bool isContinue = false;

			for (auto aBox : boxPos) {
				if (insidenum == aBox)
					isContinue = true;
			}

			if (!isContinue)
				continue;

			pos.emplace_back(Vec2{i,j});

		}
	}
	return pos;
}

std::vector<Vec2> Field::GetClearPos() {
	std::vector<Vec2> pos	;
	std::vector<int>gool	;
	gool.clear()			;
	pos.clear()				;

	gool.emplace_back(static_cast<int>(FieldInsideNumber::gool_Green)				);
	gool.emplace_back(static_cast<int>(FieldInsideNumber::boxStartAndGool_Green)	);
	gool.emplace_back(static_cast<int>(FieldInsideNumber::gool_Bule)				);
	gool.emplace_back(static_cast<int>(FieldInsideNumber::boxStartAndGool_Bule)		);
	gool.emplace_back(static_cast<int>(FieldInsideNumber::gool_Red)					);
	gool.emplace_back(static_cast<int>(FieldInsideNumber::boxStartAndGool_Red)		);
	gool.emplace_back(static_cast<int>(FieldInsideNumber::gool_Yellow)				);
	gool.emplace_back(static_cast<int>(FieldInsideNumber::boxStartAndGool_Yellow)	);

	for (int j = 0; j < xShaftMaxNum; j++) {//y
		for (int i = 0; i < 10; i++) {//x

			const int insidenum = field[IndexChange(i, j)];
			bool isContinue = false;

			for (auto g : gool) {
				if (insidenum == g)
					isContinue = true;
			}

			if ( !isContinue)
				continue;

			pos.emplace_back(Vec2{ i, j });
		}
	}
	return pos;
}

void Field::Save() {
	SelectedField* selectedField = SceneManager::GetCommonScene()->Invoke<SelectedField>();
	if (selectedField == nullptr)
		return;

	const int stageNum	 = selectedField->GetSelected()	;
	std::string pass	 = ""							;
	pass				+= "data/stagedata/field"		;
	pass				+= std::to_string(stageNum)		;
	pass				+= ".csv"						;
	std::vector<std::string>saveData					;
	saveData.clear()									;

	for (int i = 0; static_cast<unsigned int>(i) < field.size(); i++)
		saveData.emplace_back(std::to_string(field[i]))	;
	
	CsvSave::Save(pass, saveData);
}

void Field::Load() {
	SelectedField* selectedField = SceneManager::GetCommonScene()->Invoke<SelectedField>();
	
	if (selectedField == nullptr)
		return;

	const int stageNum = selectedField->GetSelected();
	std::vector<std::string> fileStr = CsvSave::Load("data/stagedata/field" + std::to_string(stageNum) + ".csv");

	if (fileStr.empty())
		return;

	for (int i = 0; static_cast<unsigned int>(i) < fileStr.size(); i++) {
		if (fileStr[i].c_str() == "-") {
			i++;
			field.emplace_back(-1);
			continue;
		}
		const int inNumber = atoi(fileStr[i].c_str());
		field.emplace_back(inNumber);
	}

}

Vec2 Field::ChipSelect(FieldInsideNumber _fieldNum) {
	using ffInside = Field::FieldInsideNumber;
	switch (_fieldNum){
	case ffInside::empty:
		//return{0,0};
		return{ 4,3 };
		break;
	case ffInside::normal:
	case ffInside::playerStart:	/* yes fall down */
	case ffInside::boxStart:	/* yes fall down */
		return { 3,0 };
		//return {2,4};
		//return {1,0};

		break;
	case ffInside::wall:
		//return {4,1};
		//return {2,3};
		return { 4,4 };
		break;
	case ffInside::gool_Bule:
	case ffInside::boxStartAndGool_Bule:	/* yes fall down */
		return { 2,3 };
		break;
	case ffInside::gool_Green:
	case ffInside::boxStartAndGool_Green:	/* yes fall down */
		return { 5,0 };
		break;
	case ffInside::gool_Red:
	case ffInside::boxStartAndGool_Red:	/* yes fall down */
		return { 1,4 };
		break;
	case ffInside::gool_Yellow:
	case ffInside::boxStartAndGool_Yellow:	/* yes fall down */
		return { 5,3 };
		break;
	case ffInside::max:
		return{ 0,0 };
		break;
	default:
		return{ 4,3 };
		break;
	}

	return Vec2();
}