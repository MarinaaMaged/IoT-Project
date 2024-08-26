import 'package:flutter/material.dart';

class ProfileItem extends StatelessWidget {
  final String labelText;

  const ProfileItem({
    Key? key,
    required this.labelText,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 8.0),
      child: Text(
        labelText,
        style: TextStyle(
          fontSize: 20,
          fontWeight: FontWeight.bold,
          foreground: Paint()
            ..style = PaintingStyle.stroke
            ..strokeWidth = 2
            ..color = Colors.black,
          color: Color.fromRGBO(135, 215, 226, 1),
        ),
      ),
    );
  }
}
