/* Copyright (c) 2018 The node-webrtc project authors. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE.md file in the root of the source tree. All contributing
 * project authors may be found in the AUTHORS file in the root of the source
 * tree.
 */

/*
 * This file defines conversion functions between WebRTC and v8 data types. We
 * try to match the W3C-specced Web IDL as closely as possible.
 */

#ifndef SRC_CONVERTERS_WEBRTC_H_
#define SRC_CONVERTERS_WEBRTC_H_

#include "nan.h"
#include "webrtc/api/peerconnectioninterface.h"

#include "src/converters.h"
#include "src/converters/v8.h"
#include "src/functional/validation.h"

namespace node_webrtc {

/*
 * dictionary RTCOAuthCredential {
 *   required DOMString macKey;
 *   required DOMString accessToken;
 * };
 */

// NOTE(mroberts): I've added this to match the Web IDL, but our build of
// WebRTC doesn't currently support this.
struct RTCOAuthCredential {
  RTCOAuthCredential(): macKey(""), accessToken("") {}
  RTCOAuthCredential(const std::string& macKey, const std::string& accessToken): macKey(macKey), accessToken(accessToken) {}
  const std::string macKey;
  const std::string accessToken;
};

template <>
struct Converter<v8::Local<v8::Value>, RTCOAuthCredential> {
  static Validation<RTCOAuthCredential> Convert(v8::Local<v8::Value> value);
};

/*
 * enum RTCIceCredentialType {
 *   "password",
 *   "oauth"
 * };
 */

enum RTCIceCredentialType {
  kPassword,
  kOAuth
};

template <>
struct Converter<v8::Local<v8::Value>, RTCIceCredentialType> {
  static Validation<RTCIceCredentialType> Convert(v8::Local<v8::Value> value);
};

/*
 * dictionary RTCIceServer {
 *   required (DOMString or sequence<DOMString>) urls;
 *            DOMString                          username;
 *            (DOMString or RTCOAuthCredential)  credential;
 *            RTCIceCredentialType               credentialType = "password";
 * };
 */

template <>
struct Converter<v8::Local<v8::Value>, webrtc::PeerConnectionInterface::IceServer> {
  static Validation<webrtc::PeerConnectionInterface::IceServer> Convert(v8::Local<v8::Value> value);
};

template <>
struct Converter<webrtc::PeerConnectionInterface::IceServer, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(webrtc::PeerConnectionInterface::IceServer value);
};

/*
 * enum RTCIceTransportPolicy {
 *   "relay",
 *   "all"
 * };
 */

template <>
struct Converter<v8::Local<v8::Value>, webrtc::PeerConnectionInterface::IceTransportsType> {
  static Validation<webrtc::PeerConnectionInterface::IceTransportsType> Convert(v8::Local<v8::Value> value);
};

template <>
struct Converter<webrtc::PeerConnectionInterface::IceTransportsType, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(webrtc::PeerConnectionInterface::IceTransportsType value);
};

/*
 * enum RTCBundlePolicy {
 *   "balanced",
 *   "max-compat",
 *   "max-bundle"
 * };
 */

template <>
struct Converter<v8::Local<v8::Value>, webrtc::PeerConnectionInterface::BundlePolicy> {
  static Validation<webrtc::PeerConnectionInterface::BundlePolicy> Convert(v8::Local<v8::Value> value);
};

template <>
struct Converter<webrtc::PeerConnectionInterface::BundlePolicy, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(webrtc::PeerConnectionInterface::BundlePolicy value);
};

/*
 * enum RTCRtcpMuxPolicy {
 *   // At risk due to lack of implementers' interest.
 *   "negotiate",
 *   "require"
 * };
 */

template <>
struct Converter<v8::Local<v8::Value>, webrtc::PeerConnectionInterface::RtcpMuxPolicy> {
  static Validation<webrtc::PeerConnectionInterface::RtcpMuxPolicy> Convert(v8::Local<v8::Value> value);
};

template <>
struct Converter<webrtc::PeerConnectionInterface::RtcpMuxPolicy, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(webrtc::PeerConnectionInterface::RtcpMuxPolicy value);
};

/*
 * dictionary RTCDtlsFingerprint {
 *   DOMString algorithm;
 *   DOMString value;
 * };
 */

// NOTE(mroberts): I've added this to match the Web IDL, but our build of
// WebRTC doesn't currently support this.
struct RTCDtlsFingerprint {
  RTCDtlsFingerprint(): algorithm(Maybe<std::string>::Nothing()), value(Maybe<std::string>::Nothing()) {}
  RTCDtlsFingerprint(const Maybe<std::string> algorithm, const Maybe<std::string> value): algorithm(algorithm), value(value) {}
  const Maybe<std::string> algorithm;
  const Maybe<std::string> value;
};

