import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';


// void main() => runApp(new MyApp());
void main() {
  debugPaintSizeEnabled = true;
  debugPaintBaselinesEnabled = true;
  debugPaintPointersEnabled = true;
  runApp(new MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Flutter Demo',
      theme: new ThemeData(
        // This is the theme of your application.
        //
        // Try running your application with "flutter run". You'll see the
        // application has a blue toolbar. Then, without quitting the app, try
        // changing the primarySwatch below to Colors.green and then invoke
        // "hot reload" (press "r" in the console where you ran "flutter run",
        // or press Run > Flutter Hot Reload in IntelliJ). Notice that the
        // counter didn't reset back to zero; the application is not restarted.
        primarySwatch: Colors.blue,
      ),
      home: new MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String title;

  @override
  _MyHomePageState createState() => new _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _counter = 0;

  void _incrementCounter() {
    setState(() {
      // This call to setState tells the Flutter framework that something has
      // changed in this State, which causes it to rerun the build method below
      // so that the display can reflect the updated values. If we changed
      // _counter without calling setState(), then the build method would not be
      // called again, and so nothing would appear to happen.
      _counter++;
    });
  }

  @override
  Widget build(BuildContext context) {
    // This method is rerun every time setState is called, for instance as done
    // by the _incrementCounter method above.
    //
    // The Flutter framework has been optimized to make rerunning build methods
    // fast, so that you can just rebuild anything that needs updating rather
    // than having to individually change instances of widgets.


      Widget weekHeader;
      weekHeader = new Container(
        margin: const EdgeInsets.only( top: 10.0),
        child: new Row(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
            new Container(
              // decoration: new BoxDecoration(
              //   border: new Border.all(
              //     width: 1.0,
              //     color: Colors.black
              //   ),
              // ),
              child: new Text('Sun', style: new TextStyle( color: Colors.red),),
            ),
            new Container(
              child: new Text('Mon'),
            ),
            new Container(
              child: new Text('Thu'),
            ),
            new Container(
              child: new Text('Wed'),
            ),
            new Container(
              child: new Text('Tur'),
            ),
            new Container(
              child: new Text('Fri'),
            ),
            new Container(
              child: new Text('Sut', textAlign: TextAlign.left, style: new TextStyle( color: Colors.blue),),
            ),
        ],
      ));


      Widget line1 = new Expanded(
        // margin: const EdgeInsets.only( top: 10.0),
        child: new Flex(
          direction: Axis.horizontal,//new Row(
          mainAxisSize: MainAxisSize.max,
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
            new Container(
              width: 30.0,
              decoration: new BoxDecoration(
                border: new Border(top: new BorderSide(
                  width: 1.0,
                  color: Colors.black
                ),),
              ),
              child: new Column(
                children: <Widget>[
                  new Text('1'),
                  new Container(
                    decoration: new BoxDecoration(
                      color: Colors.blue[200],
                    ),
                    child: new Text('ランチミーティング', softWrap: false,),
                  )
                ],
              ),
            ),
            new Container(
              child: new Text('2'),
            ),
            new Container(
              child: new Text('3'),
            ),
            new Container(
              child: new Text('4'),
            ),
            new Container(
              child: new Text('5'),
            ),
            new Container(
              child: new Text('6'),
            ),
            new Container(
              child: new Text('7'),
            ),
        ],
      ));

    // Widget line1 = new GridView.count(
    //   primary: false,
    //   padding: const EdgeInsets.all(20.0),
    //   crossAxisSpacing: 10.0,
    //   crossAxisCount: 2,
    //   children: <Widget>[
    //     const Text('He\'d have you all unravel at the'),
    //     const Text('Heed not the rabble'),
    //     const Text('Sound of screams but the'),
    //     const Text('Who scream'),
    //     const Text('Revolution is coming...'),
    //     const Text('Revolution, they...'),
    //   ],);



    return new Scaffold(
      appBar: new AppBar(
        // Here we take the value from the MyHomePage object that was created by
        // the App.build method, and use it to set our appbar title.
        title: new Text(widget.title),
      ),
      body: new Column(
        children: <Widget>[
          weekHeader,
          line1,
        ],
      ),
      // body: new Container(
      //   decoration: new BoxDecoration(
      //     color: Colors.black12
      //   ),
      //   child: new Row(
      //     children: <Widget>[
      //       new Expanded(
      //         child: new Container(
      //             decoration: new BoxDecoration(
      //               border: new Border.all(color: Colors.black, style: )
      //             ),
      //         ),
      //       )
      //     ],
      //   ),
      // ),





      // body: new CustomScrollView(
      //   primary: false,
      //   slivers: <Widget>[
      //     new SliverPadding(
      //       padding: const EdgeInsets.all(0.0),
      //       sliver: new SliverGrid.count(
      //         crossAxisSpacing: 10.0,
      //         crossAxisCount: 7,
      //         children: <Widget>[
      //           // new Expanded(
      //           //   child: new Container(
      //           //     decoration: new BoxDecoration(
      //           //       border: new Border.all(width: 1.0, color: Colors.black45)
      //           //     ),
      //           //     // child: new Text('Sun', style: new TextStyle(color: Colors.red),),
      //           //   ),
      //           // ),



      //             new Container(
      //               height: 10.0,
      //               padding: const EdgeInsets.all(0.0),
      //               decoration: new BoxDecoration(
      //                 border: new Border.all(width: 1.0, color: Colors.black45)
      //               ),
      //               child: new Text('Sun', style: new TextStyle(color: Colors.red,),),
      //             ),



      //           // const Text('He\'d have you all unravel at the'),
      //           // const Text('Heed not the rabble'),
      //           // const Text('Sound of screams but the'),
      //           // const Text('Who scream'),
      //           // const Text('Revolution is coming...'),
      //           // const Text('Revolution, they...'),
      //         ],
      //       ),
      //     ),
      //   ],
      // ),
    );
  }
}
