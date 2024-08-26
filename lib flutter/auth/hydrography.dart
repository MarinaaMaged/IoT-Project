import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter/material.dart';
import 'package:project/components/background.dart';

class HydrographyScreen extends StatefulWidget {
  @override
  _HydrographyScreenState createState() => _HydrographyScreenState();
}

class _HydrographyScreenState extends State<HydrographyScreen> {
  final FirebaseFirestore _firestore = FirebaseFirestore.instance;

  int waterIntake = 0;
  int heartRate = 0;
  double temperature = 0.0;

  @override
  void initState() {
    super.initState();
    _fetchSensorData();
  }

  void _fetchSensorData() {
    // Listen to Firestore document changes
    _firestore.collection('sensorData').doc('latest').snapshots().listen((snapshot) {
      if (snapshot.exists) {
        final data = snapshot.data()!;
        final heartRate = data['heartRate'] ?? 0;
        final temperature = data['temperature']?.toDouble() ?? 0.0;
        final waterIntake = data['waterIntake'] ?? 0; // Fetch water intake from Firestore

        setState(() {
          this.heartRate = heartRate;
          this.temperature = temperature;
          this.waterIntake = waterIntake;
        });
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return background(
      child: Scaffold(
        backgroundColor: Colors.transparent,
        body: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              const SizedBox(height: 60),
              Center(
                child: Stack(
                  children: [
                    // Outline text
                    Text(
                      "Hydrography",
                      style: TextStyle(
                        fontSize: 45,
                        fontWeight: FontWeight.bold,
                        foreground: Paint()
                          ..style = PaintingStyle.stroke
                          ..strokeWidth = 3
                          ..color = Colors.black, // Outline color
                      ),
                    ),
                    // Fill text
                    Text(
                      "Hydrography",
                      style: TextStyle(
                        fontSize: 45,
                        fontWeight: FontWeight.bold,
                        color: Color.fromRGBO(135, 215, 226, 1), // Fill color
                      ),
                    ),
                  ],
                ),
              ),
              const SizedBox(height: 20),
              HydrographyItem(label: "Your Heart Rate: 70 bpm"),
              HydrographyItem(label: "Temperature : 28 °C"),
              HydrographyItem(label: "REMINDER!!"),
              HydrographyItem(label: "Don't forget to drink 250 ml/hr water"),
            ],
          ),
        ),
      ),
    );
  }
}

class HydrographyItem extends StatelessWidget {
  final String label;

  HydrographyItem({required this.label});

  @override
  Widget build(BuildContext context) {
    return Stack(
      children: [
        Text(
          label,
          style: TextStyle(
            fontSize: 22,
            fontWeight: FontWeight.bold,
            foreground: Paint()
              ..style = PaintingStyle.stroke
              ..strokeWidth = 3
              ..color = Colors.black, // Outline color
          ),
        ),
        Text(
          label,
          style: TextStyle(
            fontSize: 22,
            fontWeight: FontWeight.bold,
            color: Color.fromRGBO(135, 215, 226, 1), // Fill color
          ),
        ),
      ],
    );
  }
}
