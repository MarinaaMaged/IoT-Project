import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:project/components/background.dart';
import 'package:project/components/TextFromField.dart';
import 'package:project/auth/GetData.dart';
import 'package:project/components/buttons.dart';
import 'package:project/components/ShowError.dart';


class signup extends StatefulWidget {
  const signup({Key? key}) : super(key: key);

  @override
  State<signup> createState() => _signupState();
}

class _signupState extends State <signup> {
  final TextEditingController name = TextEditingController();
  final TextEditingController username = TextEditingController();
  final TextEditingController password = TextEditingController();
  final TextEditingController confirmPass = TextEditingController();

  GlobalKey <FormState> formState = GlobalKey <FormState> ();

  @override
  Widget build(BuildContext context) {
   return background(
         child:Center(
           child: SingleChildScrollView(
             padding: const EdgeInsets.symmetric(horizontal: 30),
             child : Form(
               key:formState,
             child: Column(
               children: [
                 Stack(
                   children: [
                     Text(
                       "Create new account",
                       style: TextStyle(
                         fontSize: 35,
                         fontWeight: FontWeight.bold,
                         foreground: Paint()
                           ..style = PaintingStyle.stroke
                           ..strokeWidth = 3
                           ..color = Colors.black,
                       ),
                     ),
                     Text(
                       "Create new account",
                       style: TextStyle(
                         fontSize: 35,
                         fontWeight: FontWeight.bold,
                         color: Color.fromRGBO(135, 215, 226, 1),
                       ),
                     ),
                   ],
                 ),
                 SizedBox(height: 20),
                 TextFromField(
                   labelText: "Enter your name:",
                   controller: name,
                   validator: (val){
                     if (val == null || val.isEmpty) {
                       return "Field is requird" ;
                     }
                     return null;
                   },
                 ),
                 TextFromField(
                   labelText: "Enter your username:",
                   controller: username,
                   validator: (val){
                     if (val == null || val.isEmpty) {
                       return "Field is requird" ;
                     }
                     return null;
                   },
                 ),
                 TextFromField(
                   labelText: "Enter your password:",
                   controller: password,
                   obscureText: true,
                   validator: (val){
                     if (val == null || val.isEmpty) {
                       return "Field is requird" ;
                     }
                     return null;
                   },
                 ),
                 TextFromField(
                   labelText: "Confirm your password:",
                   controller: confirmPass,
                   obscureText: true,
                   validator: (val){
                      if (val == null || val.isEmpty) {
                       return "Field is requird" ;
                     }
                     if (val != password.text) {
                       return "Passwords do not match";
                     }
                     return null;
                   },
                 ),
                 SizedBox(height: 20),
                 buttons(
                   title: 'Sign Up',
                   onPressed: () async {
                     if (formState.currentState!.validate()) {
                       try {
                         final credential = await FirebaseAuth.instance.createUserWithEmailAndPassword(
                           email: username.text,
                           password: password.text,
                         );
                         // Store user data in Firestore
                         FirebaseFirestore.instance.collection("users").doc(credential.user!.uid).set({
                           "name": name.text,
                           "username": username.text,
                           "email": username.text,
                           "uid": credential.user!.uid,
                         });
                         Navigator.of(context).pushReplacementNamed("GetData");
                       } on FirebaseAuthException catch (e) {
                         print('Firebase error code: ${e.code}');
                         String errorMessage;
                         if (e.code == 'weak-password') {
                           errorMessage = 'weak-password';
                         } else if (e.code == 'email-already-in-use') {
                           errorMessage = 'email-already-in-use';
                         } else {
                           errorMessage = 'An unexpected error occurred. Please try again.';
                         }
                         ShowErrorDialog.show(
                           context: context,
                           errorMessage: errorMessage,
                         );
                       } catch (e) {
                         print(e);
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
  }

