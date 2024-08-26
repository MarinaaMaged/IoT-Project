import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:google_sign_in/google_sign_in.dart';
import 'package:project/auth/signup.dart';
import 'package:project/auth/profile.dart';
import 'package:project/components/background.dart';
import 'package:project/components/TextFromField.dart';
import 'package:project/components/buttons.dart';
import 'package:project/components/ShowError.dart';

class login extends StatefulWidget {
  const login({super.key});

  @override
  State<login> createState() => _loginState();
}

class _loginState extends State<login> {
  TextEditingController username =TextEditingController();
  TextEditingController password =TextEditingController();

  GlobalKey <FormState> formState = GlobalKey <FormState> ();

  Future signInWithGoogle() async {
    // Trigger the authentication flow
    final GoogleSignInAccount? googleUser = await GoogleSignIn().signIn();

    if (googleUser == null) {
      return;
    }

    // Obtain the auth details from the request
    final GoogleSignInAuthentication? googleAuth = await googleUser?.authentication;

    // Create a new credential
    final credential = GoogleAuthProvider.credential(
      accessToken: googleAuth?.accessToken,
      idToken: googleAuth?.idToken,
    );

    // Once signed in, return the UserCredential
  await FirebaseAuth.instance.signInWithCredential(credential);

  Navigator.of(context).pushNamedAndRemoveUntil("profile", (route) => false);
  }

  Future<void> handleEmailPasswordLogin() async {
    String errorMessage = '';
    if (formState.currentState!.validate()) {
      try {
        final credential = await FirebaseAuth.instance.signInWithEmailAndPassword(
          email: username.text,
          password: password.text,
        );
        Navigator.of(context).pushReplacementNamed("profile");
      } on FirebaseAuthException catch (e) {
        if (e.code == 'user-not-found') {
          errorMessage = 'No user found for that email.';
        } else if (e.code == 'wrong-password') {
          errorMessage = 'Wrong password provided for that user.';
        } else {
          errorMessage = 'An error occurred. Please try again.';
        }
        ShowErrorDialog.show(
          context: context,
          errorMessage: errorMessage,
        );
      } catch (e) {
        ShowErrorDialog.show(
          context: context,
          errorMessage: errorMessage,
        );
      }
    } else {
      print("Form is not valid");
    }
  }

  @override
  Widget build(BuildContext context) {
    return background(
      child: Center(
        child: SingleChildScrollView(
          padding: const EdgeInsets.symmetric(horizontal: 30),
          child: Form (
            key:formState,
            child: Column(
              children: [
                Container(height: 250),
//Alignment text to the left
//username text with stroke
                SizedBox(height: 20),
                TextFromField(
                  labelText: "Enter your username:",
                  controller: username,
                  validator: (val){
                     if (val == null || val.trim().isEmpty){
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
                    if (val == null || val.trim().isEmpty) {
                      return "Field is requird" ;
                    }
                    return null;
                  },
                ),
                SizedBox(height: 20),
 //Login button with stroke
                 buttons(
                  title: 'Login',
                     onPressed: handleEmailPasswordLogin,
                  backgroundColor: Colors.transparent,
                  textColor: Color.fromRGBO(135, 215, 226, 1),
                ),
                 SizedBox(height: 16),
//Social login section with stroke
                Stack(
                  children: [
//stroke text
                    Text(
                      'or Login with',
                      style: TextStyle(
                          fontSize: 15,
                          fontWeight: FontWeight.bold,
                          foreground: Paint()
                            ..style = PaintingStyle.stroke
                            ..strokeWidth = 3
                            ..color = Colors.black),
                    ),

//filled text
                    Text(
                      "or Login with",
                      style: TextStyle(
                        fontSize: 15,
                        fontWeight: FontWeight.bold,
                        color: Color.fromRGBO(135, 215, 226, 1),
                      ),
                    ),
                  ],
                ),

                   SizedBox(height: 16),
//Google Login button
                IconButton(
                  icon: Image.asset(
                    "lib/assets/google_icon.png",
                    width: 50,
                    height: 50,
                  ),
                  onPressed: () async {
                    await signInWithGoogle();
                  },
                ),
                SizedBox(height: 18),
//Sign up section with stroke
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Stack(
                      children: [
//stroke text
                        Text(
                          "Don't have an account?",
                          style: TextStyle(
                              fontSize: 15,
                              foreground: Paint()
                                ..style = PaintingStyle.stroke
                                ..strokeWidth = 3
                                ..color = Colors.black),
                        ),
//filled text
                        Text(
                          "Don't have an account?",
                          style: TextStyle(
                            fontSize: 15,
                            color: Color.fromRGBO(135, 215, 226, 1),
                          ),
                        ),
                      ],
                    ),
                    OutlinedButton(
                      onPressed: () {
                        Navigator.pushReplacementNamed(context, 'signup');
                      },
                      style: OutlinedButton.styleFrom(
                        side: BorderSide(
                          color:
                          Color.fromRGBO(248, 173, 79, 1), // Border color
                          width: 2,
                        ),
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(50),
                        ),
                        padding: EdgeInsets.symmetric(horizontal: 15),
                      ),
                      child: Stack(
                        children: [
//sign up text with stroke

                          Text(
                            " Sign up",
                            style: TextStyle(
                              fontSize: 20,
                              fontWeight: FontWeight.bold,
                              foreground: Paint()
                                ..style = PaintingStyle.stroke
                                ..strokeWidth = 3
                                ..color = Colors.black,
                            ),
                          ),

//filled text
                          Text(
                            "Sign up",
                            style: TextStyle(
                              fontSize: 20,
                              fontWeight: FontWeight.bold,
                              color: Color.fromRGBO(135, 215, 226, 1),
                            ),
                          ),
                        ],
                      ),
                    ),
                  ],
                ),
              ],
            ),
          ),
        ),
      ),
    );

  }
}


