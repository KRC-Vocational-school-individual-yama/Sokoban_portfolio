#include "selectmode.h"

#include"libs/scenemanager.h"
#include"save.h"
#include"selected.h"

namespace {
	static const int STAGENUM = 5;//初期ステージ数
};

SelectMode::SelectMode(Scene* sc)
	:Object		(sc)
	,keystop	(true)
	,stage		(0)
	,maxStage	(STAGENUM)
	,dispStr	()
{}
SelectMode::~SelectMode(){
}
void SelectMode::Init(){
	std::vector<std::string>fieldNumberStr;
	fieldNumberStr = CsvSave::Load("data/stagedata/fieldcount.csv");

	if (!fieldNumberStr.empty()) 
		maxStage = atoi(fieldNumberStr[0].c_str());
	
	dispStr.clear();

	for (int i = 0; i < maxStage; i++) 
		dispStr.emplace_back("stage_"+std::to_string(i+1));
}
void SelectMode::Update() {
	
	bool upKey		= CheckHitKey(KEY_INPUT_W)		|| CheckHitKey(KEY_INPUT_UP)	;
	bool downKey	= CheckHitKey(KEY_INPUT_S)		|| CheckHitKey(KEY_INPUT_DOWN)	;
	bool leftKey	= CheckHitKey(KEY_INPUT_A)		|| CheckHitKey(KEY_INPUT_LEFT)	;
	bool rightKey	= CheckHitKey(KEY_INPUT_D)		|| CheckHitKey(KEY_INPUT_RIGHT)	;
	
	bool enterKey	= CheckHitKey(KEY_INPUT_SPACE)	|| CheckHitKey(KEY_INPUT_RETURN);
	bool escapeKey	= CheckHitKey(KEY_INPUT_ESCAPE)	;
	
	bool allKey		= escapeKey|| enterKey || upKey || downKey || leftKey || rightKey;

	std::vector<bool> _key		 ;
	_key.emplace_back(upKey		);
	_key.emplace_back(downKey	);
	_key.emplace_back(leftKey	);
	_key.emplace_back(rightKey	);

	Update_UpDownLeftRight(_key	);
	
	if (enterKey && !keystop) {
		using namespace SceneManager;
		
		SelectedField* selectedField = GetCommonScene()->Invoke<SelectedField>();
		if(selectedField!=nullptr)
			selectedField->SetSelected(stage);
		
		SceneChange("Game");
	}
	
	if (escapeKey&& !keystop) 
		SceneManager::SceneChange("Title");
	
#ifdef _DEBUG
	bool tabKey = CheckHitKey(KEY_INPUT_TAB);
	if (tabKey&&!keystop) 
		SceneManager::SceneChange("Title");
	
	bool createField	= CheckHitKey(KEY_INPUT_N) && CheckHitKey(KEY_INPUT_LSHIFT) && CheckHitKey(KEY_INPUT_LCONTROL) ;
	bool destroyField	= CheckHitKey(KEY_INPUT_M) && CheckHitKey(KEY_INPUT_LSHIFT) && CheckHitKey(KEY_INPUT_LCONTROL) ;
	
	std::vector<bool>keyDebug			 ;
	keyDebug.emplace_back(createField	);
	keyDebug.emplace_back(destroyField	);

	Update_InCreateDestroy(keyDebug		);

	keystop = allKey || destroyField || createField || tabKey;
#else
	keystop = allKey ;
#endif
}

void SelectMode::Draw() {
	//選択が10個よりも下なら一列
	if (maxStage < 10) {

		//カーソル　選択場所
		DrawFormatString(50, 100 + stage * 32, 0xffffff, "→");
		DrawBox(50, 100 + stage * 32, 190, 120 + stage * 32, 0xffffff, false);

		//選択項目
		for (int i = 0; i < dispStr.size(); i++)
			DrawFormatString(100, 100 + i * 32, 0xffffff, dispStr[i].c_str());
	}
	else {
		const int loopMax = maxStage / 10+maxStage%10;
		//選択が10以上なら横にも一列づつ
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < loopMax; j++) {

				int index = i+j*10;
				if (index >= maxStage)
					continue;

				int offsetX = (stage/10) * 132;
				int offsetY = (stage%10) * 32;

				//カーソル　選択場所
				DrawFormatString(50+ offsetX, 100 + offsetY, 0xffffff, "→");
				DrawBox(50+ offsetX, 100 + offsetY, 190+ offsetX, 120 + offsetY, 0xffffff, false);

				//選択項目
				offsetX = j * 132;
				offsetY = i * 32;
				DrawFormatString(100+offsetX, 100 + offsetY, 0xffffff, dispStr[index].c_str());
			}
		}
	}
#ifdef _DEBUG
	printfDx("\n");
	printfDx("LCONTROL + LShift + Nキーで　ステージ追加\n");
	printfDx("LCONTROL + LShift + Mキーで　ステージ削除\n");
#endif
}

void SelectMode::SaveStageNum(){
	std::vector<std::string>str;
	str.clear();
	str.emplace_back(std::to_string(maxStage));

	CsvSave::Save("data/stagedata/fieldcount.csv",str);
}

void SelectMode::Update_UpDownLeftRight(const std::vector<bool>& _key){

	enum key {
		up
		, down
		, left
		, right
	};

	if (_key[key::up] && !keystop) {
		stage--;
		if (stage < 0)
			stage = maxStage - 1;

		if (stage > maxStage - 1)
			stage = maxStage - 1;
	}

	if (_key[key::down] && !keystop) {
		stage++;
		if (stage > maxStage - 1)
			stage = 0;

		if (stage < 0)
			stage = maxStage - 1;
	}

	if (_key[key::left] && !keystop) {
		stage -= 10;
		if (stage < 0)
			stage = 0;
	}

	if (_key[key::right] && !keystop) {
		stage += 10;
		if (stage >= maxStage - 1)
			stage = maxStage - 1;
	}
}

void SelectMode::Update_InCreateDestroy(const std::vector<bool>& _key){

	enum key {
		createField
		,destroyField
	};

	if (_key[key::createField] && !keystop) {
		if (maxStage < 50) {
			maxStage++;

			dispStr.emplace_back("stage_" + std::to_string(maxStage));

			SaveStageNum();
		}
	}

	if (_key[key::destroyField] && !keystop) {
		maxStage--;

		if (maxStage < 1)
			maxStage = 1;

		if (!dispStr.empty() && dispStr.size() != 1)
			dispStr.pop_back();

		SaveStageNum();
	}

}

