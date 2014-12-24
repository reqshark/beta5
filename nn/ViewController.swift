//
//created by Bent Cardan
//reqshark software. lifestyles of the rich and/or resourceful. authored 12/23/2014
//

import UIKit
var NN_SUB: CInt = 33
let s = nn_socket(AF_SP,NN_SUB)

let addr = ADDR
let r = getevents(s, NN_IN, 10)

var jobs = chan_init(0)
var done = chan_init(0)
var messages = chan_init(0)

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
  }

  override func didReceiveMemoryWarning() {
    super.didReceiveMemoryWarning()
    // Dispose of any resources that can be recreated.
  }

}