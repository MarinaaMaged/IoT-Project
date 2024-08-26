import 'package:flutter/material.dart';
import 'dart:ui';
import 'package:project/auth/login.dart';
import 'package:project/auth/signup.dart';

class background extends StatelessWidget {
  final Widget child;
  final String backgroundImage;

  const background ({
    Key? key,
    required this.child,
    this.backgroundImage = "lib/assets/background.jpg"

  }) : super(key: key);


  @override
  Widget build(BuildContext context){
    return Scaffold(
      body: Stack(
        children: [
          Container(
            decoration: BoxDecoration(
              image: DecorationImage(
                image: AssetImage("lib/assets/background.jpg"),
                fit: BoxFit.cover,
              ),
            ),
          ),
// blur effect
          Positioned.fill(
            child: BackdropFilter(
              filter: ImageFilter.blur(sigmaX: 20, sigmaY: 20),
            ),
          ),
          child,
        ],
      ),
    );
  }
}