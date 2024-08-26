import 'package:flutter/material.dart';

class ShowErrorDialog {
  static void show({
    required BuildContext context,
    required String errorMessage,

  }) {
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          title: Text('Error'),
          content: Text(errorMessage),
          actions: <Widget> [
            TextButton(
              child: Text('OK'),
              onPressed: () {
                Navigator.of(context).pop();  // Close the dialog
              },
            ),
          ],
        );
      },
    );
  }
}
