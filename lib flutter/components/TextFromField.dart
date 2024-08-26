import 'package:flutter/material.dart';
import 'package:project/auth/login.dart';
import 'package:project/auth/signup.dart';

class TextFromField extends StatelessWidget {
  final String labelText;
   final TextEditingController controller;
   final bool obscureText;
   final String? Function(String?)? validator;
  
  const TextFromField ({
    Key? key,
    required this.labelText,
    required this.controller,
    this.obscureText = false,
    required this.validator,
}) :super(key: key);


  @override
  Widget build(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Stack(
          children: [
            Text(
              labelText,
              style: TextStyle(
                fontSize: 25,
                fontWeight: FontWeight.bold,
                foreground: Paint()
                  ..style = PaintingStyle.stroke
                  ..strokeWidth = 3
                  ..color = Colors.black,
              ),
            ),
            Text(
              labelText,
              style: TextStyle(
                fontSize: 25,
                fontWeight: FontWeight.bold,
                color: Color.fromRGBO(135, 215, 226, 1),
              ),
            ),
          ],
        ),
        SizedBox(height: 6),
        Align(
          alignment: Alignment.centerLeft,
          child: SizedBox(
            width: 350,
            child: TextFormField(
              controller: controller,
              obscureText: obscureText,
              validator: validator,
              decoration: InputDecoration(
                contentPadding: EdgeInsets.symmetric(horizontal: 40),
                filled: true,
                fillColor: Color.fromRGBO(255, 255, 255, 1),
                border: OutlineInputBorder(
                  borderRadius: BorderRadius.circular(50),
                  borderSide: BorderSide(
                    color: Color.fromRGBO(248, 173, 79, 1),
                  ),
                ),
                enabledBorder: OutlineInputBorder(
                  borderRadius: BorderRadius.circular(50),
                  borderSide: BorderSide(
                    color: Color.fromRGBO(248, 173, 79, 1),
                  ),
                ),
              ),
            ),
          ),
        ),
        SizedBox(height: 12),
      ],
    );

  }
}