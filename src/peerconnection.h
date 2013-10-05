#include <queue>
#include <v8.h>
#include <node.h>
#include <uv.h>

#undef STATIC_ASSERT  // Node defines this and so do we.

#include "nsAutoPtr.h"

using namespace node;
using namespace v8;

// forward decl
namespace sipcc { class PeerConnectionImpl; }

class PeerConnectionObserver;

class PeerConnection
: public ObjectWrap
{

public:

  enum AsyncEventType {
    CREATE_OFFER_SUCCESS,
    CREATE_OFFER_ERROR,
    CREATE_ANSWER_SUCCESS,
    CREATE_ANSWER_ERROR,
    SET_LOCAL_DESCRIPTION_SUCCESS,
    SET_LOCAL_DESCRIPTION_ERROR,
    SET_REMOTE_DESCRIPTION_SUCCESS,
    SET_REMOTE_DESCRIPTION_ERROR,
    ADD_ICE_CANDIDATE_SUCCESS,
    ADD_ICE_CANDIDATE_ERROR,
    NOTIFY_DATA_CHANNEL,
    NOTIFY_CONNECTION,
    NOTIFY_CLOSED_CONNECTION,
    STATE_CHANGE,
    ICE_CANDIDATE
  };

  PeerConnection();
  ~PeerConnection();

  //
  // Nodejs wrapping.
  //
  static void Init( Handle<Object> exports );
  static Persistent<Function> constructor;
  static Handle<Value> New( const Arguments& args );

  static Handle<Value> CreateOffer( const Arguments& args );
  static Handle<Value> CreateAnswer( const Arguments& args );
  static Handle<Value> SetLocalDescription( const Arguments& args );
  static Handle<Value> SetRemoteDescription( const Arguments& args );
  static Handle<Value> UpdateIce( const Arguments& args );
  static Handle<Value> AddIceCandidate( const Arguments& args );
  static Handle<Value> Close( const Arguments& args );

  static Handle<Value> GetLocalDescription( Local<String> property, const AccessorInfo& info );
  static Handle<Value> GetRemoteDescription( Local<String> property, const AccessorInfo& info );
  static Handle<Value> GetSignalingState( Local<String> property, const AccessorInfo& info );
  static void ReadOnly( Local<String> property, Local<Value> value, const AccessorInfo& info );

  void QueueEvent(AsyncEventType type, void* data);

private:
  // Private initializer.
  void Init_m();
  static void Run(uv_async_t* handle, int status);

  struct AsyncEvent {
    AsyncEventType type;
    void* data;
  };

  uv_mutex_t lock;
  uv_async_t async;
  std::queue<AsyncEvent> _events;

  nsRefPtr<sipcc::PeerConnectionImpl> _pc;
  nsRefPtr<PeerConnectionObserver> _pco;
};