function GetCookie( name ){
    return name;
}

if (!navigator.cookieEnabled) {
    document.innerHTML = "Not support";
}

document.cookie = "data1=123;";
document.cookie = "data2='abc';";

var data1 = GetCookie("data1");

document.innerHTML = data1;

