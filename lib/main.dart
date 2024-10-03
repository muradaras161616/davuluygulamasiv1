import 'package:audioplayers/audioplayers.dart';
import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      home: DrumPage(),
    );
  }
}

class DrumPage extends StatefulWidget {
  const DrumPage({super.key});

  @override
  State<DrumPage> createState() => _DrumPageState();
}

class _DrumPageState extends State<DrumPage> {
  final oynatici = AudioPlayer(); // bir nesne oluşturduk ses oynatıcı

  void bip(String soundName) {
    var ses = AssetSource('$soundName.wav');
    oynatici.play(ses);
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Column(
        children: [
          Expanded(
            child: Row(
              children: [
                Expanded(
                  child: TextButton(
                    onPressed: () {
                      setState(() {
                        bip('bip');
                      });
                    },
                    child: Container(
                      color: Colors.deepPurple,
                    ),
                  ),
                ),
                Expanded(
                  child: TextButton(
                    onPressed: () {
                      var ses = AssetSource('bongo.wav');
                      oynatici.play(ses);
                    },
                    child: Container(
                      color: Colors.blue,
                    ),
                  ),
                ),
              ],
            ),
          ),
          Expanded(
            child: Row(
              children: [
                Expanded(
                  child: TextButton(
                    onPressed: () {
                      var ses = AssetSource('clap1.wav');
                      oynatici.play(ses);
                    },
                    child: Container(
                      color: Colors.green,
                    ),
                  ),
                ),
                Expanded(
                  child: TextButton(
                    onPressed: () {
                      var ses = AssetSource('clap2.wav');
                      oynatici.play(ses);
                    },
                    child: Container(
                      color: Colors.deepOrange,
                    ),
                  ),
                ),
              ],
            ),
          ),
          Expanded(
            child: Row(
              children: [
                Expanded(
                  child: TextButton(
                    onPressed: () {
                      var ses = AssetSource('clap3.wav');
                      oynatici.play(ses);
                    },
                    child: Container(
                      color: Colors.yellow,
                    ),
                  ),
                ),
                Expanded(
                  child: TextButton(
                    onPressed: () {
                      var ses = AssetSource('crash.wav');
                      oynatici.play(ses);
                    },
                    child: Container(
                      color: Colors.greenAccent,
                    ),
                  ),
                ),
              ],
            ),
          ),
          Expanded(
            child: Row(
              children: [
                Expanded(
                  child: TextButton(
                    onPressed: () {
                      var ses = AssetSource('how.wav');
                      oynatici.play(ses);
                    },
                    child: Container(
                      color: Colors.orangeAccent,
                    ),
                  ),
                ),
                Expanded(
                  child: TextButton(
                    onPressed: () {
                      var ses = AssetSource('oobah.wav');
                      oynatici.play(ses);
                    },
                    child: Container(
                      color: Colors.deepPurpleAccent,
                    ),
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
