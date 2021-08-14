/*
 * Finite State Machine using MSXML (Microsoft XML Parser 2.0)
 */

#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>

#import "msxml.dll"

using namespace std;
using namespace MSXML;

/*
 * elementからattribute_nameなるアトリビュート値を取り出す
 */
inline string get_attribute(MSXML::IXMLDOMElementPtr element, const char* attribute_name) {
	return (const char*)_bstr_t(element->getAttribute(attribute_name));
}

/*
 * parentの子nodeの中からattribute_nameなるアトリビュート値がkeyに一致するものを見つける
 */
MSXML::IXMLDOMElementPtr find_element(MSXML::IXMLDOMNodePtr parent, const char* attribute_name, const string& key) {
	MSXML::IXMLDOMElementPtr element;
	for ( MSXML::IXMLDOMNodePtr node = parent->firstChild; node != 0; node = node->nextSibling ) {
		if ( node->nodeType == MSXML::NODE_ELEMENT ) {
			element = node;
			if ( get_attribute(element,attribute_name) == key )
				return element;
		}
	}
	return 0;
}

/*
 * ----- main -----
 */
int main(int argc, char* argv[]) {
	
	if ( argc != 2 ) {
		cerr << "fsm <URL for FSM>" << endl;
		return 1;
	}
	
	if ( FAILED(CoInitialize(0)) ) {
		cerr << "Can't initialize COM" << endl;
		return 1;
	}
	
	try {
		
		/*
		 * XML Parser の生成と初期化
		 */
		MSXML::IXMLDOMDocumentPtr document("MSXML.DOMDocument");
		document->validateOnParse = VARIANT_TRUE; // 検証を行う
		document->async = VARIANT_FALSE;          // Parse完了までloadメソッドをブロック
		
		/*
		 * 引数に与えられたURLで示されたXMLをロードする
		 */
		document->load(argv[1]);
		
		/*
		 * Parseエラーがあれば出力
		 */
		MSXML::IXMLDOMParseErrorPtr error = document->parseError;
		if ( error->errorCode != 0 ) {
			if ( error->line ) {
				cerr << "line     : " << error->line << endl;
				cerr << "position : " << error->linepos << endl;
				cerr << "source   : " << (const char*)error->srcText << endl;
			}
			cerr << "URL        : " << (const char*)error->url       << endl;
			cerr << "code       : " << error->errorCode << endl;
			cerr << "reason     : " << (const char*)error->reason    << endl;
			return 1;
		}
		
		/*
		 * ルートエレメントを取得する
		 */
		MSXML::IXMLDOMElementPtr root = document->documentElement;
		
		/*
		 * 全イベントを取り出す
		 */
		set<string> event_set;
		MSXML::IXMLDOMNodeListPtr events = root->getElementsByTagName("Event");
		for ( int i = 0; i < events->length; ++i ) {
			MSXML::IXMLDOMElementPtr node = events->item[i];
			event_set.insert(get_attribute(node,"name"));
		}
		
		/*
		 * 初期状態 / 終了状態 を取得する
		 */
		string state_name     = get_attribute(root,"initial");
		string terminal_name  = get_attribute(root,"terminal");
		
		string fsm_name       = get_attribute(root,"name");
		cout << "FSM : " << fsm_name << endl;
		
		/*
		 * 状態遷移表を駆動する
		 */
		while ( state_name != terminal_name ) {
			
			/*
			 * state_name で示される State を見つける
			 */
			MSXML::IXMLDOMElementPtr state  = find_element(root,"name",state_name);
			if ( state == 0 ) {
				cerr << "can't find state : " << state_name << endl;
				break;
			}
			
			/*
			 * 現在の状態とイベント一覧を出力する
			 */
			cout << "state : " << state_name << endl;
			cout << "enter an event (";
			copy(event_set.begin(), event_set.end(), ostream_iterator<string>(cout,","));
			cout << "exit) ? " << flush;
			
			/*
			 * ユーザからのイベント入力
			 */
			string event_name;
			cin >> event_name;
			if ( event_name == "exit" )
				break;
			if ( event_set.find(event_name) == event_set.end() ) {
				cerr << event_name << " is not valid." << endl;
				continue;
			}
			
			/*
			 * event_name で示される Event を見つける
			 */
			MSXML::IXMLDOMElementPtr event = find_element(state,"name",event_name);
			if ( event == 0 ) {
				cerr << "can't find event : " << event_name << endl;
				break;
			}
			
			/*
			 * アクションを実行する
			 */
			string action_name = get_attribute(event,"action");
			if ( action_name != "none" )
				cout << "action : " << action_name << endl;
			
			/*
			 * 次の状態へ遷移する
			 */
			string transition_name = get_attribute(event,"transition");
			if ( transition_name != "none" )
				state_name = transition_name;
		}
		
	} catch ( _com_error& ex ) {
		cerr << "COM error occurred : " << ex.ErrorMessage() << endl;
	}
	
	CoUninitialize();
	return 0;
}
