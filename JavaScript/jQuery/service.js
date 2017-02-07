
var data = [
	['tuyano', 'tuyano@mac.com',     '090-9999-9999'],
	['taro',   'taro@yamada.hoge',   '03-3333-3333'],
	['hanako', 'hanako@flower.hoge', '080-7777-6666']
];

var id = Jaxer.request.data['id'];
var col = Jaxer.request.data['col'];


Jaxer.response.headers['Content-Type'] = 'text/plain';
Jaxer.response.setContents(data[id][col]);
