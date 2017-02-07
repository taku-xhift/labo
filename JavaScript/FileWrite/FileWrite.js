


fs.root.getFile(filename, { create: true },
  function(fileEntry){
    var text = "ファイルパス："+fileEntry.fullPath+"<br>";
    text += "ファイル名："+fileEntry.name+"<br>";
    document.getElementById("result").innerHTML = text;
  },
  function(err){  // 失敗時のコールバック関数
    document.getElementById("result").innerHTML = "ファイル生成エラー!!<br>"+err;
  }
);


