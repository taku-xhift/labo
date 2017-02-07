function init(){
    window.addEventListener("devicemotion", deviceMotion);
};
 
function deviceMotion(e) {
    e.preventDefault();
    var ac = e.acceleration;
    var ag = e.accelerationIncludingGravity;
    var rt = e.rotationRate;
        document.getElementById("ac0").innerHTML = "X: " + ac.x;
        document.getElementById("ac1").innerHTML = "Y: " + ac.y;
        document.getElementById("ac2").innerHTML = "Z: " + ac.z;
        
        document.getElementById("ag0").innerHTML = "X: " + ag.x;
        document.getElementById("ag1").innerHTML = "Y: " + ag.y;
        document.getElementById("ag2").innerHTML = "Z: " + ag.z;
        
        document.getElementById("rt0").innerHTML = "ALPHA: " + rt.alpha;
        document.getElementById("rt1").innerHTML = "BETA: " + rt.beta;
        document.getElementById("rt2").innerHTML = "GAMMA: " + rt.gamma;
}