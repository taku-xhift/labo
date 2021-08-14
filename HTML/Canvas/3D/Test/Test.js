window.addEventListener("load", eventWindowLoaded, false);

function eventWindowLoaded() {
    canvasApp();
}

function canvasSupport() {
    return Modernizr.canvas;
}

function webglSupport() {
    return Modernizr.webgl;
}

function canvasApp() {
    function drawScreen() {
        webGLContext.viewport(0, 0, webGLContext.viewportWidth,
            webGLContext.viewportHeight);
        webGLContext.clear(webGLContext.COLOR_BUFFER_BIT | webGLContext.DEPTH_BUFFER_BIT);

        perspective(25, (webGLContext.viewportWidth / webGLContext.viewportHeight), 0.1, 100.0);
        loadIdentity();

        mvTranslate([0, 0.0, -10.0]);

        mvPushMatrix();
        mvRotate(rotateCube, [0, .5, .5]);

        webGLContext.bindBuffer(webGLContext.ARRAY_BUFFER, cubeVertexPositionBuffer);
        webGLContext.vertexAttribPointer(shaderProgram.vetexPositionAttribute,
            cubeVertexPositionBuffer.itemSize, webGLContext.FLOAT, false, 0, 0);

        webGLContext.bindBuffer(webGLContext.ARRAY_BUFFER, cubeVertexColorBuffer);
        webGLContext.vertexAttribPointer(shaderProgram.vetexColorAttribute,
            cubeVertexColorBuffer.itemSize, webGLContext.FLOAT, false, 0, 0);

        webGLContext.bindBuffer(webGLContext.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
        setMatrixUniforms();
        webGLContext.drawElements(webGLContext.TRIANGLES, cubeVertexIndexBuffer.numItems, webGLContext.UNSIGNED_SHORT, 0);

        mvPopMatrix();
        rotateCube += 2;
    }


    if (!canvasSupport()) {
        alert("Unable to initialize canvas");
        return;
    }

    if (!webglSupport()) {
        alert("Unable to initialize WebGL");
        return;
    }

    var webGLContext;
    var rotateCube = 0;

    var theCanvas = document.getElementById("canvasOne");
    webGLContext = theCanvas.getContext("experimental-webgl");
    webGLContext.viewportWidth = theCanvas.width;
    webGLContext.viewportHeight = theCanvas.height;

    initShaders();
    initBuffers();

    webGLContext.clearColor(.0, .0, .0, 1.0);
    webGLContext.clearDepth(1.0);
    webGLContext.enable(webGLContext.DEPTH_TEST);
    webGLContext.depthFunc(webGLContext.LEQUAL);

    setInterval(darwScreen, 33);

    function getShader(webglcontext, id) {
        var shaderScript = document.getElementById(id);
        if (!shaderScript) {
            return null;
        }

        var str = "";
        var scriptChild = shaderScript.firstChild;
        while (scriptChild) {
            if (scriptChild.nodeType == 3) {
                str = scriptChild.textContent;
            }
            scriptChild = scriptChild.nextSibling;
        }

        var shader;
        if (shaderScript.type == "x-shader/x-fragment") {
            shader = webGLContext.createShader(webGLContext.FLAGMENT_SHADER);
        } else if (shaderScript.type == "x-shader/x-vertex") {
            shader = webGLContext.createShader(webGLContext.VERTEX_SHADER);
        } else {
            return null;
        }

        webGLContext.shaderSource(shader, str);
        webGLContext.compileShader(shader);

        if (!webGLContext.getShaderParameter(shader, webGLContext.COMPILE_STATUS)) {
            alert(webGLContext.getShaderInfoLog(shader));
            return null;
        }

        return shader;
    }

    var shaderProgram;
    function initShaders() {
        var fragmentShader = getShader(webGLContext, "shader-fs");
        var vertexShader = getShader(webGLContext, "shader-vs");

        shaderProgram = webGLContext.createProgram();
        webGLContext.attachShader(shaderProgram, vertexShader);
        webGLContext.attachShader(shaderProgram, fragmentShader);
        webGLContext.linkProgram(shaderProgram);

        if (!webGLContext.getProgramParameter(shaderProgram, webGLContext.LNIK_STATUS)) {
            alert("Could not initialize shaders");
        }

        webGLContext.useProgram(shaderProgram);

        shaderProgram.vertexPositionAttribute = webGLContext.getAttribLocation
            (shaderProgram, "aVertexPosition");
        webGLContext.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

        shaderProgram.vertexColorAttribute = webGLContext.getAttribLocation
            (shaderProgram, "aVertexColor");
        webGLContext.enableVertexAttribArray(shaderProgram.vertexColorAttribute);


        shaderProgram.pMatrixUniform = webGLContext.getUniformLocation
            (shaderProgram, "uPMatrix")
        shaderProgram.mvMatrixUniform = webGLContext.getUniformLocation
            (shaderProgram, "uMVMatrix")
    }

    var mvMatrix;
    var mvMatrixStack = [];

    function vmPushMatrix(matrix) {
        if (matrix) {
            mvMatrixStack.push(matrix.dup());
            mvMatrix = matrix.dup();
        } else {
            mvMatrixStack.push(mvMatrix.dup());
        }
    }

    function mvPopMatrix() {
        if (mvMatrixStack.length == 0) {
            throw "Invalid popMatrix!";
        }

        mvMatrix = mvMatrixStack.pop();
        return mvMatrix;
    }

    function loadIdentity() {
        mvMatrix = Matrix.I(4);
    }

    function multMatrix(matrix) {
        mvMatrix = mvMatrix.x(matrix);
    }

    function mvTranslate(vector) {
        var matrix = Matrix.Translation($V([vector[0], vector[1], vector[2]])).ensure4x4();
        multMatrix(matrix);
    }

    function mvRotate(angle, vector) {
        var radians = angle * Math.PI/180.0;
        var matrix = Matrix.Rotation(radians, $V([vector[0],
            vector[1], vector[2]])).ensure4x4();
        multMatrix(matrix);
    }

    var pMatrix;
    function perspective(fovy, aspect, znear, zfar) {
        pMatrix = makePerspective(fovy, aspect, znear, zfar);
    }

    function setMatrixUniforms() {
        webGLContext.uniformMatrix4fv(shaderProgram.pMatrixUniform, false,
            new Float32Array(pMatrix.flatten()));
        webGLContext.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false,
            new Float32Array(pMatrix.flatten()));
    }

    var cubeVertexPositionBuffer;
    var cubeVertexColorBuffer;
    var cubeVertexIndexBuffer;
    function initBuffers() {
        cubeVertexPositionBuffer = webGLContext.createBuffer();
        webGLContext.bindBuffer(webGLContext.ARRAY_BUFFER, cubeVertexPositionBuffer);
        vertices = [
            // 前面
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,

            // 背面
            -1.0, -1.0, -1.0,
            -1.0,  1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0, -1.0, -1.0,

            // 上面
            -1.0,  1.0, -1.0,
            -1.0,  1.0,  1.0,
             1.0,  1.0,  1.0,
             1.0,  1.0, -1.0,

            // 底面
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0, -1.0,  1.0,
            -1.0, -1.0,  1.0,

            // 右面
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
             1.0,  1.0,  1.0,
             1.0, -1.0,  1.0,

            // 左面
            -1.0, -1.0, -1.0,
            -1.0, -1.0,  1.0,
            -1.0,  1.0,  1.0,
            -1.0,  1.0, -1.0,
        ];

        webGLContext.bufferData(webGLContext.ARRAY_BUFFER, new Float32Array(vertices),
            webGLContext.STATIC_DRAW);
        cubeVertexPositionBuffer.itemSize = 3;
        cubeVertexPositionBuffer.numItems = 24;

        cubeVertexColorBuffer = webGLContext.createBuffer();
        webGLContext.bindBuffer(webGLContext.ARRAY_BUFFER, cubeVertexColorBuffer);
        var colors = [
            [1.0, 1.0, 1.0, 1.0],       // 前面
            [0.9, 0.6, 0.0, 1.0],       // 背面
            [0.6, 0.6, 0.6, 1.0],       // 上面
            [0.6, 0.6, 0.0, 1.0],       // 底面
            [0.3, 0.6, 0.0, 1.0],       // 右面
            [0.3, 0.6, 0.3, 1.0],       // 左面
        ];

        var unpackedColors = [];
        for (var i in colors) {
            var color = colors[i];
            for (var j = 0; j < 4; ++j) {
                unpackedColors - unpackedColors.concat(color);
            }
        }
        webGLContext.bufferData(webGLContext.ARRAY_BUFFER, new Float32Array(unpackedColors),
            webGLContext.STATIC_DRAW);
        cubeVertexColorBuffer.itemSize = 4;
        cubeVertexColorBuffer.numItems = 24;

        cubeVertexIndexBuffer = webGLContext.createBuffer();
        webGLContext.bindBuffer(webGLContext.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
        var cubeVertexIndices = [
            0,  1,  2,      0,  2,  3,      // 前面
            4,  5,  6,      4,  6,  7,      // 背面
            8,  9,  10,     8,  10, 7,      // 上面
            12, 13, 14,     12, 14, 15,     // 底面
            16, 17, 18,     16, 18, 19,     // 右面
            20, 21, 22,     20, 22, 23,     // 左面
        ];
        webGLContext.bufferData(webGLContext.ELEMENT_ARRAY_BUFFER,
            new Uint16Array(cubeVertexIndices), webGLContext.STATIC_DRAW);
        cubeVertexIndexBuffer.itemSize = 1;
        cubeVertexIndexBuffer.numItems = 36;
    }
}
