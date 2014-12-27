//
//  ViewController.swift
//  nn
//
//  created by Bent Cardan
//  reqshark software. lifestyles of the rich and/or resourceful. authored 12/23/2014
//

import UIKit
import Foundation

var NN_SUB: CInt = 33
let s = nn_socket(AF_SP,NN_SUB)
let addr = ADDR

class ViewController: UIViewController, UITextFieldDelegate {
  
  //@IBOutlet weak var msgTextBox: UITextView!
  
  //func changeMsgText(){
    //msgTextBox.text = "changing"
  //}
  
  @IBOutlet weak var msgTextBox: UITextView!
  
  @IBOutlet weak var simpleTextField: UITextField!
  
  @IBOutlet weak var simpleLabel: UILabel!
  
  @IBAction func changeLabel(sender: AnyObject) {
    simpleLabel.text = "Hello, " + simpleTextField.text + "!"
    self.simpleTextField.resignFirstResponder()
  }
  
  func textFieldShouldReturn(textField: UITextField) -> Bool {
    simpleLabel.text = "Hello, " + simpleTextField.text + "!"
    textField.resignFirstResponder()
    return false
  }
  
  override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
    self.view.endEditing(true)
  }
  
  override func viewDidLoad() {
    super.viewDidLoad()
    nn_setsockopt (s, NN_SUB, NN_SUB_SUBSCRIBE, "", 0)
    nn_setsockopt (s, NN_TCP, NN_TCP_NODELAY, &optval, optlen)
    nn_connect (s, ADDR)
    nn_sleep (100)
   
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), {
      while(true){
        if(getevents(s, NN_IN, 10) == 1){
          var str: UnsafeMutablePointer = msgGet(s)
          dispatch_async(dispatch_get_main_queue(), {
            self.msgTextBox.text = String.fromCString(str)!
            msgFree(str)
          })
        }
      }
    })
    
  }
  
  override func didReceiveMemoryWarning() {
    super.didReceiveMemoryWarning()
    // Dispose of any resources that can be recreated.
  }
  
  override func viewDidAppear(animated: Bool) {
    println("something else interesting")
  }
  
}