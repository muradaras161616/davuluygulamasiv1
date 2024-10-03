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
            child: Column(
              children: [
                Expanded(
                  child: Row(
                    children: [
                      TextButtonFonksiyonu('bip', Colors.blue, 1),
                      TextButtonFonksiyonu('bongo', Colors.cyanAccent, 1),
                    ],
                  ),
                ),
                Expanded(
                  child: Row(
                    children: [
                      TextButtonFonksiyonu('clap1', Colors.cyan, 1),
                      TextButtonFonksiyonu('clap2', Colors.cyanAccent, 1),
                    ],
                  ),
                ),
                Expanded(
                  child: Row(
                    children: [
                      TextButtonFonksiyonu('clap3', Colors.cyan, 1),
                      TextButtonFonksiyonu('crash', Colors.cyanAccent, 1),
                      TextButtonFonksiyonu('woo', Colors.cyanAccent, 1),
                    ],
                  ),
                ),
                Expanded(
                  child: Row(
                    children: [
                      TextButtonFonksiyonu("how", Colors.cyan, 1),
                      TextButtonFonksiyonu('oobah', Colors.cyanAccent, 1),
                      TextButtonFonksiyonu('ridebel', Colors.red, 1)
                    ],
                  ),
                ),
              ],
            ),
          )
          /*
          Expanded(
            child: Row(
              children: [
                Expanded(
                  child: TextButtonFonksiyonu(),
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
          */
        ],
      ),
    );
  }

  Expanded TextButtonFonksiyonu(String sesAdi, Color renk, int ras) {
    return Expanded(
      flex: ras,
      child: TextButton(
        onPressed: () {
          setState(() {
            bip(sesAdi);
          });
        },
        child: Container(
          decoration: BoxDecoration(
            borderRadius: BorderRadius.circular(4),
            color: renk,
          ),
          child: Center(
            child: Text(
              sesAdi,
              style: TextStyle(
                  color: Colors.white,
                  fontSize: 40,
                  fontWeight: FontWeight.bold,
                  fontStyle: FontStyle.italic),
            ),
          ),
        ),
      ),
    );
  }
}
