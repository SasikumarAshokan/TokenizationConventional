import Foundation
import UIKit
import D1
/// D1 SDK iOS plugin entry point.
@objc(TokenizationConventional) class TokenizationConventional : CDVPlugin {
    
    private var d1Task: D1Task?
    
    @objc(firstMethood:)
    func firstMethood(command: CDVInvokedUrlCommand){
		NSLog("Sasi=====>", "Came To Cordova")
        let pluginResult = CDVPluginResult(status: CDVCommandStatus_OK, messageAs: "Retrun From Cordova");
        self.commandDelegate!.send(pluginResult, callbackId: command.callbackId)
    }
    
    @objc(configure:)
    /// Configures the D1 SDK.
    /// - Parameter command: Cordova command.
    func configure(command: CDVInvokedUrlCommand) {
        let serviceUrl = command.arguments[0] as! String
        let issuerId = command.arguments[1] as! String
        let exponent = command.arguments[2] as! NSArray
        let modulus = command.arguments[3] as! NSArray
        let digitalCardUrl = command.arguments[4] as! String
        let consumerId = command.arguments[5] as! String
        
        var exponentData = Data()
        for exponentByte in exponent {
            exponentData.append(exponentByte as! UInt8)
        }
        
        var modulusData = Data()
        for modulusByte in modulus {
            modulusData.append(modulusByte as! UInt8)
        }
        

        self.configure(serviceUrl, issuerId, exponentData, modulusData, digitalCardUrl, consumerId, self.commandDelegate, command.callbackId)
    }
    
    @objc(login:)
    /// Logs in in to D1.
    /// - Parameter command: Cordova command.
    func login(command: CDVInvokedUrlCommand) {
        let issuerToken = command.arguments[0] as! String
        self.login(issuerToken, self.commandDelegate, command.callbackId)
    }
    
    /// Configures the D1 SDK.
    /// - Parameters:
    ///   - d1ServiceURLString: Service URL.
    ///   - issuerID: Issuer ID.
    ///   - publicKeyExponent: Public Key Exponent.
    ///   - publicKeyModulus: Public Key Modulus.
    ///   - digitalCardURLString: Digital Cardl URL.
    ///   - consumerID: Consumer ID.
    ///   - callback: Callback.
    func configure(_ d1ServiceURLString:String, _ issuerID:String, _ publicKeyExponent: Data, _ publicKeyModulus: Data, _ digitalCardURLString:String, _ consumerID: String, _ callback: CDVCommandDelegate, _ callbackId: String) -> Void {
        
        var comp = D1Task.Components()
        comp.d1ServiceURLString = d1ServiceURLString
        comp.issuerID = issuerID
        comp.d1ServiceRSAExponent = publicKeyExponent
        comp.d1ServiceRSAModulus = publicKeyModulus
        comp.digitalCardURLString = digitalCardURLString
        d1Task = comp.task()
        
        let coreConfig = ConfigParams.coreConfig(consumerID: consumerID)
        // required for Card Processing & OEM Pay
        let cardConfig = ConfigParams.cardConfig()
        
        getD1Task().configure([coreConfig, cardConfig]) { errors in
            if let jsonError = self.createErrorJson(errors) {
                let pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: jsonError);
                callback.send(pluginResult, callbackId: callbackId);
                return
            }
            
            let pluginResult = CDVPluginResult(status: CDVCommandStatus_OK);
            callback.send(pluginResult, callbackId: callbackId);
        }
    }
    
    /// Logs is to D1 SDK.
    /// - Parameters:
    ///   - issueToken: Issuer token.
    ///   - callback: Callback.
    private func login(_ issueToken: String, _ callback: CDVCommandDelegate, _ callbackId: String) -> Void {
        if var issueTokenData: Data = issueToken.data(using: .utf8) {
            self.getD1Task().login(&issueTokenData) { error in
                if let jsonError = self.createErrorJson(error) {
                    let pluginResult = CDVPluginResult(status: CDVCommandStatus_ERROR, messageAs: "");
                    callback.send(pluginResult, callbackId: callbackId);
                    return
                }
                
                let pluginResult = CDVPluginResult(status: CDVCommandStatus_OK);
                callback.send(pluginResult, callbackId: callbackId);
            }
        }
    }
    
    /// Creates a JSON response string from D1Error object.
    /// - Parameter error: D1Error object.
    /// - Returns: JSON string or nil if D1Error object is nil.
    private func createErrorJson(_ error: D1Error?) -> String? {
        /*if let error = error {
            do {
                let jsonEncoder = JSONEncoder()
                let jsonData = try jsonEncoder.encode(RD1Error(code: error.code.rawValue, message: error.localizedDescription))
                let jsonRD1Error = String(data: jsonData, encoding: String.Encoding.utf8)
                
                return jsonRD1Error
            } catch {
                // this should not happen
                fatalError()
            }
        }*/
        
        return nil
    }
    
    /// Creates a JSON response string from D1Error array.
    /// - Parameter error: D1Error object.
    /// - Returns: JSON string or nil if D1Error array is nil.
    private func createErrorJson(_ error: [D1Error]?) -> String? {
        /*if let error = error {
            do {
                var dic = [RD1Error]()
                for i in 0..<error.count {
                    dic.append(RD1Error(code: error[i].code.rawValue, message: error[i].localizedDescription))
                }
                let jsonEncoder = JSONEncoder()
                let jsonData = try jsonEncoder.encode(dic)
                let json = String(data: jsonData, encoding: String.Encoding.utf8)
                
                return json
            } catch {
                // should not happen
                fatalError()
            }
        }*/
        
        return nil
    }
    
    /// Retrieves the D1Task. Need to configure the D1 SDK first.
    /// - Returns: D1Task object. fatalError is thrown if called without D1 SDK configuration.
    private func getD1Task() -> D1Task {
        if let d1Task = d1Task {
            return d1Task
        } else {
            fatalError("Need to configure D1 SDK first.")
        }
    }
}
