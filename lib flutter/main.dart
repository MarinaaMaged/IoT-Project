import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'auth/login.dart';
import 'auth/signup.dart';
import 'auth/profile.dart';
import 'auth/GetData.dart';
import 'auth/hydrography.dart';


void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  void iniState() {
    FirebaseAuth.instance.authStateChanges().listen((User? user) {
      if (user == null) {
        print('=============================User is currently signed out!');
      } else {
        print('=============================User is signed in!');
      }
    });
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        debugShowCheckedModeBanner: false,
      home:FirebaseAuth.instance.currentUser == null? login() :Profile(),
      //home: login(),
    routes: {
      'login': (context) => login(),
      'profile': (context) => Profile(),
      'signup': (context) => signup(),
      'GetData': (context) => GetData(),






    },




      );
  }
}