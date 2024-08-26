import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:project/components/background.dart';
import 'package:project/components/TextFromField.dart';
import 'package:project/components/buttons.dart';
import 'package:project/components/ShowError.dart';

class GetData extends StatefulWidget {
  const GetData({super.key});

  @override
  State<GetData> createState() => _GetDataState();
}

class _GetDataState extends State<GetData> {
  TextEditingController weight = TextEditingController();
  TextEditingController age = TextEditingController();

  GlobalKey<FormState> formState = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return background(
      child: Center(
        child: SingleChildScrollView(
          padding: const EdgeInsets.symmetric(horizontal: 30),
          child: Form(
            key: formState,
            child: Column(
              children: [
                Stack(
                  children: [
                    Text(
                      "Get Data",
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
                      "Get Data",
                      style: TextStyle(
                        fontSize: 45,
                        fontWeight: FontWeight.bold,
                        color: Color.fromRGBO(135, 215, 226, 1),
                      ),
                    ),
                  ],
                ),
                SizedBox(height: 20),
                TextFromField(
                  labelText: "Enter your weight:",
                  controller: weight,
                  validator: (val) {
                    if (val == null || val.isEmpty) {
                      return "Field is required";
                    }
                    return null;
                  },
                ),
                TextFromField(
                  labelText: "Enter your age:",
                  controller: age,
                  validator: (val) {
                    if (val == null || val.isEmpty) {
                      return "Field is required";
                    }
                    return null;
                  },
                ),
                SizedBox(height: 20),
                buttons(
                  title: 'Next',
                  onPressed: () async {
                    if (formState.currentState!.validate()) {
                      final userId = FirebaseAuth.instance.currentUser?.uid;

                      if (userId != null) {
                        await submitWeightAndAge(
                          context: context,
                          weightController: weight,
                          ageController: age,
                          userId: userId,
                        );
                        Navigator.of(context).pushReplacementNamed("profile");
                      } else {
                        ShowErrorDialog.show(
                          context: context,
                          errorMessage: 'User not logged in. Please sign in again.',
                        );
                      }
                    }
                  },
                  backgroundColor: Colors.transparent,
                  textColor: Color.fromRGBO(135, 215, 226, 1),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }

  Future<void> submitWeightAndAge({
    required BuildContext context,
    required TextEditingController weightController,
    required TextEditingController ageController,
    required String userId,
  }) async {
    final weight = weightController.text;
    final age = ageController.text;

    // Basic validation
    if (weight.isEmpty || age.isEmpty) {
      ShowErrorDialog.show(
        context: context,
        errorMessage: 'Please fill in both weight and age fields.',
      );
      return;
    }

    try {
      // Update Firestore document with the weight and age
      await FirebaseFirestore.instance
          .collection("users")
          .doc(userId)
          .set({
        "weight": double.tryParse(weight) ?? 0,  // Convert to double (if possible)
        "age": int.tryParse(age) ?? 0,           // Convert to int (if possible)
      }, SetOptions(merge: true)); // Use merge to avoid overwriting existing data

      // Successfully updated Firestore, navigate to profile page
      Navigator.of(context).pushReplacementNamed("ProfilePage");

    } on FirebaseException catch (e) {
      // Handle Firestore-specific errors
      print('FirebaseException: ${e.code} - ${e.message}');
      ShowErrorDialog.show(
        context: context,
        errorMessage: 'Firestore error: ${e.message}',
      );
    } catch (e) {
      // Handle any other errors
      print('Unexpected Error: $e');
      ShowErrorDialog.show(
        context: context,
        errorMessage: 'An unexpected error occurred: $e',
      );
    }
  }
}