template <>
struct Converter<v8::Local<v8::Value>, RTCDtlsFingerprint> {
  static Validation<RTCDtlsFingerprint> Convert(v8::Local<v8::Value> value);
};

/*
 * dictionary UnsignedShortRange {
 *   unsigned short min;
 *   unsigned short max;
 * }
 */

struct UnsignedShortRange {
  UnsignedShortRange(): min(Maybe<uint16_t>::Nothing()), max(Maybe<uint16_t>::Nothing()) {}
  UnsignedShortRange(const Maybe<uint16_t> min, const Maybe<uint16_t> max): min(min), max(max) {}
  Maybe<uint16_t> min;
  Maybe<uint16_t> max;
};

template <>
struct Converter<v8::Local<v8::Value>, UnsignedShortRange> {
  static Validation<UnsignedShortRange> Convert(v8::Local<v8::Value> value);
};

template <>
struct Converter<UnsignedShortRange, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(UnsignedShortRange value);
};

/*
 * dictionary RTCConfiguration {
 *   sequence<RTCIceServer>   iceServers;
 *   RTCIceTransportPolicy    iceTransportPolicy = "all";
 *   RTCBundlePolicy          bundlePolicy = "balanced";
 *   RTCRtcpMuxPolicy         rtcpMuxPolicy = "require";
 *   DOMString                peerIdentity;
 *   sequence<RTCCertificate> certificates;
 *   [EnforceRange]
 *   octet                    iceCandidatePoolSize = 0;
 *   UnsignedShortRange       portRange;
 * };
 */

template <>
struct Converter<v8::Local<v8::Value>, webrtc::PeerConnectionInterface::RTCConfiguration> {
  static Validation<webrtc::PeerConnectionInterface::RTCConfiguration> Convert(v8::Local<v8::Value> value);
};

struct ExtendedRTCConfiguration {
  ExtendedRTCConfiguration(): configuration(webrtc::PeerConnectionInterface::RTCConfiguration()), portRange(UnsignedShortRange()) {}
  ExtendedRTCConfiguration(const webrtc::PeerConnectionInterface::RTCConfiguration configuration, const UnsignedShortRange portRange): configuration(configuration), portRange(portRange) {}
  webrtc::PeerConnectionInterface::RTCConfiguration configuration;
  UnsignedShortRange portRange;
};

template <>
struct Converter<v8::Local<v8::Value>, ExtendedRTCConfiguration> {
  static Validation<ExtendedRTCConfiguration> Convert(v8::Local<v8::Value> value);
};

template <>
struct Converter<ExtendedRTCConfiguration, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(ExtendedRTCConfiguration value);
};

/*
 * dictionary RTCOfferAnswerOptions {
 *   boolean voiceActivityDetection = true;
 * };
 */

/*
 * dictionary RTCOfferOptions : RTCOfferAnswerOptions {
 *   boolean iceRestart = false;
 * };
 *
 * partial dictionary RTCOfferOptions {
 *   boolean offerToReceiveAudio;
 *   boolean offerToReceiveVideo;
 * };
 */

// NOTE(mroberts): I'm just doing something akin to a newtype here.
struct RTCOfferOptions {
  RTCOfferOptions(): options(webrtc::PeerConnectionInterface::RTCOfferAnswerOptions()) {}
  explicit RTCOfferOptions(const webrtc::PeerConnectionInterface::RTCOfferAnswerOptions options): options(options) {}
  const webrtc::PeerConnectionInterface::RTCOfferAnswerOptions options;
};

template <>
struct Converter<v8::Local<v8::Value>, RTCOfferOptions> {
  static Validation<RTCOfferOptions> Convert(v8::Local<v8::Value> value);
};

/*
 * dictionary RTCAnswerOptions : RTCOfferAnswerOptions {
 * };
 */

// NOTE(mroberts): I'm just doing something akin to a newtype here.
struct RTCAnswerOptions {
  RTCAnswerOptions(): options(webrtc::PeerConnectionInterface::RTCOfferAnswerOptions()) {}
  explicit RTCAnswerOptions(const webrtc::PeerConnectionInterface::RTCOfferAnswerOptions options): options(options) {}
  const webrtc::PeerConnectionInterface::RTCOfferAnswerOptions options;
};

