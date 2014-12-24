//
//  ViewController.swift
//  nn
//
//  Created by Bent Cardan on 12/23/14.
//  Copyright (c) 2014 Bent Cardan. All rights reserved.
//

import UIKit
var NN_SUB: CInt = 33
let s = nn_socket(AF_SP,NN_SUB)

let addr = ADDR
let r = getevents(s, NN_IN, 10)

var jobs = chan_init(0)
var done = chan_init(0)
var messages = chan_init(0)

func greet(name: String, day: String) -> String {
  return "Hello \(name), today is \(day)."
}

var e = greet("BOB", "Tuesday")

class ViewController: UIViewController, UITextFieldDelegate {

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
    nn_connect (s, ADDR)
    nn_sleep (100)
    
    init_channels()
    
    //pthread_create(&th,NULL,worker,NULL)
    
    
    println(r)
    
  }

  override func didReceiveMemoryWarning() {
    super.didReceiveMemoryWarning()
    // Dispose of any resources that can be recreated.
  }

}

//<#UnsafePointer<pthread_attr_t>#>, <#CFunctionPointer<((UnsafeMutablePointer<Void>) -> UnsafeMutablePointer<Void>)>#>, <#UnsafeMutablePointer<Void>#>