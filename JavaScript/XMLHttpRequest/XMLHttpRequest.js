//
//
//
//xmlhttp.open("GET", "./save.txt");
//xmlhttp.onreadystatechange = function() {
//  if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
//    var disp = document.getElementById("disp");
//    disp.appendChild(document.createTextNode(xmlhttp.responseText));
//  }
//}
//xmlhttp.send(null);
//
//

var array = new Array();
array.push(10);
array.push(20);
array.push(40);
array.push(30);

function createXmlhttp() {
  var xmlhttp = false;
  try {
    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
  } catch (e) {
  }
  if (!xmlhttp && typeof XMLHttpRequest!='undefined') {
    xmlhttp = new XMLHttpRequest();
  }
  return xmlhttp;
}


function POST() {
  var xmlhttp = new createXmlhttp();
    
    var value = "";
    for (var i = 0; i < 3; ++i) {
        value += array[i];
    }
    
  if (xmlhttp) {
    xmlhttp.open('POST', './save.txt');
    xmlhttp.onreadystatechange = function() {
      if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        var disp = document.getElementById("disp");
        disp.innerHTML=xmlhttp.responseText;
      }
    }
    xmlhttp.setRequestHeader("Content-Type" , "application/x-www-form-urlencoded");
    xmlhttp.send(value);
  }
}

POST();