template <>
struct Converter<v8::Local<v8::Value>, RTCAnswerOptions> {
  static Validation<RTCAnswerOptions> Convert(v8::Local<v8::Value> value);
};

/*
 * enum RTCSdpType {
 *   "offer",
 *   "pranswer",
 *   "answer",
 *   "rollback"
 * };
 */

enum RTCSdpType {
  kOffer,
  kPrAnswer,
  kAnswer,
  kRollback
};

template <>
struct Converter<v8::Local<v8::Value>, RTCSdpType> {
  static Validation<RTCSdpType> Convert(v8::Local<v8::Value> value);
};

/*
 * dictionary RTCSessionDescriptionInit {
 *   required RTCSdpType type;
 *            DOMString  sdp = "";
 * };
 */

template <>
struct Converter<v8::Local<v8::Value>, webrtc::SessionDescriptionInterface*> {
  static Validation<webrtc::SessionDescriptionInterface*> Convert(v8::Local<v8::Value> value);
};

template <>
struct Converter<const webrtc::SessionDescriptionInterface*, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(const webrtc::SessionDescriptionInterface* value);
};

/*
 * dictionary RTCIceCandidateInit {
 *     DOMString       candidate = "";
 *     DOMString?      sdpMid = null;
 *     unsigned short? sdpMLineIndex = null;
 *     DOMString       usernameFragment;
 * };
 */

template <>
struct Converter<v8::Local<v8::Value>, webrtc::IceCandidateInterface*> {
  static Validation<webrtc::IceCandidateInterface*> Convert(v8::Local<v8::Value> value);
};

template <>
struct Converter<const webrtc::IceCandidateInterface*, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(const webrtc::IceCandidateInterface* value);
};

/*
 * enum RTCPriorityType {
 *   "very-low",
 *   "low",
 *   "medium",
 *   "high"
 * };
 */

enum RTCPriorityType {
  kVeryLow,
  kLow,
  kMedium,
  kHigh
};

template <>
struct Converter<v8::Local<v8::Value>, RTCPriorityType> {
  static Validation<RTCPriorityType> Convert(v8::Local<v8::Value> value);
};

/*
 * dictionary RTCDataChannelInit {
 *   boolean         ordered = true;
 *   unsigned short  maxPacketLifeTime;
 *   unsigned short  maxRetransmits;
 *   USVString       protocol = "";
 *   boolean         negotiated = false;
 *   [EnforceRange]
 *   unsigned short  id;
 *   RTCPriorityType priority = "low";
 * };
 */

template <>
struct Converter<v8::Local<v8::Value>, webrtc::DataChannelInit> {
  static Validation<webrtc::DataChannelInit> Convert(v8::Local<v8::Value> value);
};

/*
 * enum RTCSignalingState {
 *   "stable",
 *   "have-local-offer",
 *   "have-remote-offer",
 *   "have-local-pranswer",
 *   "have-remote-pranswer",
 *   "closed"
 * }
 */

template <>
struct Converter<webrtc::PeerConnectionInterface::SignalingState, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(webrtc::PeerConnectionInterface::SignalingState value);
};

/*
 * enum RTCIceGatheringState {
 *   "new",
 *   "gathering",
 *   "complete"
 * }
 */

template <>
struct Converter<webrtc::PeerConnectionInterface::IceGatheringState, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(webrtc::PeerConnectionInterface::IceGatheringState value);
};

/*
 * enum RTCIceConnectionState {
 *   "new",
 *   "checking",
 *   "connected",
 *   "completed",
 *   "disconnected",
 *   "failed",
 *   "closed"
 * }
 */

template <>
struct Converter<webrtc::PeerConnectionInterface::IceConnectionState, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(webrtc::PeerConnectionInterface::IceConnectionState value);
};

/*
 * enum RTCDataChannelState {
 *   "connecting",
 *   "open",
 *   "closing",
 *   "closed"
 * }
 */

template <>
struct Converter<webrtc::DataChannelInterface::DataState, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(webrtc::DataChannelInterface::DataState value);
};

/*
 * enum BinaryType {
 *   "blob",
 *   "arraybuffer"
 * }
 */

enum BinaryType {
  kBlob,
  kArrayBuffer,
};

template <>
struct Converter<BinaryType, v8::Local<v8::Value>> {
  static Validation<v8::Local<v8::Value>> Convert(BinaryType value);
};

template <>
struct Converter<v8::Local<v8::Value>, BinaryType> {
  static Validation<BinaryType> Convert(v8::Local<v8::Value> value);
};

}  // namespace node_webrtc

#endif  // SRC_CONVERTERS_WEBRTC_H_
