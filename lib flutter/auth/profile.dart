import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:google_sign_in/google_sign_in.dart';
import 'package:project/components/background.dart';
import 'package:project/components/profileItems.dart';
import 'package:project/auth/hydrography.dart';

class Profile extends StatefulWidget {
  const Profile({Key? key}) : super(key: key);

  @override
  State<Profile> createState() => _ProfileState();
}

class _ProfileState extends State<Profile> {
  int _selectedIndex = 0; // Manage selected tab index
  String name = "";
  String username = "";
  int age = 0;
  double weight = 0.0;

  Future<void> _fetchUserData() async {
    try {
      User? user = FirebaseAuth.instance.currentUser;

      if (user == null) {
        user = (await FirebaseAuth.instance.signInAnonymously()).user;
      }

      if (user != null) {
        DocumentSnapshot userData = await FirebaseFirestore.instance
            .collection('users')
            .doc(user.uid)
            .get();

        if (userData.exists) {
          setState(() {
            name = userData['name'] ?? "Unknown";
            username = userData['username'] ?? "Unknown";
            age = userData['age'] ?? 0;
            weight = userData['weight']?.toDouble() ?? 0.0;
          });
        }
      }
    } catch (e) {
      print("Error fetching user data: $e");
    }
  }

  @override
  void initState() {
    super.initState();
    _fetchUserData();
  }

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    // Define the screens
    List<Widget> _screens = [
      ProfileScreen(
        name: name,
        username: username,
        age: age,
        weight: weight,

      ),
      HydrographyScreen(),
      Center(child: Text("report")),

    ];

    return Scaffold(
      body: _screens[_selectedIndex],
      bottomNavigationBar: BottomNavigationBar(
        items: const [
          BottomNavigationBarItem(
            icon: Icon(Icons.account_circle_rounded),
            label: 'Profile',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.water_drop),
            label: 'Hydrography',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.bar_chart),
            label: 'Report',
          ),

        ],
        currentIndex: _selectedIndex,
        onTap: _onItemTapped,
      ),
    );
  }
}

class ProfileScreen extends StatelessWidget {
  final String name;
  final String username;
  final int age;
  final double weight;

  const ProfileScreen({
    required this.name,
    required this.username,
    required this.age,
    required this.weight,

  });

  @override
  Widget build(BuildContext context) {
    return background(
      child: Scaffold(
        backgroundColor: Colors.transparent,
        body: Column(
          children: [
            Container(
              alignment: Alignment.topRight,
              padding: const EdgeInsets.all(16.0),
              child: IconButton(
                icon: const Icon(Icons.exit_to_app, color: Colors.red),
                onPressed: () async {
                  try {
                    await FirebaseAuth.instance.signOut();
                    GoogleSignIn googleSignIn = GoogleSignIn();
                    if (await googleSignIn.isSignedIn()) {
                      await googleSignIn.disconnect();
                    }
                    Navigator.of(context).pushNamedAndRemoveUntil(
                        "login", (route) => false);
                  } catch (e) {
                    print("Error signing out: $e");
                  }
                },
              ),
            ),
            Expanded(
              child: Padding(
                padding: const EdgeInsets.all(16.0),
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Center(
                      child: Stack(
                        children: [
                          Text(
                            "Profile",
                            style: TextStyle(
                              fontSize: 45,
                              fontWeight: FontWeight.bold,
                              foreground: Paint()
                                ..style = PaintingStyle.stroke
                                ..strokeWidth = 3
                                ..color = Colors.black,
                            ),
                          ),
                          Text(
                            "Profile",
                            style: TextStyle(
                              fontSize: 45,
                              fontWeight: FontWeight.bold,
                              color: Color.fromRGBO(135, 215, 226, 1),
                            ),
                          ),
                        ],
                      ),
                    ),
                    SizedBox(height: 30),
                    Stack(
                      children: [
                        Text(
                          "Name: $name",
                          style: TextStyle(
                            fontSize: 25,
                            foreground: Paint()
                              ..style = PaintingStyle.stroke
                              ..strokeWidth = 2
                              ..color = Colors.black,
                          ),
                        ),
                        Text(
                          "Name: $name",
                          style: TextStyle(
                            fontSize: 25,
                            color: Color.fromRGBO(135, 215, 226, 1),
                          ),
                        ),
                      ],
                    ),
                    SizedBox(height: 15),
                    Stack(
                      children: [
                        Text(
                          "Username: $username",
                          style: TextStyle(
                            fontSize: 20,
                            foreground: Paint()
                              ..style = PaintingStyle.stroke
                              ..strokeWidth = 2
                              ..color = Colors.black,
                          ),
                        ),
                        Text(
                          "Username: $username",
                          style: TextStyle(
                            fontSize: 20,
                            color: Color.fromRGBO(135, 215, 226, 1),
                          ),
                        ),
                      ],
                    ),
                    SizedBox(height: 15),
                    Stack(
                      children: [
                        Text(
                          "Age: $age",
                          style: TextStyle(
                            fontSize: 20,
                            foreground: Paint()
                              ..style = PaintingStyle.stroke
                              ..strokeWidth = 2
                              ..color = Colors.black,
                          ),
                        ),
                        Text(
                          "Age: $age",
                          style: TextStyle(
                            fontSize: 20,
                            color: Color.fromRGBO(135, 215, 226, 1),
                          ),
                        ),
                      ],
                    ),
                    SizedBox(height: 15),
                    Stack(
                      children: [
                        Text(
                          "Weight: $weight kg",
                          style: TextStyle(
                            fontSize: 20,
                            foreground: Paint()
                              ..style = PaintingStyle.stroke
                              ..strokeWidth = 2
                              ..color = Colors.black,
                          ),
                        ),
                        Text(
                          "Weight: $weight kg",
                          style: TextStyle(
                            fontSize: 20,
                            color: Color.fromRGBO(135, 215, 226, 1),
                          ),
                        ),
                      ],
                    ),
                    SizedBox(height: 15),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
