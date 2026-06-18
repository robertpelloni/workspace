(function polyfill() {
  const relList = document.createElement("link").relList;
  if (relList && relList.supports && relList.supports("modulepreload")) return;
  for (const link of document.querySelectorAll('link[rel="modulepreload"]')) processPreload(link);
  new MutationObserver((mutations) => {
    for (const mutation of mutations) {
      if (mutation.type !== "childList") continue;
      for (const node of mutation.addedNodes) if (node.tagName === "LINK" && node.rel === "modulepreload") processPreload(node);
    }
  }).observe(document, {
    childList: true,
    subtree: true
  });
  function getFetchOpts(link) {
    const fetchOpts = {};
    if (link.integrity) fetchOpts.integrity = link.integrity;
    if (link.referrerPolicy) fetchOpts.referrerPolicy = link.referrerPolicy;
    if (link.crossOrigin === "use-credentials") fetchOpts.credentials = "include";
    else if (link.crossOrigin === "anonymous") fetchOpts.credentials = "omit";
    else fetchOpts.credentials = "same-origin";
    return fetchOpts;
  }
  function processPreload(link) {
    if (link.ep) return;
    link.ep = true;
    const fetchOpts = getFetchOpts(link);
    fetch(link.href, fetchOpts);
  }
})();
var jsxRuntime = { exports: {} };
var reactJsxRuntime_production_min = {};
var react = { exports: {} };
var react_production_min = {};
/**
 * @license React
 * react.production.min.js
 *
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
var hasRequiredReact_production_min;
function requireReact_production_min() {
  if (hasRequiredReact_production_min) return react_production_min;
  hasRequiredReact_production_min = 1;
  var l = Symbol.for("react.element"), n = Symbol.for("react.portal"), p = Symbol.for("react.fragment"), q2 = Symbol.for("react.strict_mode"), r = Symbol.for("react.profiler"), t = Symbol.for("react.provider"), u3 = Symbol.for("react.context"), v2 = Symbol.for("react.forward_ref"), w2 = Symbol.for("react.suspense"), x2 = Symbol.for("react.memo"), y2 = Symbol.for("react.lazy"), z2 = Symbol.iterator;
  function A(a) {
    if (null === a || "object" !== typeof a) return null;
    a = z2 && a[z2] || a["@@iterator"];
    return "function" === typeof a ? a : null;
  }
  var B2 = { isMounted: function() {
    return false;
  }, enqueueForceUpdate: function() {
  }, enqueueReplaceState: function() {
  }, enqueueSetState: function() {
  } }, C2 = Object.assign, D2 = {};
  function E2(a, b2, e) {
    this.props = a;
    this.context = b2;
    this.refs = D2;
    this.updater = e || B2;
  }
  E2.prototype.isReactComponent = {};
  E2.prototype.setState = function(a, b2) {
    if ("object" !== typeof a && "function" !== typeof a && null != a) throw Error("setState(...): takes an object of state variables to update or a function which returns an object of state variables.");
    this.updater.enqueueSetState(this, a, b2, "setState");
  };
  E2.prototype.forceUpdate = function(a) {
    this.updater.enqueueForceUpdate(this, a, "forceUpdate");
  };
  function F2() {
  }
  F2.prototype = E2.prototype;
  function G2(a, b2, e) {
    this.props = a;
    this.context = b2;
    this.refs = D2;
    this.updater = e || B2;
  }
  var H = G2.prototype = new F2();
  H.constructor = G2;
  C2(H, E2.prototype);
  H.isPureReactComponent = true;
  var I2 = Array.isArray, J2 = Object.prototype.hasOwnProperty, K2 = { current: null }, L2 = { key: true, ref: true, __self: true, __source: true };
  function M2(a, b2, e) {
    var d2, c = {}, k2 = null, h = null;
    if (null != b2) for (d2 in void 0 !== b2.ref && (h = b2.ref), void 0 !== b2.key && (k2 = "" + b2.key), b2) J2.call(b2, d2) && !L2.hasOwnProperty(d2) && (c[d2] = b2[d2]);
    var g = arguments.length - 2;
    if (1 === g) c.children = e;
    else if (1 < g) {
      for (var f = Array(g), m2 = 0; m2 < g; m2++) f[m2] = arguments[m2 + 2];
      c.children = f;
    }
    if (a && a.defaultProps) for (d2 in g = a.defaultProps, g) void 0 === c[d2] && (c[d2] = g[d2]);
    return { $$typeof: l, type: a, key: k2, ref: h, props: c, _owner: K2.current };
  }
  function N2(a, b2) {
    return { $$typeof: l, type: a.type, key: b2, ref: a.ref, props: a.props, _owner: a._owner };
  }
  function O(a) {
    return "object" === typeof a && null !== a && a.$$typeof === l;
  }
  function escape(a) {
    var b2 = { "=": "=0", ":": "=2" };
    return "$" + a.replace(/[=:]/g, function(a2) {
      return b2[a2];
    });
  }
  var P2 = /\/+/g;
  function Q2(a, b2) {
    return "object" === typeof a && null !== a && null != a.key ? escape("" + a.key) : b2.toString(36);
  }
  function R(a, b2, e, d2, c) {
    var k2 = typeof a;
    if ("undefined" === k2 || "boolean" === k2) a = null;
    var h = false;
    if (null === a) h = true;
    else switch (k2) {
      case "string":
      case "number":
        h = true;
        break;
      case "object":
        switch (a.$$typeof) {
          case l:
          case n:
            h = true;
        }
    }
    if (h) return h = a, c = c(h), a = "" === d2 ? "." + Q2(h, 0) : d2, I2(c) ? (e = "", null != a && (e = a.replace(P2, "$&/") + "/"), R(c, b2, e, "", function(a2) {
      return a2;
    })) : null != c && (O(c) && (c = N2(c, e + (!c.key || h && h.key === c.key ? "" : ("" + c.key).replace(P2, "$&/") + "/") + a)), b2.push(c)), 1;
    h = 0;
    d2 = "" === d2 ? "." : d2 + ":";
    if (I2(a)) for (var g = 0; g < a.length; g++) {
      k2 = a[g];
      var f = d2 + Q2(k2, g);
      h += R(k2, b2, e, f, c);
    }
    else if (f = A(a), "function" === typeof f) for (a = f.call(a), g = 0; !(k2 = a.next()).done; ) k2 = k2.value, f = d2 + Q2(k2, g++), h += R(k2, b2, e, f, c);
    else if ("object" === k2) throw b2 = String(a), Error("Objects are not valid as a React child (found: " + ("[object Object]" === b2 ? "object with keys {" + Object.keys(a).join(", ") + "}" : b2) + "). If you meant to render a collection of children, use an array instead.");
    return h;
  }
  function S2(a, b2, e) {
    if (null == a) return a;
    var d2 = [], c = 0;
    R(a, d2, "", "", function(a2) {
      return b2.call(e, a2, c++);
    });
    return d2;
  }
  function T2(a) {
    if (-1 === a._status) {
      var b2 = a._result;
      b2 = b2();
      b2.then(function(b3) {
        if (0 === a._status || -1 === a._status) a._status = 1, a._result = b3;
      }, function(b3) {
        if (0 === a._status || -1 === a._status) a._status = 2, a._result = b3;
      });
      -1 === a._status && (a._status = 0, a._result = b2);
    }
    if (1 === a._status) return a._result.default;
    throw a._result;
  }
  var U2 = { current: null }, V2 = { transition: null }, W2 = { ReactCurrentDispatcher: U2, ReactCurrentBatchConfig: V2, ReactCurrentOwner: K2 };
  function X2() {
    throw Error("act(...) is not supported in production builds of React.");
  }
  react_production_min.Children = { map: S2, forEach: function(a, b2, e) {
    S2(a, function() {
      b2.apply(this, arguments);
    }, e);
  }, count: function(a) {
    var b2 = 0;
    S2(a, function() {
      b2++;
    });
    return b2;
  }, toArray: function(a) {
    return S2(a, function(a2) {
      return a2;
    }) || [];
  }, only: function(a) {
    if (!O(a)) throw Error("React.Children.only expected to receive a single React element child.");
    return a;
  } };
  react_production_min.Component = E2;
  react_production_min.Fragment = p;
  react_production_min.Profiler = r;
  react_production_min.PureComponent = G2;
  react_production_min.StrictMode = q2;
  react_production_min.Suspense = w2;
  react_production_min.__SECRET_INTERNALS_DO_NOT_USE_OR_YOU_WILL_BE_FIRED = W2;
  react_production_min.act = X2;
  react_production_min.cloneElement = function(a, b2, e) {
    if (null === a || void 0 === a) throw Error("React.cloneElement(...): The argument must be a React element, but you passed " + a + ".");
    var d2 = C2({}, a.props), c = a.key, k2 = a.ref, h = a._owner;
    if (null != b2) {
      void 0 !== b2.ref && (k2 = b2.ref, h = K2.current);
      void 0 !== b2.key && (c = "" + b2.key);
      if (a.type && a.type.defaultProps) var g = a.type.defaultProps;
      for (f in b2) J2.call(b2, f) && !L2.hasOwnProperty(f) && (d2[f] = void 0 === b2[f] && void 0 !== g ? g[f] : b2[f]);
    }
    var f = arguments.length - 2;
    if (1 === f) d2.children = e;
    else if (1 < f) {
      g = Array(f);
      for (var m2 = 0; m2 < f; m2++) g[m2] = arguments[m2 + 2];
      d2.children = g;
    }
    return { $$typeof: l, type: a.type, key: c, ref: k2, props: d2, _owner: h };
  };
  react_production_min.createContext = function(a) {
    a = { $$typeof: u3, _currentValue: a, _currentValue2: a, _threadCount: 0, Provider: null, Consumer: null, _defaultValue: null, _globalName: null };
    a.Provider = { $$typeof: t, _context: a };
    return a.Consumer = a;
  };
  react_production_min.createElement = M2;
  react_production_min.createFactory = function(a) {
    var b2 = M2.bind(null, a);
    b2.type = a;
    return b2;
  };
  react_production_min.createRef = function() {
    return { current: null };
  };
  react_production_min.forwardRef = function(a) {
    return { $$typeof: v2, render: a };
  };
  react_production_min.isValidElement = O;
  react_production_min.lazy = function(a) {
    return { $$typeof: y2, _payload: { _status: -1, _result: a }, _init: T2 };
  };
  react_production_min.memo = function(a, b2) {
    return { $$typeof: x2, type: a, compare: void 0 === b2 ? null : b2 };
  };
  react_production_min.startTransition = function(a) {
    var b2 = V2.transition;
    V2.transition = {};
    try {
      a();
    } finally {
      V2.transition = b2;
    }
  };
  react_production_min.unstable_act = X2;
  react_production_min.useCallback = function(a, b2) {
    return U2.current.useCallback(a, b2);
  };
  react_production_min.useContext = function(a) {
    return U2.current.useContext(a);
  };
  react_production_min.useDebugValue = function() {
  };
  react_production_min.useDeferredValue = function(a) {
    return U2.current.useDeferredValue(a);
  };
  react_production_min.useEffect = function(a, b2) {
    return U2.current.useEffect(a, b2);
  };
  react_production_min.useId = function() {
    return U2.current.useId();
  };
  react_production_min.useImperativeHandle = function(a, b2, e) {
    return U2.current.useImperativeHandle(a, b2, e);
  };
  react_production_min.useInsertionEffect = function(a, b2) {
    return U2.current.useInsertionEffect(a, b2);
  };
  react_production_min.useLayoutEffect = function(a, b2) {
    return U2.current.useLayoutEffect(a, b2);
  };
  react_production_min.useMemo = function(a, b2) {
    return U2.current.useMemo(a, b2);
  };
  react_production_min.useReducer = function(a, b2, e) {
    return U2.current.useReducer(a, b2, e);
  };
  react_production_min.useRef = function(a) {
    return U2.current.useRef(a);
  };
  react_production_min.useState = function(a) {
    return U2.current.useState(a);
  };
  react_production_min.useSyncExternalStore = function(a, b2, e) {
    return U2.current.useSyncExternalStore(a, b2, e);
  };
  react_production_min.useTransition = function() {
    return U2.current.useTransition();
  };
  react_production_min.version = "18.3.1";
  return react_production_min;
}
var hasRequiredReact;
function requireReact() {
  if (hasRequiredReact) return react.exports;
  hasRequiredReact = 1;
  {
    react.exports = requireReact_production_min();
  }
  return react.exports;
}
/**
 * @license React
 * react-jsx-runtime.production.min.js
 *
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
var hasRequiredReactJsxRuntime_production_min;
function requireReactJsxRuntime_production_min() {
  if (hasRequiredReactJsxRuntime_production_min) return reactJsxRuntime_production_min;
  hasRequiredReactJsxRuntime_production_min = 1;
  var f = requireReact(), k2 = Symbol.for("react.element"), l = Symbol.for("react.fragment"), m2 = Object.prototype.hasOwnProperty, n = f.__SECRET_INTERNALS_DO_NOT_USE_OR_YOU_WILL_BE_FIRED.ReactCurrentOwner, p = { key: true, ref: true, __self: true, __source: true };
  function q2(c, a, g) {
    var b2, d2 = {}, e = null, h = null;
    void 0 !== g && (e = "" + g);
    void 0 !== a.key && (e = "" + a.key);
    void 0 !== a.ref && (h = a.ref);
    for (b2 in a) m2.call(a, b2) && !p.hasOwnProperty(b2) && (d2[b2] = a[b2]);
    if (c && c.defaultProps) for (b2 in a = c.defaultProps, a) void 0 === d2[b2] && (d2[b2] = a[b2]);
    return { $$typeof: k2, type: c, key: e, ref: h, props: d2, _owner: n.current };
  }
  reactJsxRuntime_production_min.Fragment = l;
  reactJsxRuntime_production_min.jsx = q2;
  reactJsxRuntime_production_min.jsxs = q2;
  return reactJsxRuntime_production_min;
}
var hasRequiredJsxRuntime;
function requireJsxRuntime() {
  if (hasRequiredJsxRuntime) return jsxRuntime.exports;
  hasRequiredJsxRuntime = 1;
  {
    jsxRuntime.exports = requireReactJsxRuntime_production_min();
  }
  return jsxRuntime.exports;
}
var jsxRuntimeExports = requireJsxRuntime();
var reactExports = requireReact();
var client = {};
var reactDom = { exports: {} };
var reactDom_production_min = {};
var scheduler = { exports: {} };
var scheduler_production_min = {};
/**
 * @license React
 * scheduler.production.min.js
 *
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
var hasRequiredScheduler_production_min;
function requireScheduler_production_min() {
  if (hasRequiredScheduler_production_min) return scheduler_production_min;
  hasRequiredScheduler_production_min = 1;
  (function(exports) {
    function f(a, b2) {
      var c = a.length;
      a.push(b2);
      a: for (; 0 < c; ) {
        var d2 = c - 1 >>> 1, e = a[d2];
        if (0 < g(e, b2)) a[d2] = b2, a[c] = e, c = d2;
        else break a;
      }
    }
    function h(a) {
      return 0 === a.length ? null : a[0];
    }
    function k2(a) {
      if (0 === a.length) return null;
      var b2 = a[0], c = a.pop();
      if (c !== b2) {
        a[0] = c;
        a: for (var d2 = 0, e = a.length, w2 = e >>> 1; d2 < w2; ) {
          var m2 = 2 * (d2 + 1) - 1, C2 = a[m2], n = m2 + 1, x2 = a[n];
          if (0 > g(C2, c)) n < e && 0 > g(x2, C2) ? (a[d2] = x2, a[n] = c, d2 = n) : (a[d2] = C2, a[m2] = c, d2 = m2);
          else if (n < e && 0 > g(x2, c)) a[d2] = x2, a[n] = c, d2 = n;
          else break a;
        }
      }
      return b2;
    }
    function g(a, b2) {
      var c = a.sortIndex - b2.sortIndex;
      return 0 !== c ? c : a.id - b2.id;
    }
    if ("object" === typeof performance && "function" === typeof performance.now) {
      var l = performance;
      exports.unstable_now = function() {
        return l.now();
      };
    } else {
      var p = Date, q2 = p.now();
      exports.unstable_now = function() {
        return p.now() - q2;
      };
    }
    var r = [], t = [], u3 = 1, v2 = null, y2 = 3, z2 = false, A = false, B2 = false, D2 = "function" === typeof setTimeout ? setTimeout : null, E2 = "function" === typeof clearTimeout ? clearTimeout : null, F2 = "undefined" !== typeof setImmediate ? setImmediate : null;
    "undefined" !== typeof navigator && void 0 !== navigator.scheduling && void 0 !== navigator.scheduling.isInputPending && navigator.scheduling.isInputPending.bind(navigator.scheduling);
    function G2(a) {
      for (var b2 = h(t); null !== b2; ) {
        if (null === b2.callback) k2(t);
        else if (b2.startTime <= a) k2(t), b2.sortIndex = b2.expirationTime, f(r, b2);
        else break;
        b2 = h(t);
      }
    }
    function H(a) {
      B2 = false;
      G2(a);
      if (!A) if (null !== h(r)) A = true, I2(J2);
      else {
        var b2 = h(t);
        null !== b2 && K2(H, b2.startTime - a);
      }
    }
    function J2(a, b2) {
      A = false;
      B2 && (B2 = false, E2(L2), L2 = -1);
      z2 = true;
      var c = y2;
      try {
        G2(b2);
        for (v2 = h(r); null !== v2 && (!(v2.expirationTime > b2) || a && !M2()); ) {
          var d2 = v2.callback;
          if ("function" === typeof d2) {
            v2.callback = null;
            y2 = v2.priorityLevel;
            var e = d2(v2.expirationTime <= b2);
            b2 = exports.unstable_now();
            "function" === typeof e ? v2.callback = e : v2 === h(r) && k2(r);
            G2(b2);
          } else k2(r);
          v2 = h(r);
        }
        if (null !== v2) var w2 = true;
        else {
          var m2 = h(t);
          null !== m2 && K2(H, m2.startTime - b2);
          w2 = false;
        }
        return w2;
      } finally {
        v2 = null, y2 = c, z2 = false;
      }
    }
    var N2 = false, O = null, L2 = -1, P2 = 5, Q2 = -1;
    function M2() {
      return exports.unstable_now() - Q2 < P2 ? false : true;
    }
    function R() {
      if (null !== O) {
        var a = exports.unstable_now();
        Q2 = a;
        var b2 = true;
        try {
          b2 = O(true, a);
        } finally {
          b2 ? S2() : (N2 = false, O = null);
        }
      } else N2 = false;
    }
    var S2;
    if ("function" === typeof F2) S2 = function() {
      F2(R);
    };
    else if ("undefined" !== typeof MessageChannel) {
      var T2 = new MessageChannel(), U2 = T2.port2;
      T2.port1.onmessage = R;
      S2 = function() {
        U2.postMessage(null);
      };
    } else S2 = function() {
      D2(R, 0);
    };
    function I2(a) {
      O = a;
      N2 || (N2 = true, S2());
    }
    function K2(a, b2) {
      L2 = D2(function() {
        a(exports.unstable_now());
      }, b2);
    }
    exports.unstable_IdlePriority = 5;
    exports.unstable_ImmediatePriority = 1;
    exports.unstable_LowPriority = 4;
    exports.unstable_NormalPriority = 3;
    exports.unstable_Profiling = null;
    exports.unstable_UserBlockingPriority = 2;
    exports.unstable_cancelCallback = function(a) {
      a.callback = null;
    };
    exports.unstable_continueExecution = function() {
      A || z2 || (A = true, I2(J2));
    };
    exports.unstable_forceFrameRate = function(a) {
      0 > a || 125 < a ? console.error("forceFrameRate takes a positive int between 0 and 125, forcing frame rates higher than 125 fps is not supported") : P2 = 0 < a ? Math.floor(1e3 / a) : 5;
    };
    exports.unstable_getCurrentPriorityLevel = function() {
      return y2;
    };
    exports.unstable_getFirstCallbackNode = function() {
      return h(r);
    };
    exports.unstable_next = function(a) {
      switch (y2) {
        case 1:
        case 2:
        case 3:
          var b2 = 3;
          break;
        default:
          b2 = y2;
      }
      var c = y2;
      y2 = b2;
      try {
        return a();
      } finally {
        y2 = c;
      }
    };
    exports.unstable_pauseExecution = function() {
    };
    exports.unstable_requestPaint = function() {
    };
    exports.unstable_runWithPriority = function(a, b2) {
      switch (a) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
          break;
        default:
          a = 3;
      }
      var c = y2;
      y2 = a;
      try {
        return b2();
      } finally {
        y2 = c;
      }
    };
    exports.unstable_scheduleCallback = function(a, b2, c) {
      var d2 = exports.unstable_now();
      "object" === typeof c && null !== c ? (c = c.delay, c = "number" === typeof c && 0 < c ? d2 + c : d2) : c = d2;
      switch (a) {
        case 1:
          var e = -1;
          break;
        case 2:
          e = 250;
          break;
        case 5:
          e = 1073741823;
          break;
        case 4:
          e = 1e4;
          break;
        default:
          e = 5e3;
      }
      e = c + e;
      a = { id: u3++, callback: b2, priorityLevel: a, startTime: c, expirationTime: e, sortIndex: -1 };
      c > d2 ? (a.sortIndex = c, f(t, a), null === h(r) && a === h(t) && (B2 ? (E2(L2), L2 = -1) : B2 = true, K2(H, c - d2))) : (a.sortIndex = e, f(r, a), A || z2 || (A = true, I2(J2)));
      return a;
    };
    exports.unstable_shouldYield = M2;
    exports.unstable_wrapCallback = function(a) {
      var b2 = y2;
      return function() {
        var c = y2;
        y2 = b2;
        try {
          return a.apply(this, arguments);
        } finally {
          y2 = c;
        }
      };
    };
  })(scheduler_production_min);
  return scheduler_production_min;
}
var hasRequiredScheduler;
function requireScheduler() {
  if (hasRequiredScheduler) return scheduler.exports;
  hasRequiredScheduler = 1;
  {
    scheduler.exports = requireScheduler_production_min();
  }
  return scheduler.exports;
}
/**
 * @license React
 * react-dom.production.min.js
 *
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
var hasRequiredReactDom_production_min;
function requireReactDom_production_min() {
  if (hasRequiredReactDom_production_min) return reactDom_production_min;
  hasRequiredReactDom_production_min = 1;
  var aa = requireReact(), ca = requireScheduler();
  function p(a) {
    for (var b2 = "https://reactjs.org/docs/error-decoder.html?invariant=" + a, c = 1; c < arguments.length; c++) b2 += "&args[]=" + encodeURIComponent(arguments[c]);
    return "Minified React error #" + a + "; visit " + b2 + " for the full message or use the non-minified dev environment for full errors and additional helpful warnings.";
  }
  var da = /* @__PURE__ */ new Set(), ea = {};
  function fa(a, b2) {
    ha(a, b2);
    ha(a + "Capture", b2);
  }
  function ha(a, b2) {
    ea[a] = b2;
    for (a = 0; a < b2.length; a++) da.add(b2[a]);
  }
  var ia = !("undefined" === typeof window || "undefined" === typeof window.document || "undefined" === typeof window.document.createElement), ja = Object.prototype.hasOwnProperty, ka = /^[:A-Z_a-z\u00C0-\u00D6\u00D8-\u00F6\u00F8-\u02FF\u0370-\u037D\u037F-\u1FFF\u200C-\u200D\u2070-\u218F\u2C00-\u2FEF\u3001-\uD7FF\uF900-\uFDCF\uFDF0-\uFFFD][:A-Z_a-z\u00C0-\u00D6\u00D8-\u00F6\u00F8-\u02FF\u0370-\u037D\u037F-\u1FFF\u200C-\u200D\u2070-\u218F\u2C00-\u2FEF\u3001-\uD7FF\uF900-\uFDCF\uFDF0-\uFFFD\-.0-9\u00B7\u0300-\u036F\u203F-\u2040]*$/, la = {}, ma = {};
  function oa(a) {
    if (ja.call(ma, a)) return true;
    if (ja.call(la, a)) return false;
    if (ka.test(a)) return ma[a] = true;
    la[a] = true;
    return false;
  }
  function pa(a, b2, c, d2) {
    if (null !== c && 0 === c.type) return false;
    switch (typeof b2) {
      case "function":
      case "symbol":
        return true;
      case "boolean":
        if (d2) return false;
        if (null !== c) return !c.acceptsBooleans;
        a = a.toLowerCase().slice(0, 5);
        return "data-" !== a && "aria-" !== a;
      default:
        return false;
    }
  }
  function qa(a, b2, c, d2) {
    if (null === b2 || "undefined" === typeof b2 || pa(a, b2, c, d2)) return true;
    if (d2) return false;
    if (null !== c) switch (c.type) {
      case 3:
        return !b2;
      case 4:
        return false === b2;
      case 5:
        return isNaN(b2);
      case 6:
        return isNaN(b2) || 1 > b2;
    }
    return false;
  }
  function v2(a, b2, c, d2, e, f, g) {
    this.acceptsBooleans = 2 === b2 || 3 === b2 || 4 === b2;
    this.attributeName = d2;
    this.attributeNamespace = e;
    this.mustUseProperty = c;
    this.propertyName = a;
    this.type = b2;
    this.sanitizeURL = f;
    this.removeEmptyString = g;
  }
  var z2 = {};
  "children dangerouslySetInnerHTML defaultValue defaultChecked innerHTML suppressContentEditableWarning suppressHydrationWarning style".split(" ").forEach(function(a) {
    z2[a] = new v2(a, 0, false, a, null, false, false);
  });
  [["acceptCharset", "accept-charset"], ["className", "class"], ["htmlFor", "for"], ["httpEquiv", "http-equiv"]].forEach(function(a) {
    var b2 = a[0];
    z2[b2] = new v2(b2, 1, false, a[1], null, false, false);
  });
  ["contentEditable", "draggable", "spellCheck", "value"].forEach(function(a) {
    z2[a] = new v2(a, 2, false, a.toLowerCase(), null, false, false);
  });
  ["autoReverse", "externalResourcesRequired", "focusable", "preserveAlpha"].forEach(function(a) {
    z2[a] = new v2(a, 2, false, a, null, false, false);
  });
  "allowFullScreen async autoFocus autoPlay controls default defer disabled disablePictureInPicture disableRemotePlayback formNoValidate hidden loop noModule noValidate open playsInline readOnly required reversed scoped seamless itemScope".split(" ").forEach(function(a) {
    z2[a] = new v2(a, 3, false, a.toLowerCase(), null, false, false);
  });
  ["checked", "multiple", "muted", "selected"].forEach(function(a) {
    z2[a] = new v2(a, 3, true, a, null, false, false);
  });
  ["capture", "download"].forEach(function(a) {
    z2[a] = new v2(a, 4, false, a, null, false, false);
  });
  ["cols", "rows", "size", "span"].forEach(function(a) {
    z2[a] = new v2(a, 6, false, a, null, false, false);
  });
  ["rowSpan", "start"].forEach(function(a) {
    z2[a] = new v2(a, 5, false, a.toLowerCase(), null, false, false);
  });
  var ra = /[\-:]([a-z])/g;
  function sa(a) {
    return a[1].toUpperCase();
  }
  "accent-height alignment-baseline arabic-form baseline-shift cap-height clip-path clip-rule color-interpolation color-interpolation-filters color-profile color-rendering dominant-baseline enable-background fill-opacity fill-rule flood-color flood-opacity font-family font-size font-size-adjust font-stretch font-style font-variant font-weight glyph-name glyph-orientation-horizontal glyph-orientation-vertical horiz-adv-x horiz-origin-x image-rendering letter-spacing lighting-color marker-end marker-mid marker-start overline-position overline-thickness paint-order panose-1 pointer-events rendering-intent shape-rendering stop-color stop-opacity strikethrough-position strikethrough-thickness stroke-dasharray stroke-dashoffset stroke-linecap stroke-linejoin stroke-miterlimit stroke-opacity stroke-width text-anchor text-decoration text-rendering underline-position underline-thickness unicode-bidi unicode-range units-per-em v-alphabetic v-hanging v-ideographic v-mathematical vector-effect vert-adv-y vert-origin-x vert-origin-y word-spacing writing-mode xmlns:xlink x-height".split(" ").forEach(function(a) {
    var b2 = a.replace(
      ra,
      sa
    );
    z2[b2] = new v2(b2, 1, false, a, null, false, false);
  });
  "xlink:actuate xlink:arcrole xlink:role xlink:show xlink:title xlink:type".split(" ").forEach(function(a) {
    var b2 = a.replace(ra, sa);
    z2[b2] = new v2(b2, 1, false, a, "http://www.w3.org/1999/xlink", false, false);
  });
  ["xml:base", "xml:lang", "xml:space"].forEach(function(a) {
    var b2 = a.replace(ra, sa);
    z2[b2] = new v2(b2, 1, false, a, "http://www.w3.org/XML/1998/namespace", false, false);
  });
  ["tabIndex", "crossOrigin"].forEach(function(a) {
    z2[a] = new v2(a, 1, false, a.toLowerCase(), null, false, false);
  });
  z2.xlinkHref = new v2("xlinkHref", 1, false, "xlink:href", "http://www.w3.org/1999/xlink", true, false);
  ["src", "href", "action", "formAction"].forEach(function(a) {
    z2[a] = new v2(a, 1, false, a.toLowerCase(), null, true, true);
  });
  function ta(a, b2, c, d2) {
    var e = z2.hasOwnProperty(b2) ? z2[b2] : null;
    if (null !== e ? 0 !== e.type : d2 || !(2 < b2.length) || "o" !== b2[0] && "O" !== b2[0] || "n" !== b2[1] && "N" !== b2[1]) qa(b2, c, e, d2) && (c = null), d2 || null === e ? oa(b2) && (null === c ? a.removeAttribute(b2) : a.setAttribute(b2, "" + c)) : e.mustUseProperty ? a[e.propertyName] = null === c ? 3 === e.type ? false : "" : c : (b2 = e.attributeName, d2 = e.attributeNamespace, null === c ? a.removeAttribute(b2) : (e = e.type, c = 3 === e || 4 === e && true === c ? "" : "" + c, d2 ? a.setAttributeNS(d2, b2, c) : a.setAttribute(b2, c)));
  }
  var ua = aa.__SECRET_INTERNALS_DO_NOT_USE_OR_YOU_WILL_BE_FIRED, va = Symbol.for("react.element"), wa = Symbol.for("react.portal"), ya = Symbol.for("react.fragment"), za = Symbol.for("react.strict_mode"), Aa = Symbol.for("react.profiler"), Ba = Symbol.for("react.provider"), Ca = Symbol.for("react.context"), Da = Symbol.for("react.forward_ref"), Ea = Symbol.for("react.suspense"), Fa = Symbol.for("react.suspense_list"), Ga = Symbol.for("react.memo"), Ha = Symbol.for("react.lazy");
  var Ia = Symbol.for("react.offscreen");
  var Ja = Symbol.iterator;
  function Ka(a) {
    if (null === a || "object" !== typeof a) return null;
    a = Ja && a[Ja] || a["@@iterator"];
    return "function" === typeof a ? a : null;
  }
  var A = Object.assign, La;
  function Ma(a) {
    if (void 0 === La) try {
      throw Error();
    } catch (c) {
      var b2 = c.stack.trim().match(/\n( *(at )?)/);
      La = b2 && b2[1] || "";
    }
    return "\n" + La + a;
  }
  var Na = false;
  function Oa(a, b2) {
    if (!a || Na) return "";
    Na = true;
    var c = Error.prepareStackTrace;
    Error.prepareStackTrace = void 0;
    try {
      if (b2) if (b2 = function() {
        throw Error();
      }, Object.defineProperty(b2.prototype, "props", { set: function() {
        throw Error();
      } }), "object" === typeof Reflect && Reflect.construct) {
        try {
          Reflect.construct(b2, []);
        } catch (l) {
          var d2 = l;
        }
        Reflect.construct(a, [], b2);
      } else {
        try {
          b2.call();
        } catch (l) {
          d2 = l;
        }
        a.call(b2.prototype);
      }
      else {
        try {
          throw Error();
        } catch (l) {
          d2 = l;
        }
        a();
      }
    } catch (l) {
      if (l && d2 && "string" === typeof l.stack) {
        for (var e = l.stack.split("\n"), f = d2.stack.split("\n"), g = e.length - 1, h = f.length - 1; 1 <= g && 0 <= h && e[g] !== f[h]; ) h--;
        for (; 1 <= g && 0 <= h; g--, h--) if (e[g] !== f[h]) {
          if (1 !== g || 1 !== h) {
            do
              if (g--, h--, 0 > h || e[g] !== f[h]) {
                var k2 = "\n" + e[g].replace(" at new ", " at ");
                a.displayName && k2.includes("<anonymous>") && (k2 = k2.replace("<anonymous>", a.displayName));
                return k2;
              }
            while (1 <= g && 0 <= h);
          }
          break;
        }
      }
    } finally {
      Na = false, Error.prepareStackTrace = c;
    }
    return (a = a ? a.displayName || a.name : "") ? Ma(a) : "";
  }
  function Pa(a) {
    switch (a.tag) {
      case 5:
        return Ma(a.type);
      case 16:
        return Ma("Lazy");
      case 13:
        return Ma("Suspense");
      case 19:
        return Ma("SuspenseList");
      case 0:
      case 2:
      case 15:
        return a = Oa(a.type, false), a;
      case 11:
        return a = Oa(a.type.render, false), a;
      case 1:
        return a = Oa(a.type, true), a;
      default:
        return "";
    }
  }
  function Qa(a) {
    if (null == a) return null;
    if ("function" === typeof a) return a.displayName || a.name || null;
    if ("string" === typeof a) return a;
    switch (a) {
      case ya:
        return "Fragment";
      case wa:
        return "Portal";
      case Aa:
        return "Profiler";
      case za:
        return "StrictMode";
      case Ea:
        return "Suspense";
      case Fa:
        return "SuspenseList";
    }
    if ("object" === typeof a) switch (a.$$typeof) {
      case Ca:
        return (a.displayName || "Context") + ".Consumer";
      case Ba:
        return (a._context.displayName || "Context") + ".Provider";
      case Da:
        var b2 = a.render;
        a = a.displayName;
        a || (a = b2.displayName || b2.name || "", a = "" !== a ? "ForwardRef(" + a + ")" : "ForwardRef");
        return a;
      case Ga:
        return b2 = a.displayName || null, null !== b2 ? b2 : Qa(a.type) || "Memo";
      case Ha:
        b2 = a._payload;
        a = a._init;
        try {
          return Qa(a(b2));
        } catch (c) {
        }
    }
    return null;
  }
  function Ra(a) {
    var b2 = a.type;
    switch (a.tag) {
      case 24:
        return "Cache";
      case 9:
        return (b2.displayName || "Context") + ".Consumer";
      case 10:
        return (b2._context.displayName || "Context") + ".Provider";
      case 18:
        return "DehydratedFragment";
      case 11:
        return a = b2.render, a = a.displayName || a.name || "", b2.displayName || ("" !== a ? "ForwardRef(" + a + ")" : "ForwardRef");
      case 7:
        return "Fragment";
      case 5:
        return b2;
      case 4:
        return "Portal";
      case 3:
        return "Root";
      case 6:
        return "Text";
      case 16:
        return Qa(b2);
      case 8:
        return b2 === za ? "StrictMode" : "Mode";
      case 22:
        return "Offscreen";
      case 12:
        return "Profiler";
      case 21:
        return "Scope";
      case 13:
        return "Suspense";
      case 19:
        return "SuspenseList";
      case 25:
        return "TracingMarker";
      case 1:
      case 0:
      case 17:
      case 2:
      case 14:
      case 15:
        if ("function" === typeof b2) return b2.displayName || b2.name || null;
        if ("string" === typeof b2) return b2;
    }
    return null;
  }
  function Sa(a) {
    switch (typeof a) {
      case "boolean":
      case "number":
      case "string":
      case "undefined":
        return a;
      case "object":
        return a;
      default:
        return "";
    }
  }
  function Ta(a) {
    var b2 = a.type;
    return (a = a.nodeName) && "input" === a.toLowerCase() && ("checkbox" === b2 || "radio" === b2);
  }
  function Ua(a) {
    var b2 = Ta(a) ? "checked" : "value", c = Object.getOwnPropertyDescriptor(a.constructor.prototype, b2), d2 = "" + a[b2];
    if (!a.hasOwnProperty(b2) && "undefined" !== typeof c && "function" === typeof c.get && "function" === typeof c.set) {
      var e = c.get, f = c.set;
      Object.defineProperty(a, b2, { configurable: true, get: function() {
        return e.call(this);
      }, set: function(a2) {
        d2 = "" + a2;
        f.call(this, a2);
      } });
      Object.defineProperty(a, b2, { enumerable: c.enumerable });
      return { getValue: function() {
        return d2;
      }, setValue: function(a2) {
        d2 = "" + a2;
      }, stopTracking: function() {
        a._valueTracker = null;
        delete a[b2];
      } };
    }
  }
  function Va(a) {
    a._valueTracker || (a._valueTracker = Ua(a));
  }
  function Wa(a) {
    if (!a) return false;
    var b2 = a._valueTracker;
    if (!b2) return true;
    var c = b2.getValue();
    var d2 = "";
    a && (d2 = Ta(a) ? a.checked ? "true" : "false" : a.value);
    a = d2;
    return a !== c ? (b2.setValue(a), true) : false;
  }
  function Xa(a) {
    a = a || ("undefined" !== typeof document ? document : void 0);
    if ("undefined" === typeof a) return null;
    try {
      return a.activeElement || a.body;
    } catch (b2) {
      return a.body;
    }
  }
  function Ya(a, b2) {
    var c = b2.checked;
    return A({}, b2, { defaultChecked: void 0, defaultValue: void 0, value: void 0, checked: null != c ? c : a._wrapperState.initialChecked });
  }
  function Za(a, b2) {
    var c = null == b2.defaultValue ? "" : b2.defaultValue, d2 = null != b2.checked ? b2.checked : b2.defaultChecked;
    c = Sa(null != b2.value ? b2.value : c);
    a._wrapperState = { initialChecked: d2, initialValue: c, controlled: "checkbox" === b2.type || "radio" === b2.type ? null != b2.checked : null != b2.value };
  }
  function ab(a, b2) {
    b2 = b2.checked;
    null != b2 && ta(a, "checked", b2, false);
  }
  function bb(a, b2) {
    ab(a, b2);
    var c = Sa(b2.value), d2 = b2.type;
    if (null != c) if ("number" === d2) {
      if (0 === c && "" === a.value || a.value != c) a.value = "" + c;
    } else a.value !== "" + c && (a.value = "" + c);
    else if ("submit" === d2 || "reset" === d2) {
      a.removeAttribute("value");
      return;
    }
    b2.hasOwnProperty("value") ? cb(a, b2.type, c) : b2.hasOwnProperty("defaultValue") && cb(a, b2.type, Sa(b2.defaultValue));
    null == b2.checked && null != b2.defaultChecked && (a.defaultChecked = !!b2.defaultChecked);
  }
  function db(a, b2, c) {
    if (b2.hasOwnProperty("value") || b2.hasOwnProperty("defaultValue")) {
      var d2 = b2.type;
      if (!("submit" !== d2 && "reset" !== d2 || void 0 !== b2.value && null !== b2.value)) return;
      b2 = "" + a._wrapperState.initialValue;
      c || b2 === a.value || (a.value = b2);
      a.defaultValue = b2;
    }
    c = a.name;
    "" !== c && (a.name = "");
    a.defaultChecked = !!a._wrapperState.initialChecked;
    "" !== c && (a.name = c);
  }
  function cb(a, b2, c) {
    if ("number" !== b2 || Xa(a.ownerDocument) !== a) null == c ? a.defaultValue = "" + a._wrapperState.initialValue : a.defaultValue !== "" + c && (a.defaultValue = "" + c);
  }
  var eb = Array.isArray;
  function fb(a, b2, c, d2) {
    a = a.options;
    if (b2) {
      b2 = {};
      for (var e = 0; e < c.length; e++) b2["$" + c[e]] = true;
      for (c = 0; c < a.length; c++) e = b2.hasOwnProperty("$" + a[c].value), a[c].selected !== e && (a[c].selected = e), e && d2 && (a[c].defaultSelected = true);
    } else {
      c = "" + Sa(c);
      b2 = null;
      for (e = 0; e < a.length; e++) {
        if (a[e].value === c) {
          a[e].selected = true;
          d2 && (a[e].defaultSelected = true);
          return;
        }
        null !== b2 || a[e].disabled || (b2 = a[e]);
      }
      null !== b2 && (b2.selected = true);
    }
  }
  function gb(a, b2) {
    if (null != b2.dangerouslySetInnerHTML) throw Error(p(91));
    return A({}, b2, { value: void 0, defaultValue: void 0, children: "" + a._wrapperState.initialValue });
  }
  function hb(a, b2) {
    var c = b2.value;
    if (null == c) {
      c = b2.children;
      b2 = b2.defaultValue;
      if (null != c) {
        if (null != b2) throw Error(p(92));
        if (eb(c)) {
          if (1 < c.length) throw Error(p(93));
          c = c[0];
        }
        b2 = c;
      }
      null == b2 && (b2 = "");
      c = b2;
    }
    a._wrapperState = { initialValue: Sa(c) };
  }
  function ib(a, b2) {
    var c = Sa(b2.value), d2 = Sa(b2.defaultValue);
    null != c && (c = "" + c, c !== a.value && (a.value = c), null == b2.defaultValue && a.defaultValue !== c && (a.defaultValue = c));
    null != d2 && (a.defaultValue = "" + d2);
  }
  function jb(a) {
    var b2 = a.textContent;
    b2 === a._wrapperState.initialValue && "" !== b2 && null !== b2 && (a.value = b2);
  }
  function kb(a) {
    switch (a) {
      case "svg":
        return "http://www.w3.org/2000/svg";
      case "math":
        return "http://www.w3.org/1998/Math/MathML";
      default:
        return "http://www.w3.org/1999/xhtml";
    }
  }
  function lb(a, b2) {
    return null == a || "http://www.w3.org/1999/xhtml" === a ? kb(b2) : "http://www.w3.org/2000/svg" === a && "foreignObject" === b2 ? "http://www.w3.org/1999/xhtml" : a;
  }
  var mb, nb = (function(a) {
    return "undefined" !== typeof MSApp && MSApp.execUnsafeLocalFunction ? function(b2, c, d2, e) {
      MSApp.execUnsafeLocalFunction(function() {
        return a(b2, c, d2, e);
      });
    } : a;
  })(function(a, b2) {
    if ("http://www.w3.org/2000/svg" !== a.namespaceURI || "innerHTML" in a) a.innerHTML = b2;
    else {
      mb = mb || document.createElement("div");
      mb.innerHTML = "<svg>" + b2.valueOf().toString() + "</svg>";
      for (b2 = mb.firstChild; a.firstChild; ) a.removeChild(a.firstChild);
      for (; b2.firstChild; ) a.appendChild(b2.firstChild);
    }
  });
  function ob(a, b2) {
    if (b2) {
      var c = a.firstChild;
      if (c && c === a.lastChild && 3 === c.nodeType) {
        c.nodeValue = b2;
        return;
      }
    }
    a.textContent = b2;
  }
  var pb = {
    animationIterationCount: true,
    aspectRatio: true,
    borderImageOutset: true,
    borderImageSlice: true,
    borderImageWidth: true,
    boxFlex: true,
    boxFlexGroup: true,
    boxOrdinalGroup: true,
    columnCount: true,
    columns: true,
    flex: true,
    flexGrow: true,
    flexPositive: true,
    flexShrink: true,
    flexNegative: true,
    flexOrder: true,
    gridArea: true,
    gridRow: true,
    gridRowEnd: true,
    gridRowSpan: true,
    gridRowStart: true,
    gridColumn: true,
    gridColumnEnd: true,
    gridColumnSpan: true,
    gridColumnStart: true,
    fontWeight: true,
    lineClamp: true,
    lineHeight: true,
    opacity: true,
    order: true,
    orphans: true,
    tabSize: true,
    widows: true,
    zIndex: true,
    zoom: true,
    fillOpacity: true,
    floodOpacity: true,
    stopOpacity: true,
    strokeDasharray: true,
    strokeDashoffset: true,
    strokeMiterlimit: true,
    strokeOpacity: true,
    strokeWidth: true
  }, qb = ["Webkit", "ms", "Moz", "O"];
  Object.keys(pb).forEach(function(a) {
    qb.forEach(function(b2) {
      b2 = b2 + a.charAt(0).toUpperCase() + a.substring(1);
      pb[b2] = pb[a];
    });
  });
  function rb(a, b2, c) {
    return null == b2 || "boolean" === typeof b2 || "" === b2 ? "" : c || "number" !== typeof b2 || 0 === b2 || pb.hasOwnProperty(a) && pb[a] ? ("" + b2).trim() : b2 + "px";
  }
  function sb(a, b2) {
    a = a.style;
    for (var c in b2) if (b2.hasOwnProperty(c)) {
      var d2 = 0 === c.indexOf("--"), e = rb(c, b2[c], d2);
      "float" === c && (c = "cssFloat");
      d2 ? a.setProperty(c, e) : a[c] = e;
    }
  }
  var tb = A({ menuitem: true }, { area: true, base: true, br: true, col: true, embed: true, hr: true, img: true, input: true, keygen: true, link: true, meta: true, param: true, source: true, track: true, wbr: true });
  function ub(a, b2) {
    if (b2) {
      if (tb[a] && (null != b2.children || null != b2.dangerouslySetInnerHTML)) throw Error(p(137, a));
      if (null != b2.dangerouslySetInnerHTML) {
        if (null != b2.children) throw Error(p(60));
        if ("object" !== typeof b2.dangerouslySetInnerHTML || !("__html" in b2.dangerouslySetInnerHTML)) throw Error(p(61));
      }
      if (null != b2.style && "object" !== typeof b2.style) throw Error(p(62));
    }
  }
  function vb(a, b2) {
    if (-1 === a.indexOf("-")) return "string" === typeof b2.is;
    switch (a) {
      case "annotation-xml":
      case "color-profile":
      case "font-face":
      case "font-face-src":
      case "font-face-uri":
      case "font-face-format":
      case "font-face-name":
      case "missing-glyph":
        return false;
      default:
        return true;
    }
  }
  var wb = null;
  function xb(a) {
    a = a.target || a.srcElement || window;
    a.correspondingUseElement && (a = a.correspondingUseElement);
    return 3 === a.nodeType ? a.parentNode : a;
  }
  var yb = null, zb = null, Ab = null;
  function Bb(a) {
    if (a = Cb(a)) {
      if ("function" !== typeof yb) throw Error(p(280));
      var b2 = a.stateNode;
      b2 && (b2 = Db(b2), yb(a.stateNode, a.type, b2));
    }
  }
  function Eb(a) {
    zb ? Ab ? Ab.push(a) : Ab = [a] : zb = a;
  }
  function Fb() {
    if (zb) {
      var a = zb, b2 = Ab;
      Ab = zb = null;
      Bb(a);
      if (b2) for (a = 0; a < b2.length; a++) Bb(b2[a]);
    }
  }
  function Gb(a, b2) {
    return a(b2);
  }
  function Hb() {
  }
  var Ib = false;
  function Jb(a, b2, c) {
    if (Ib) return a(b2, c);
    Ib = true;
    try {
      return Gb(a, b2, c);
    } finally {
      if (Ib = false, null !== zb || null !== Ab) Hb(), Fb();
    }
  }
  function Kb(a, b2) {
    var c = a.stateNode;
    if (null === c) return null;
    var d2 = Db(c);
    if (null === d2) return null;
    c = d2[b2];
    a: switch (b2) {
      case "onClick":
      case "onClickCapture":
      case "onDoubleClick":
      case "onDoubleClickCapture":
      case "onMouseDown":
      case "onMouseDownCapture":
      case "onMouseMove":
      case "onMouseMoveCapture":
      case "onMouseUp":
      case "onMouseUpCapture":
      case "onMouseEnter":
        (d2 = !d2.disabled) || (a = a.type, d2 = !("button" === a || "input" === a || "select" === a || "textarea" === a));
        a = !d2;
        break a;
      default:
        a = false;
    }
    if (a) return null;
    if (c && "function" !== typeof c) throw Error(p(231, b2, typeof c));
    return c;
  }
  var Lb = false;
  if (ia) try {
    var Mb = {};
    Object.defineProperty(Mb, "passive", { get: function() {
      Lb = true;
    } });
    window.addEventListener("test", Mb, Mb);
    window.removeEventListener("test", Mb, Mb);
  } catch (a) {
    Lb = false;
  }
  function Nb(a, b2, c, d2, e, f, g, h, k2) {
    var l = Array.prototype.slice.call(arguments, 3);
    try {
      b2.apply(c, l);
    } catch (m2) {
      this.onError(m2);
    }
  }
  var Ob = false, Pb = null, Qb = false, Rb = null, Sb = { onError: function(a) {
    Ob = true;
    Pb = a;
  } };
  function Tb(a, b2, c, d2, e, f, g, h, k2) {
    Ob = false;
    Pb = null;
    Nb.apply(Sb, arguments);
  }
  function Ub(a, b2, c, d2, e, f, g, h, k2) {
    Tb.apply(this, arguments);
    if (Ob) {
      if (Ob) {
        var l = Pb;
        Ob = false;
        Pb = null;
      } else throw Error(p(198));
      Qb || (Qb = true, Rb = l);
    }
  }
  function Vb(a) {
    var b2 = a, c = a;
    if (a.alternate) for (; b2.return; ) b2 = b2.return;
    else {
      a = b2;
      do
        b2 = a, 0 !== (b2.flags & 4098) && (c = b2.return), a = b2.return;
      while (a);
    }
    return 3 === b2.tag ? c : null;
  }
  function Wb(a) {
    if (13 === a.tag) {
      var b2 = a.memoizedState;
      null === b2 && (a = a.alternate, null !== a && (b2 = a.memoizedState));
      if (null !== b2) return b2.dehydrated;
    }
    return null;
  }
  function Xb(a) {
    if (Vb(a) !== a) throw Error(p(188));
  }
  function Yb(a) {
    var b2 = a.alternate;
    if (!b2) {
      b2 = Vb(a);
      if (null === b2) throw Error(p(188));
      return b2 !== a ? null : a;
    }
    for (var c = a, d2 = b2; ; ) {
      var e = c.return;
      if (null === e) break;
      var f = e.alternate;
      if (null === f) {
        d2 = e.return;
        if (null !== d2) {
          c = d2;
          continue;
        }
        break;
      }
      if (e.child === f.child) {
        for (f = e.child; f; ) {
          if (f === c) return Xb(e), a;
          if (f === d2) return Xb(e), b2;
          f = f.sibling;
        }
        throw Error(p(188));
      }
      if (c.return !== d2.return) c = e, d2 = f;
      else {
        for (var g = false, h = e.child; h; ) {
          if (h === c) {
            g = true;
            c = e;
            d2 = f;
            break;
          }
          if (h === d2) {
            g = true;
            d2 = e;
            c = f;
            break;
          }
          h = h.sibling;
        }
        if (!g) {
          for (h = f.child; h; ) {
            if (h === c) {
              g = true;
              c = f;
              d2 = e;
              break;
            }
            if (h === d2) {
              g = true;
              d2 = f;
              c = e;
              break;
            }
            h = h.sibling;
          }
          if (!g) throw Error(p(189));
        }
      }
      if (c.alternate !== d2) throw Error(p(190));
    }
    if (3 !== c.tag) throw Error(p(188));
    return c.stateNode.current === c ? a : b2;
  }
  function Zb(a) {
    a = Yb(a);
    return null !== a ? $b(a) : null;
  }
  function $b(a) {
    if (5 === a.tag || 6 === a.tag) return a;
    for (a = a.child; null !== a; ) {
      var b2 = $b(a);
      if (null !== b2) return b2;
      a = a.sibling;
    }
    return null;
  }
  var ac = ca.unstable_scheduleCallback, bc = ca.unstable_cancelCallback, cc = ca.unstable_shouldYield, dc = ca.unstable_requestPaint, B2 = ca.unstable_now, ec = ca.unstable_getCurrentPriorityLevel, fc = ca.unstable_ImmediatePriority, gc = ca.unstable_UserBlockingPriority, hc = ca.unstable_NormalPriority, ic = ca.unstable_LowPriority, jc = ca.unstable_IdlePriority, kc = null, lc = null;
  function mc(a) {
    if (lc && "function" === typeof lc.onCommitFiberRoot) try {
      lc.onCommitFiberRoot(kc, a, void 0, 128 === (a.current.flags & 128));
    } catch (b2) {
    }
  }
  var oc = Math.clz32 ? Math.clz32 : nc, pc = Math.log, qc = Math.LN2;
  function nc(a) {
    a >>>= 0;
    return 0 === a ? 32 : 31 - (pc(a) / qc | 0) | 0;
  }
  var rc = 64, sc = 4194304;
  function tc(a) {
    switch (a & -a) {
      case 1:
        return 1;
      case 2:
        return 2;
      case 4:
        return 4;
      case 8:
        return 8;
      case 16:
        return 16;
      case 32:
        return 32;
      case 64:
      case 128:
      case 256:
      case 512:
      case 1024:
      case 2048:
      case 4096:
      case 8192:
      case 16384:
      case 32768:
      case 65536:
      case 131072:
      case 262144:
      case 524288:
      case 1048576:
      case 2097152:
        return a & 4194240;
      case 4194304:
      case 8388608:
      case 16777216:
      case 33554432:
      case 67108864:
        return a & 130023424;
      case 134217728:
        return 134217728;
      case 268435456:
        return 268435456;
      case 536870912:
        return 536870912;
      case 1073741824:
        return 1073741824;
      default:
        return a;
    }
  }
  function uc(a, b2) {
    var c = a.pendingLanes;
    if (0 === c) return 0;
    var d2 = 0, e = a.suspendedLanes, f = a.pingedLanes, g = c & 268435455;
    if (0 !== g) {
      var h = g & ~e;
      0 !== h ? d2 = tc(h) : (f &= g, 0 !== f && (d2 = tc(f)));
    } else g = c & ~e, 0 !== g ? d2 = tc(g) : 0 !== f && (d2 = tc(f));
    if (0 === d2) return 0;
    if (0 !== b2 && b2 !== d2 && 0 === (b2 & e) && (e = d2 & -d2, f = b2 & -b2, e >= f || 16 === e && 0 !== (f & 4194240))) return b2;
    0 !== (d2 & 4) && (d2 |= c & 16);
    b2 = a.entangledLanes;
    if (0 !== b2) for (a = a.entanglements, b2 &= d2; 0 < b2; ) c = 31 - oc(b2), e = 1 << c, d2 |= a[c], b2 &= ~e;
    return d2;
  }
  function vc(a, b2) {
    switch (a) {
      case 1:
      case 2:
      case 4:
        return b2 + 250;
      case 8:
      case 16:
      case 32:
      case 64:
      case 128:
      case 256:
      case 512:
      case 1024:
      case 2048:
      case 4096:
      case 8192:
      case 16384:
      case 32768:
      case 65536:
      case 131072:
      case 262144:
      case 524288:
      case 1048576:
      case 2097152:
        return b2 + 5e3;
      case 4194304:
      case 8388608:
      case 16777216:
      case 33554432:
      case 67108864:
        return -1;
      case 134217728:
      case 268435456:
      case 536870912:
      case 1073741824:
        return -1;
      default:
        return -1;
    }
  }
  function wc(a, b2) {
    for (var c = a.suspendedLanes, d2 = a.pingedLanes, e = a.expirationTimes, f = a.pendingLanes; 0 < f; ) {
      var g = 31 - oc(f), h = 1 << g, k2 = e[g];
      if (-1 === k2) {
        if (0 === (h & c) || 0 !== (h & d2)) e[g] = vc(h, b2);
      } else k2 <= b2 && (a.expiredLanes |= h);
      f &= ~h;
    }
  }
  function xc(a) {
    a = a.pendingLanes & -1073741825;
    return 0 !== a ? a : a & 1073741824 ? 1073741824 : 0;
  }
  function yc() {
    var a = rc;
    rc <<= 1;
    0 === (rc & 4194240) && (rc = 64);
    return a;
  }
  function zc(a) {
    for (var b2 = [], c = 0; 31 > c; c++) b2.push(a);
    return b2;
  }
  function Ac(a, b2, c) {
    a.pendingLanes |= b2;
    536870912 !== b2 && (a.suspendedLanes = 0, a.pingedLanes = 0);
    a = a.eventTimes;
    b2 = 31 - oc(b2);
    a[b2] = c;
  }
  function Bc(a, b2) {
    var c = a.pendingLanes & ~b2;
    a.pendingLanes = b2;
    a.suspendedLanes = 0;
    a.pingedLanes = 0;
    a.expiredLanes &= b2;
    a.mutableReadLanes &= b2;
    a.entangledLanes &= b2;
    b2 = a.entanglements;
    var d2 = a.eventTimes;
    for (a = a.expirationTimes; 0 < c; ) {
      var e = 31 - oc(c), f = 1 << e;
      b2[e] = 0;
      d2[e] = -1;
      a[e] = -1;
      c &= ~f;
    }
  }
  function Cc(a, b2) {
    var c = a.entangledLanes |= b2;
    for (a = a.entanglements; c; ) {
      var d2 = 31 - oc(c), e = 1 << d2;
      e & b2 | a[d2] & b2 && (a[d2] |= b2);
      c &= ~e;
    }
  }
  var C2 = 0;
  function Dc(a) {
    a &= -a;
    return 1 < a ? 4 < a ? 0 !== (a & 268435455) ? 16 : 536870912 : 4 : 1;
  }
  var Ec, Fc, Gc, Hc, Ic, Jc = false, Kc = [], Lc = null, Mc = null, Nc = null, Oc = /* @__PURE__ */ new Map(), Pc = /* @__PURE__ */ new Map(), Qc = [], Rc = "mousedown mouseup touchcancel touchend touchstart auxclick dblclick pointercancel pointerdown pointerup dragend dragstart drop compositionend compositionstart keydown keypress keyup input textInput copy cut paste click change contextmenu reset submit".split(" ");
  function Sc(a, b2) {
    switch (a) {
      case "focusin":
      case "focusout":
        Lc = null;
        break;
      case "dragenter":
      case "dragleave":
        Mc = null;
        break;
      case "mouseover":
      case "mouseout":
        Nc = null;
        break;
      case "pointerover":
      case "pointerout":
        Oc.delete(b2.pointerId);
        break;
      case "gotpointercapture":
      case "lostpointercapture":
        Pc.delete(b2.pointerId);
    }
  }
  function Tc(a, b2, c, d2, e, f) {
    if (null === a || a.nativeEvent !== f) return a = { blockedOn: b2, domEventName: c, eventSystemFlags: d2, nativeEvent: f, targetContainers: [e] }, null !== b2 && (b2 = Cb(b2), null !== b2 && Fc(b2)), a;
    a.eventSystemFlags |= d2;
    b2 = a.targetContainers;
    null !== e && -1 === b2.indexOf(e) && b2.push(e);
    return a;
  }
  function Uc(a, b2, c, d2, e) {
    switch (b2) {
      case "focusin":
        return Lc = Tc(Lc, a, b2, c, d2, e), true;
      case "dragenter":
        return Mc = Tc(Mc, a, b2, c, d2, e), true;
      case "mouseover":
        return Nc = Tc(Nc, a, b2, c, d2, e), true;
      case "pointerover":
        var f = e.pointerId;
        Oc.set(f, Tc(Oc.get(f) || null, a, b2, c, d2, e));
        return true;
      case "gotpointercapture":
        return f = e.pointerId, Pc.set(f, Tc(Pc.get(f) || null, a, b2, c, d2, e)), true;
    }
    return false;
  }
  function Vc(a) {
    var b2 = Wc(a.target);
    if (null !== b2) {
      var c = Vb(b2);
      if (null !== c) {
        if (b2 = c.tag, 13 === b2) {
          if (b2 = Wb(c), null !== b2) {
            a.blockedOn = b2;
            Ic(a.priority, function() {
              Gc(c);
            });
            return;
          }
        } else if (3 === b2 && c.stateNode.current.memoizedState.isDehydrated) {
          a.blockedOn = 3 === c.tag ? c.stateNode.containerInfo : null;
          return;
        }
      }
    }
    a.blockedOn = null;
  }
  function Xc(a) {
    if (null !== a.blockedOn) return false;
    for (var b2 = a.targetContainers; 0 < b2.length; ) {
      var c = Yc(a.domEventName, a.eventSystemFlags, b2[0], a.nativeEvent);
      if (null === c) {
        c = a.nativeEvent;
        var d2 = new c.constructor(c.type, c);
        wb = d2;
        c.target.dispatchEvent(d2);
        wb = null;
      } else return b2 = Cb(c), null !== b2 && Fc(b2), a.blockedOn = c, false;
      b2.shift();
    }
    return true;
  }
  function Zc(a, b2, c) {
    Xc(a) && c.delete(b2);
  }
  function $c() {
    Jc = false;
    null !== Lc && Xc(Lc) && (Lc = null);
    null !== Mc && Xc(Mc) && (Mc = null);
    null !== Nc && Xc(Nc) && (Nc = null);
    Oc.forEach(Zc);
    Pc.forEach(Zc);
  }
  function ad(a, b2) {
    a.blockedOn === b2 && (a.blockedOn = null, Jc || (Jc = true, ca.unstable_scheduleCallback(ca.unstable_NormalPriority, $c)));
  }
  function bd(a) {
    function b2(b3) {
      return ad(b3, a);
    }
    if (0 < Kc.length) {
      ad(Kc[0], a);
      for (var c = 1; c < Kc.length; c++) {
        var d2 = Kc[c];
        d2.blockedOn === a && (d2.blockedOn = null);
      }
    }
    null !== Lc && ad(Lc, a);
    null !== Mc && ad(Mc, a);
    null !== Nc && ad(Nc, a);
    Oc.forEach(b2);
    Pc.forEach(b2);
    for (c = 0; c < Qc.length; c++) d2 = Qc[c], d2.blockedOn === a && (d2.blockedOn = null);
    for (; 0 < Qc.length && (c = Qc[0], null === c.blockedOn); ) Vc(c), null === c.blockedOn && Qc.shift();
  }
  var cd = ua.ReactCurrentBatchConfig, dd = true;
  function ed(a, b2, c, d2) {
    var e = C2, f = cd.transition;
    cd.transition = null;
    try {
      C2 = 1, fd(a, b2, c, d2);
    } finally {
      C2 = e, cd.transition = f;
    }
  }
  function gd(a, b2, c, d2) {
    var e = C2, f = cd.transition;
    cd.transition = null;
    try {
      C2 = 4, fd(a, b2, c, d2);
    } finally {
      C2 = e, cd.transition = f;
    }
  }
  function fd(a, b2, c, d2) {
    if (dd) {
      var e = Yc(a, b2, c, d2);
      if (null === e) hd(a, b2, d2, id, c), Sc(a, d2);
      else if (Uc(e, a, b2, c, d2)) d2.stopPropagation();
      else if (Sc(a, d2), b2 & 4 && -1 < Rc.indexOf(a)) {
        for (; null !== e; ) {
          var f = Cb(e);
          null !== f && Ec(f);
          f = Yc(a, b2, c, d2);
          null === f && hd(a, b2, d2, id, c);
          if (f === e) break;
          e = f;
        }
        null !== e && d2.stopPropagation();
      } else hd(a, b2, d2, null, c);
    }
  }
  var id = null;
  function Yc(a, b2, c, d2) {
    id = null;
    a = xb(d2);
    a = Wc(a);
    if (null !== a) if (b2 = Vb(a), null === b2) a = null;
    else if (c = b2.tag, 13 === c) {
      a = Wb(b2);
      if (null !== a) return a;
      a = null;
    } else if (3 === c) {
      if (b2.stateNode.current.memoizedState.isDehydrated) return 3 === b2.tag ? b2.stateNode.containerInfo : null;
      a = null;
    } else b2 !== a && (a = null);
    id = a;
    return null;
  }
  function jd(a) {
    switch (a) {
      case "cancel":
      case "click":
      case "close":
      case "contextmenu":
      case "copy":
      case "cut":
      case "auxclick":
      case "dblclick":
      case "dragend":
      case "dragstart":
      case "drop":
      case "focusin":
      case "focusout":
      case "input":
      case "invalid":
      case "keydown":
      case "keypress":
      case "keyup":
      case "mousedown":
      case "mouseup":
      case "paste":
      case "pause":
      case "play":
      case "pointercancel":
      case "pointerdown":
      case "pointerup":
      case "ratechange":
      case "reset":
      case "resize":
      case "seeked":
      case "submit":
      case "touchcancel":
      case "touchend":
      case "touchstart":
      case "volumechange":
      case "change":
      case "selectionchange":
      case "textInput":
      case "compositionstart":
      case "compositionend":
      case "compositionupdate":
      case "beforeblur":
      case "afterblur":
      case "beforeinput":
      case "blur":
      case "fullscreenchange":
      case "focus":
      case "hashchange":
      case "popstate":
      case "select":
      case "selectstart":
        return 1;
      case "drag":
      case "dragenter":
      case "dragexit":
      case "dragleave":
      case "dragover":
      case "mousemove":
      case "mouseout":
      case "mouseover":
      case "pointermove":
      case "pointerout":
      case "pointerover":
      case "scroll":
      case "toggle":
      case "touchmove":
      case "wheel":
      case "mouseenter":
      case "mouseleave":
      case "pointerenter":
      case "pointerleave":
        return 4;
      case "message":
        switch (ec()) {
          case fc:
            return 1;
          case gc:
            return 4;
          case hc:
          case ic:
            return 16;
          case jc:
            return 536870912;
          default:
            return 16;
        }
      default:
        return 16;
    }
  }
  var kd = null, ld = null, md = null;
  function nd() {
    if (md) return md;
    var a, b2 = ld, c = b2.length, d2, e = "value" in kd ? kd.value : kd.textContent, f = e.length;
    for (a = 0; a < c && b2[a] === e[a]; a++) ;
    var g = c - a;
    for (d2 = 1; d2 <= g && b2[c - d2] === e[f - d2]; d2++) ;
    return md = e.slice(a, 1 < d2 ? 1 - d2 : void 0);
  }
  function od(a) {
    var b2 = a.keyCode;
    "charCode" in a ? (a = a.charCode, 0 === a && 13 === b2 && (a = 13)) : a = b2;
    10 === a && (a = 13);
    return 32 <= a || 13 === a ? a : 0;
  }
  function pd() {
    return true;
  }
  function qd() {
    return false;
  }
  function rd(a) {
    function b2(b3, d2, e, f, g) {
      this._reactName = b3;
      this._targetInst = e;
      this.type = d2;
      this.nativeEvent = f;
      this.target = g;
      this.currentTarget = null;
      for (var c in a) a.hasOwnProperty(c) && (b3 = a[c], this[c] = b3 ? b3(f) : f[c]);
      this.isDefaultPrevented = (null != f.defaultPrevented ? f.defaultPrevented : false === f.returnValue) ? pd : qd;
      this.isPropagationStopped = qd;
      return this;
    }
    A(b2.prototype, { preventDefault: function() {
      this.defaultPrevented = true;
      var a2 = this.nativeEvent;
      a2 && (a2.preventDefault ? a2.preventDefault() : "unknown" !== typeof a2.returnValue && (a2.returnValue = false), this.isDefaultPrevented = pd);
    }, stopPropagation: function() {
      var a2 = this.nativeEvent;
      a2 && (a2.stopPropagation ? a2.stopPropagation() : "unknown" !== typeof a2.cancelBubble && (a2.cancelBubble = true), this.isPropagationStopped = pd);
    }, persist: function() {
    }, isPersistent: pd });
    return b2;
  }
  var sd = { eventPhase: 0, bubbles: 0, cancelable: 0, timeStamp: function(a) {
    return a.timeStamp || Date.now();
  }, defaultPrevented: 0, isTrusted: 0 }, td = rd(sd), ud = A({}, sd, { view: 0, detail: 0 }), vd = rd(ud), wd, xd, yd, Ad = A({}, ud, { screenX: 0, screenY: 0, clientX: 0, clientY: 0, pageX: 0, pageY: 0, ctrlKey: 0, shiftKey: 0, altKey: 0, metaKey: 0, getModifierState: zd, button: 0, buttons: 0, relatedTarget: function(a) {
    return void 0 === a.relatedTarget ? a.fromElement === a.srcElement ? a.toElement : a.fromElement : a.relatedTarget;
  }, movementX: function(a) {
    if ("movementX" in a) return a.movementX;
    a !== yd && (yd && "mousemove" === a.type ? (wd = a.screenX - yd.screenX, xd = a.screenY - yd.screenY) : xd = wd = 0, yd = a);
    return wd;
  }, movementY: function(a) {
    return "movementY" in a ? a.movementY : xd;
  } }), Bd = rd(Ad), Cd = A({}, Ad, { dataTransfer: 0 }), Dd = rd(Cd), Ed = A({}, ud, { relatedTarget: 0 }), Fd = rd(Ed), Gd = A({}, sd, { animationName: 0, elapsedTime: 0, pseudoElement: 0 }), Hd = rd(Gd), Id = A({}, sd, { clipboardData: function(a) {
    return "clipboardData" in a ? a.clipboardData : window.clipboardData;
  } }), Jd = rd(Id), Kd = A({}, sd, { data: 0 }), Ld = rd(Kd), Md = {
    Esc: "Escape",
    Spacebar: " ",
    Left: "ArrowLeft",
    Up: "ArrowUp",
    Right: "ArrowRight",
    Down: "ArrowDown",
    Del: "Delete",
    Win: "OS",
    Menu: "ContextMenu",
    Apps: "ContextMenu",
    Scroll: "ScrollLock",
    MozPrintableKey: "Unidentified"
  }, Nd = {
    8: "Backspace",
    9: "Tab",
    12: "Clear",
    13: "Enter",
    16: "Shift",
    17: "Control",
    18: "Alt",
    19: "Pause",
    20: "CapsLock",
    27: "Escape",
    32: " ",
    33: "PageUp",
    34: "PageDown",
    35: "End",
    36: "Home",
    37: "ArrowLeft",
    38: "ArrowUp",
    39: "ArrowRight",
    40: "ArrowDown",
    45: "Insert",
    46: "Delete",
    112: "F1",
    113: "F2",
    114: "F3",
    115: "F4",
    116: "F5",
    117: "F6",
    118: "F7",
    119: "F8",
    120: "F9",
    121: "F10",
    122: "F11",
    123: "F12",
    144: "NumLock",
    145: "ScrollLock",
    224: "Meta"
  }, Od = { Alt: "altKey", Control: "ctrlKey", Meta: "metaKey", Shift: "shiftKey" };
  function Pd(a) {
    var b2 = this.nativeEvent;
    return b2.getModifierState ? b2.getModifierState(a) : (a = Od[a]) ? !!b2[a] : false;
  }
  function zd() {
    return Pd;
  }
  var Qd = A({}, ud, { key: function(a) {
    if (a.key) {
      var b2 = Md[a.key] || a.key;
      if ("Unidentified" !== b2) return b2;
    }
    return "keypress" === a.type ? (a = od(a), 13 === a ? "Enter" : String.fromCharCode(a)) : "keydown" === a.type || "keyup" === a.type ? Nd[a.keyCode] || "Unidentified" : "";
  }, code: 0, location: 0, ctrlKey: 0, shiftKey: 0, altKey: 0, metaKey: 0, repeat: 0, locale: 0, getModifierState: zd, charCode: function(a) {
    return "keypress" === a.type ? od(a) : 0;
  }, keyCode: function(a) {
    return "keydown" === a.type || "keyup" === a.type ? a.keyCode : 0;
  }, which: function(a) {
    return "keypress" === a.type ? od(a) : "keydown" === a.type || "keyup" === a.type ? a.keyCode : 0;
  } }), Rd = rd(Qd), Sd = A({}, Ad, { pointerId: 0, width: 0, height: 0, pressure: 0, tangentialPressure: 0, tiltX: 0, tiltY: 0, twist: 0, pointerType: 0, isPrimary: 0 }), Td = rd(Sd), Ud = A({}, ud, { touches: 0, targetTouches: 0, changedTouches: 0, altKey: 0, metaKey: 0, ctrlKey: 0, shiftKey: 0, getModifierState: zd }), Vd = rd(Ud), Wd = A({}, sd, { propertyName: 0, elapsedTime: 0, pseudoElement: 0 }), Xd = rd(Wd), Yd = A({}, Ad, {
    deltaX: function(a) {
      return "deltaX" in a ? a.deltaX : "wheelDeltaX" in a ? -a.wheelDeltaX : 0;
    },
    deltaY: function(a) {
      return "deltaY" in a ? a.deltaY : "wheelDeltaY" in a ? -a.wheelDeltaY : "wheelDelta" in a ? -a.wheelDelta : 0;
    },
    deltaZ: 0,
    deltaMode: 0
  }), Zd = rd(Yd), $d = [9, 13, 27, 32], ae2 = ia && "CompositionEvent" in window, be2 = null;
  ia && "documentMode" in document && (be2 = document.documentMode);
  var ce2 = ia && "TextEvent" in window && !be2, de2 = ia && (!ae2 || be2 && 8 < be2 && 11 >= be2), ee = String.fromCharCode(32), fe2 = false;
  function ge2(a, b2) {
    switch (a) {
      case "keyup":
        return -1 !== $d.indexOf(b2.keyCode);
      case "keydown":
        return 229 !== b2.keyCode;
      case "keypress":
      case "mousedown":
      case "focusout":
        return true;
      default:
        return false;
    }
  }
  function he2(a) {
    a = a.detail;
    return "object" === typeof a && "data" in a ? a.data : null;
  }
  var ie2 = false;
  function je2(a, b2) {
    switch (a) {
      case "compositionend":
        return he2(b2);
      case "keypress":
        if (32 !== b2.which) return null;
        fe2 = true;
        return ee;
      case "textInput":
        return a = b2.data, a === ee && fe2 ? null : a;
      default:
        return null;
    }
  }
  function ke2(a, b2) {
    if (ie2) return "compositionend" === a || !ae2 && ge2(a, b2) ? (a = nd(), md = ld = kd = null, ie2 = false, a) : null;
    switch (a) {
      case "paste":
        return null;
      case "keypress":
        if (!(b2.ctrlKey || b2.altKey || b2.metaKey) || b2.ctrlKey && b2.altKey) {
          if (b2.char && 1 < b2.char.length) return b2.char;
          if (b2.which) return String.fromCharCode(b2.which);
        }
        return null;
      case "compositionend":
        return de2 && "ko" !== b2.locale ? null : b2.data;
      default:
        return null;
    }
  }
  var le2 = { color: true, date: true, datetime: true, "datetime-local": true, email: true, month: true, number: true, password: true, range: true, search: true, tel: true, text: true, time: true, url: true, week: true };
  function me2(a) {
    var b2 = a && a.nodeName && a.nodeName.toLowerCase();
    return "input" === b2 ? !!le2[a.type] : "textarea" === b2 ? true : false;
  }
  function ne(a, b2, c, d2) {
    Eb(d2);
    b2 = oe2(b2, "onChange");
    0 < b2.length && (c = new td("onChange", "change", null, c, d2), a.push({ event: c, listeners: b2 }));
  }
  var pe2 = null, qe2 = null;
  function re2(a) {
    se2(a, 0);
  }
  function te(a) {
    var b2 = ue2(a);
    if (Wa(b2)) return a;
  }
  function ve2(a, b2) {
    if ("change" === a) return b2;
  }
  var we2 = false;
  if (ia) {
    var xe;
    if (ia) {
      var ye2 = "oninput" in document;
      if (!ye2) {
        var ze2 = document.createElement("div");
        ze2.setAttribute("oninput", "return;");
        ye2 = "function" === typeof ze2.oninput;
      }
      xe = ye2;
    } else xe = false;
    we2 = xe && (!document.documentMode || 9 < document.documentMode);
  }
  function Ae2() {
    pe2 && (pe2.detachEvent("onpropertychange", Be2), qe2 = pe2 = null);
  }
  function Be2(a) {
    if ("value" === a.propertyName && te(qe2)) {
      var b2 = [];
      ne(b2, qe2, a, xb(a));
      Jb(re2, b2);
    }
  }
  function Ce2(a, b2, c) {
    "focusin" === a ? (Ae2(), pe2 = b2, qe2 = c, pe2.attachEvent("onpropertychange", Be2)) : "focusout" === a && Ae2();
  }
  function De2(a) {
    if ("selectionchange" === a || "keyup" === a || "keydown" === a) return te(qe2);
  }
  function Ee2(a, b2) {
    if ("click" === a) return te(b2);
  }
  function Fe2(a, b2) {
    if ("input" === a || "change" === a) return te(b2);
  }
  function Ge2(a, b2) {
    return a === b2 && (0 !== a || 1 / a === 1 / b2) || a !== a && b2 !== b2;
  }
  var He2 = "function" === typeof Object.is ? Object.is : Ge2;
  function Ie2(a, b2) {
    if (He2(a, b2)) return true;
    if ("object" !== typeof a || null === a || "object" !== typeof b2 || null === b2) return false;
    var c = Object.keys(a), d2 = Object.keys(b2);
    if (c.length !== d2.length) return false;
    for (d2 = 0; d2 < c.length; d2++) {
      var e = c[d2];
      if (!ja.call(b2, e) || !He2(a[e], b2[e])) return false;
    }
    return true;
  }
  function Je2(a) {
    for (; a && a.firstChild; ) a = a.firstChild;
    return a;
  }
  function Ke2(a, b2) {
    var c = Je2(a);
    a = 0;
    for (var d2; c; ) {
      if (3 === c.nodeType) {
        d2 = a + c.textContent.length;
        if (a <= b2 && d2 >= b2) return { node: c, offset: b2 - a };
        a = d2;
      }
      a: {
        for (; c; ) {
          if (c.nextSibling) {
            c = c.nextSibling;
            break a;
          }
          c = c.parentNode;
        }
        c = void 0;
      }
      c = Je2(c);
    }
  }
  function Le2(a, b2) {
    return a && b2 ? a === b2 ? true : a && 3 === a.nodeType ? false : b2 && 3 === b2.nodeType ? Le2(a, b2.parentNode) : "contains" in a ? a.contains(b2) : a.compareDocumentPosition ? !!(a.compareDocumentPosition(b2) & 16) : false : false;
  }
  function Me2() {
    for (var a = window, b2 = Xa(); b2 instanceof a.HTMLIFrameElement; ) {
      try {
        var c = "string" === typeof b2.contentWindow.location.href;
      } catch (d2) {
        c = false;
      }
      if (c) a = b2.contentWindow;
      else break;
      b2 = Xa(a.document);
    }
    return b2;
  }
  function Ne2(a) {
    var b2 = a && a.nodeName && a.nodeName.toLowerCase();
    return b2 && ("input" === b2 && ("text" === a.type || "search" === a.type || "tel" === a.type || "url" === a.type || "password" === a.type) || "textarea" === b2 || "true" === a.contentEditable);
  }
  function Oe2(a) {
    var b2 = Me2(), c = a.focusedElem, d2 = a.selectionRange;
    if (b2 !== c && c && c.ownerDocument && Le2(c.ownerDocument.documentElement, c)) {
      if (null !== d2 && Ne2(c)) {
        if (b2 = d2.start, a = d2.end, void 0 === a && (a = b2), "selectionStart" in c) c.selectionStart = b2, c.selectionEnd = Math.min(a, c.value.length);
        else if (a = (b2 = c.ownerDocument || document) && b2.defaultView || window, a.getSelection) {
          a = a.getSelection();
          var e = c.textContent.length, f = Math.min(d2.start, e);
          d2 = void 0 === d2.end ? f : Math.min(d2.end, e);
          !a.extend && f > d2 && (e = d2, d2 = f, f = e);
          e = Ke2(c, f);
          var g = Ke2(
            c,
            d2
          );
          e && g && (1 !== a.rangeCount || a.anchorNode !== e.node || a.anchorOffset !== e.offset || a.focusNode !== g.node || a.focusOffset !== g.offset) && (b2 = b2.createRange(), b2.setStart(e.node, e.offset), a.removeAllRanges(), f > d2 ? (a.addRange(b2), a.extend(g.node, g.offset)) : (b2.setEnd(g.node, g.offset), a.addRange(b2)));
        }
      }
      b2 = [];
      for (a = c; a = a.parentNode; ) 1 === a.nodeType && b2.push({ element: a, left: a.scrollLeft, top: a.scrollTop });
      "function" === typeof c.focus && c.focus();
      for (c = 0; c < b2.length; c++) a = b2[c], a.element.scrollLeft = a.left, a.element.scrollTop = a.top;
    }
  }
  var Pe2 = ia && "documentMode" in document && 11 >= document.documentMode, Qe2 = null, Re2 = null, Se2 = null, Te2 = false;
  function Ue2(a, b2, c) {
    var d2 = c.window === c ? c.document : 9 === c.nodeType ? c : c.ownerDocument;
    Te2 || null == Qe2 || Qe2 !== Xa(d2) || (d2 = Qe2, "selectionStart" in d2 && Ne2(d2) ? d2 = { start: d2.selectionStart, end: d2.selectionEnd } : (d2 = (d2.ownerDocument && d2.ownerDocument.defaultView || window).getSelection(), d2 = { anchorNode: d2.anchorNode, anchorOffset: d2.anchorOffset, focusNode: d2.focusNode, focusOffset: d2.focusOffset }), Se2 && Ie2(Se2, d2) || (Se2 = d2, d2 = oe2(Re2, "onSelect"), 0 < d2.length && (b2 = new td("onSelect", "select", null, b2, c), a.push({ event: b2, listeners: d2 }), b2.target = Qe2)));
  }
  function Ve2(a, b2) {
    var c = {};
    c[a.toLowerCase()] = b2.toLowerCase();
    c["Webkit" + a] = "webkit" + b2;
    c["Moz" + a] = "moz" + b2;
    return c;
  }
  var We2 = { animationend: Ve2("Animation", "AnimationEnd"), animationiteration: Ve2("Animation", "AnimationIteration"), animationstart: Ve2("Animation", "AnimationStart"), transitionend: Ve2("Transition", "TransitionEnd") }, Xe2 = {}, Ye = {};
  ia && (Ye = document.createElement("div").style, "AnimationEvent" in window || (delete We2.animationend.animation, delete We2.animationiteration.animation, delete We2.animationstart.animation), "TransitionEvent" in window || delete We2.transitionend.transition);
  function Ze2(a) {
    if (Xe2[a]) return Xe2[a];
    if (!We2[a]) return a;
    var b2 = We2[a], c;
    for (c in b2) if (b2.hasOwnProperty(c) && c in Ye) return Xe2[a] = b2[c];
    return a;
  }
  var $e2 = Ze2("animationend"), af = Ze2("animationiteration"), bf = Ze2("animationstart"), cf = Ze2("transitionend"), df = /* @__PURE__ */ new Map(), ef = "abort auxClick cancel canPlay canPlayThrough click close contextMenu copy cut drag dragEnd dragEnter dragExit dragLeave dragOver dragStart drop durationChange emptied encrypted ended error gotPointerCapture input invalid keyDown keyPress keyUp load loadedData loadedMetadata loadStart lostPointerCapture mouseDown mouseMove mouseOut mouseOver mouseUp paste pause play playing pointerCancel pointerDown pointerMove pointerOut pointerOver pointerUp progress rateChange reset resize seeked seeking stalled submit suspend timeUpdate touchCancel touchEnd touchStart volumeChange scroll toggle touchMove waiting wheel".split(" ");
  function ff(a, b2) {
    df.set(a, b2);
    fa(b2, [a]);
  }
  for (var gf = 0; gf < ef.length; gf++) {
    var hf = ef[gf], jf = hf.toLowerCase(), kf = hf[0].toUpperCase() + hf.slice(1);
    ff(jf, "on" + kf);
  }
  ff($e2, "onAnimationEnd");
  ff(af, "onAnimationIteration");
  ff(bf, "onAnimationStart");
  ff("dblclick", "onDoubleClick");
  ff("focusin", "onFocus");
  ff("focusout", "onBlur");
  ff(cf, "onTransitionEnd");
  ha("onMouseEnter", ["mouseout", "mouseover"]);
  ha("onMouseLeave", ["mouseout", "mouseover"]);
  ha("onPointerEnter", ["pointerout", "pointerover"]);
  ha("onPointerLeave", ["pointerout", "pointerover"]);
  fa("onChange", "change click focusin focusout input keydown keyup selectionchange".split(" "));
  fa("onSelect", "focusout contextmenu dragend focusin keydown keyup mousedown mouseup selectionchange".split(" "));
  fa("onBeforeInput", ["compositionend", "keypress", "textInput", "paste"]);
  fa("onCompositionEnd", "compositionend focusout keydown keypress keyup mousedown".split(" "));
  fa("onCompositionStart", "compositionstart focusout keydown keypress keyup mousedown".split(" "));
  fa("onCompositionUpdate", "compositionupdate focusout keydown keypress keyup mousedown".split(" "));
  var lf = "abort canplay canplaythrough durationchange emptied encrypted ended error loadeddata loadedmetadata loadstart pause play playing progress ratechange resize seeked seeking stalled suspend timeupdate volumechange waiting".split(" "), mf = new Set("cancel close invalid load scroll toggle".split(" ").concat(lf));
  function nf(a, b2, c) {
    var d2 = a.type || "unknown-event";
    a.currentTarget = c;
    Ub(d2, b2, void 0, a);
    a.currentTarget = null;
  }
  function se2(a, b2) {
    b2 = 0 !== (b2 & 4);
    for (var c = 0; c < a.length; c++) {
      var d2 = a[c], e = d2.event;
      d2 = d2.listeners;
      a: {
        var f = void 0;
        if (b2) for (var g = d2.length - 1; 0 <= g; g--) {
          var h = d2[g], k2 = h.instance, l = h.currentTarget;
          h = h.listener;
          if (k2 !== f && e.isPropagationStopped()) break a;
          nf(e, h, l);
          f = k2;
        }
        else for (g = 0; g < d2.length; g++) {
          h = d2[g];
          k2 = h.instance;
          l = h.currentTarget;
          h = h.listener;
          if (k2 !== f && e.isPropagationStopped()) break a;
          nf(e, h, l);
          f = k2;
        }
      }
    }
    if (Qb) throw a = Rb, Qb = false, Rb = null, a;
  }
  function D2(a, b2) {
    var c = b2[of];
    void 0 === c && (c = b2[of] = /* @__PURE__ */ new Set());
    var d2 = a + "__bubble";
    c.has(d2) || (pf(b2, a, 2, false), c.add(d2));
  }
  function qf(a, b2, c) {
    var d2 = 0;
    b2 && (d2 |= 4);
    pf(c, a, d2, b2);
  }
  var rf = "_reactListening" + Math.random().toString(36).slice(2);
  function sf(a) {
    if (!a[rf]) {
      a[rf] = true;
      da.forEach(function(b3) {
        "selectionchange" !== b3 && (mf.has(b3) || qf(b3, false, a), qf(b3, true, a));
      });
      var b2 = 9 === a.nodeType ? a : a.ownerDocument;
      null === b2 || b2[rf] || (b2[rf] = true, qf("selectionchange", false, b2));
    }
  }
  function pf(a, b2, c, d2) {
    switch (jd(b2)) {
      case 1:
        var e = ed;
        break;
      case 4:
        e = gd;
        break;
      default:
        e = fd;
    }
    c = e.bind(null, b2, c, a);
    e = void 0;
    !Lb || "touchstart" !== b2 && "touchmove" !== b2 && "wheel" !== b2 || (e = true);
    d2 ? void 0 !== e ? a.addEventListener(b2, c, { capture: true, passive: e }) : a.addEventListener(b2, c, true) : void 0 !== e ? a.addEventListener(b2, c, { passive: e }) : a.addEventListener(b2, c, false);
  }
  function hd(a, b2, c, d2, e) {
    var f = d2;
    if (0 === (b2 & 1) && 0 === (b2 & 2) && null !== d2) a: for (; ; ) {
      if (null === d2) return;
      var g = d2.tag;
      if (3 === g || 4 === g) {
        var h = d2.stateNode.containerInfo;
        if (h === e || 8 === h.nodeType && h.parentNode === e) break;
        if (4 === g) for (g = d2.return; null !== g; ) {
          var k2 = g.tag;
          if (3 === k2 || 4 === k2) {
            if (k2 = g.stateNode.containerInfo, k2 === e || 8 === k2.nodeType && k2.parentNode === e) return;
          }
          g = g.return;
        }
        for (; null !== h; ) {
          g = Wc(h);
          if (null === g) return;
          k2 = g.tag;
          if (5 === k2 || 6 === k2) {
            d2 = f = g;
            continue a;
          }
          h = h.parentNode;
        }
      }
      d2 = d2.return;
    }
    Jb(function() {
      var d3 = f, e2 = xb(c), g2 = [];
      a: {
        var h2 = df.get(a);
        if (void 0 !== h2) {
          var k3 = td, n = a;
          switch (a) {
            case "keypress":
              if (0 === od(c)) break a;
            case "keydown":
            case "keyup":
              k3 = Rd;
              break;
            case "focusin":
              n = "focus";
              k3 = Fd;
              break;
            case "focusout":
              n = "blur";
              k3 = Fd;
              break;
            case "beforeblur":
            case "afterblur":
              k3 = Fd;
              break;
            case "click":
              if (2 === c.button) break a;
            case "auxclick":
            case "dblclick":
            case "mousedown":
            case "mousemove":
            case "mouseup":
            case "mouseout":
            case "mouseover":
            case "contextmenu":
              k3 = Bd;
              break;
            case "drag":
            case "dragend":
            case "dragenter":
            case "dragexit":
            case "dragleave":
            case "dragover":
            case "dragstart":
            case "drop":
              k3 = Dd;
              break;
            case "touchcancel":
            case "touchend":
            case "touchmove":
            case "touchstart":
              k3 = Vd;
              break;
            case $e2:
            case af:
            case bf:
              k3 = Hd;
              break;
            case cf:
              k3 = Xd;
              break;
            case "scroll":
              k3 = vd;
              break;
            case "wheel":
              k3 = Zd;
              break;
            case "copy":
            case "cut":
            case "paste":
              k3 = Jd;
              break;
            case "gotpointercapture":
            case "lostpointercapture":
            case "pointercancel":
            case "pointerdown":
            case "pointermove":
            case "pointerout":
            case "pointerover":
            case "pointerup":
              k3 = Td;
          }
          var t = 0 !== (b2 & 4), J2 = !t && "scroll" === a, x2 = t ? null !== h2 ? h2 + "Capture" : null : h2;
          t = [];
          for (var w2 = d3, u3; null !== w2; ) {
            u3 = w2;
            var F2 = u3.stateNode;
            5 === u3.tag && null !== F2 && (u3 = F2, null !== x2 && (F2 = Kb(w2, x2), null != F2 && t.push(tf(w2, F2, u3))));
            if (J2) break;
            w2 = w2.return;
          }
          0 < t.length && (h2 = new k3(h2, n, null, c, e2), g2.push({ event: h2, listeners: t }));
        }
      }
      if (0 === (b2 & 7)) {
        a: {
          h2 = "mouseover" === a || "pointerover" === a;
          k3 = "mouseout" === a || "pointerout" === a;
          if (h2 && c !== wb && (n = c.relatedTarget || c.fromElement) && (Wc(n) || n[uf])) break a;
          if (k3 || h2) {
            h2 = e2.window === e2 ? e2 : (h2 = e2.ownerDocument) ? h2.defaultView || h2.parentWindow : window;
            if (k3) {
              if (n = c.relatedTarget || c.toElement, k3 = d3, n = n ? Wc(n) : null, null !== n && (J2 = Vb(n), n !== J2 || 5 !== n.tag && 6 !== n.tag)) n = null;
            } else k3 = null, n = d3;
            if (k3 !== n) {
              t = Bd;
              F2 = "onMouseLeave";
              x2 = "onMouseEnter";
              w2 = "mouse";
              if ("pointerout" === a || "pointerover" === a) t = Td, F2 = "onPointerLeave", x2 = "onPointerEnter", w2 = "pointer";
              J2 = null == k3 ? h2 : ue2(k3);
              u3 = null == n ? h2 : ue2(n);
              h2 = new t(F2, w2 + "leave", k3, c, e2);
              h2.target = J2;
              h2.relatedTarget = u3;
              F2 = null;
              Wc(e2) === d3 && (t = new t(x2, w2 + "enter", n, c, e2), t.target = u3, t.relatedTarget = J2, F2 = t);
              J2 = F2;
              if (k3 && n) b: {
                t = k3;
                x2 = n;
                w2 = 0;
                for (u3 = t; u3; u3 = vf(u3)) w2++;
                u3 = 0;
                for (F2 = x2; F2; F2 = vf(F2)) u3++;
                for (; 0 < w2 - u3; ) t = vf(t), w2--;
                for (; 0 < u3 - w2; ) x2 = vf(x2), u3--;
                for (; w2--; ) {
                  if (t === x2 || null !== x2 && t === x2.alternate) break b;
                  t = vf(t);
                  x2 = vf(x2);
                }
                t = null;
              }
              else t = null;
              null !== k3 && wf(g2, h2, k3, t, false);
              null !== n && null !== J2 && wf(g2, J2, n, t, true);
            }
          }
        }
        a: {
          h2 = d3 ? ue2(d3) : window;
          k3 = h2.nodeName && h2.nodeName.toLowerCase();
          if ("select" === k3 || "input" === k3 && "file" === h2.type) var na = ve2;
          else if (me2(h2)) if (we2) na = Fe2;
          else {
            na = De2;
            var xa = Ce2;
          }
          else (k3 = h2.nodeName) && "input" === k3.toLowerCase() && ("checkbox" === h2.type || "radio" === h2.type) && (na = Ee2);
          if (na && (na = na(a, d3))) {
            ne(g2, na, c, e2);
            break a;
          }
          xa && xa(a, h2, d3);
          "focusout" === a && (xa = h2._wrapperState) && xa.controlled && "number" === h2.type && cb(h2, "number", h2.value);
        }
        xa = d3 ? ue2(d3) : window;
        switch (a) {
          case "focusin":
            if (me2(xa) || "true" === xa.contentEditable) Qe2 = xa, Re2 = d3, Se2 = null;
            break;
          case "focusout":
            Se2 = Re2 = Qe2 = null;
            break;
          case "mousedown":
            Te2 = true;
            break;
          case "contextmenu":
          case "mouseup":
          case "dragend":
            Te2 = false;
            Ue2(g2, c, e2);
            break;
          case "selectionchange":
            if (Pe2) break;
          case "keydown":
          case "keyup":
            Ue2(g2, c, e2);
        }
        var $a;
        if (ae2) b: {
          switch (a) {
            case "compositionstart":
              var ba = "onCompositionStart";
              break b;
            case "compositionend":
              ba = "onCompositionEnd";
              break b;
            case "compositionupdate":
              ba = "onCompositionUpdate";
              break b;
          }
          ba = void 0;
        }
        else ie2 ? ge2(a, c) && (ba = "onCompositionEnd") : "keydown" === a && 229 === c.keyCode && (ba = "onCompositionStart");
        ba && (de2 && "ko" !== c.locale && (ie2 || "onCompositionStart" !== ba ? "onCompositionEnd" === ba && ie2 && ($a = nd()) : (kd = e2, ld = "value" in kd ? kd.value : kd.textContent, ie2 = true)), xa = oe2(d3, ba), 0 < xa.length && (ba = new Ld(ba, a, null, c, e2), g2.push({ event: ba, listeners: xa }), $a ? ba.data = $a : ($a = he2(c), null !== $a && (ba.data = $a))));
        if ($a = ce2 ? je2(a, c) : ke2(a, c)) d3 = oe2(d3, "onBeforeInput"), 0 < d3.length && (e2 = new Ld("onBeforeInput", "beforeinput", null, c, e2), g2.push({ event: e2, listeners: d3 }), e2.data = $a);
      }
      se2(g2, b2);
    });
  }
  function tf(a, b2, c) {
    return { instance: a, listener: b2, currentTarget: c };
  }
  function oe2(a, b2) {
    for (var c = b2 + "Capture", d2 = []; null !== a; ) {
      var e = a, f = e.stateNode;
      5 === e.tag && null !== f && (e = f, f = Kb(a, c), null != f && d2.unshift(tf(a, f, e)), f = Kb(a, b2), null != f && d2.push(tf(a, f, e)));
      a = a.return;
    }
    return d2;
  }
  function vf(a) {
    if (null === a) return null;
    do
      a = a.return;
    while (a && 5 !== a.tag);
    return a ? a : null;
  }
  function wf(a, b2, c, d2, e) {
    for (var f = b2._reactName, g = []; null !== c && c !== d2; ) {
      var h = c, k2 = h.alternate, l = h.stateNode;
      if (null !== k2 && k2 === d2) break;
      5 === h.tag && null !== l && (h = l, e ? (k2 = Kb(c, f), null != k2 && g.unshift(tf(c, k2, h))) : e || (k2 = Kb(c, f), null != k2 && g.push(tf(c, k2, h))));
      c = c.return;
    }
    0 !== g.length && a.push({ event: b2, listeners: g });
  }
  var xf = /\r\n?/g, yf = /\u0000|\uFFFD/g;
  function zf(a) {
    return ("string" === typeof a ? a : "" + a).replace(xf, "\n").replace(yf, "");
  }
  function Af(a, b2, c) {
    b2 = zf(b2);
    if (zf(a) !== b2 && c) throw Error(p(425));
  }
  function Bf() {
  }
  var Cf = null, Df = null;
  function Ef(a, b2) {
    return "textarea" === a || "noscript" === a || "string" === typeof b2.children || "number" === typeof b2.children || "object" === typeof b2.dangerouslySetInnerHTML && null !== b2.dangerouslySetInnerHTML && null != b2.dangerouslySetInnerHTML.__html;
  }
  var Ff = "function" === typeof setTimeout ? setTimeout : void 0, Gf = "function" === typeof clearTimeout ? clearTimeout : void 0, Hf = "function" === typeof Promise ? Promise : void 0, Jf = "function" === typeof queueMicrotask ? queueMicrotask : "undefined" !== typeof Hf ? function(a) {
    return Hf.resolve(null).then(a).catch(If);
  } : Ff;
  function If(a) {
    setTimeout(function() {
      throw a;
    });
  }
  function Kf(a, b2) {
    var c = b2, d2 = 0;
    do {
      var e = c.nextSibling;
      a.removeChild(c);
      if (e && 8 === e.nodeType) if (c = e.data, "/$" === c) {
        if (0 === d2) {
          a.removeChild(e);
          bd(b2);
          return;
        }
        d2--;
      } else "$" !== c && "$?" !== c && "$!" !== c || d2++;
      c = e;
    } while (c);
    bd(b2);
  }
  function Lf(a) {
    for (; null != a; a = a.nextSibling) {
      var b2 = a.nodeType;
      if (1 === b2 || 3 === b2) break;
      if (8 === b2) {
        b2 = a.data;
        if ("$" === b2 || "$!" === b2 || "$?" === b2) break;
        if ("/$" === b2) return null;
      }
    }
    return a;
  }
  function Mf(a) {
    a = a.previousSibling;
    for (var b2 = 0; a; ) {
      if (8 === a.nodeType) {
        var c = a.data;
        if ("$" === c || "$!" === c || "$?" === c) {
          if (0 === b2) return a;
          b2--;
        } else "/$" === c && b2++;
      }
      a = a.previousSibling;
    }
    return null;
  }
  var Nf = Math.random().toString(36).slice(2), Of = "__reactFiber$" + Nf, Pf = "__reactProps$" + Nf, uf = "__reactContainer$" + Nf, of = "__reactEvents$" + Nf, Qf = "__reactListeners$" + Nf, Rf = "__reactHandles$" + Nf;
  function Wc(a) {
    var b2 = a[Of];
    if (b2) return b2;
    for (var c = a.parentNode; c; ) {
      if (b2 = c[uf] || c[Of]) {
        c = b2.alternate;
        if (null !== b2.child || null !== c && null !== c.child) for (a = Mf(a); null !== a; ) {
          if (c = a[Of]) return c;
          a = Mf(a);
        }
        return b2;
      }
      a = c;
      c = a.parentNode;
    }
    return null;
  }
  function Cb(a) {
    a = a[Of] || a[uf];
    return !a || 5 !== a.tag && 6 !== a.tag && 13 !== a.tag && 3 !== a.tag ? null : a;
  }
  function ue2(a) {
    if (5 === a.tag || 6 === a.tag) return a.stateNode;
    throw Error(p(33));
  }
  function Db(a) {
    return a[Pf] || null;
  }
  var Sf = [], Tf = -1;
  function Uf(a) {
    return { current: a };
  }
  function E2(a) {
    0 > Tf || (a.current = Sf[Tf], Sf[Tf] = null, Tf--);
  }
  function G2(a, b2) {
    Tf++;
    Sf[Tf] = a.current;
    a.current = b2;
  }
  var Vf = {}, H = Uf(Vf), Wf = Uf(false), Xf = Vf;
  function Yf(a, b2) {
    var c = a.type.contextTypes;
    if (!c) return Vf;
    var d2 = a.stateNode;
    if (d2 && d2.__reactInternalMemoizedUnmaskedChildContext === b2) return d2.__reactInternalMemoizedMaskedChildContext;
    var e = {}, f;
    for (f in c) e[f] = b2[f];
    d2 && (a = a.stateNode, a.__reactInternalMemoizedUnmaskedChildContext = b2, a.__reactInternalMemoizedMaskedChildContext = e);
    return e;
  }
  function Zf(a) {
    a = a.childContextTypes;
    return null !== a && void 0 !== a;
  }
  function $f() {
    E2(Wf);
    E2(H);
  }
  function ag(a, b2, c) {
    if (H.current !== Vf) throw Error(p(168));
    G2(H, b2);
    G2(Wf, c);
  }
  function bg(a, b2, c) {
    var d2 = a.stateNode;
    b2 = b2.childContextTypes;
    if ("function" !== typeof d2.getChildContext) return c;
    d2 = d2.getChildContext();
    for (var e in d2) if (!(e in b2)) throw Error(p(108, Ra(a) || "Unknown", e));
    return A({}, c, d2);
  }
  function cg(a) {
    a = (a = a.stateNode) && a.__reactInternalMemoizedMergedChildContext || Vf;
    Xf = H.current;
    G2(H, a);
    G2(Wf, Wf.current);
    return true;
  }
  function dg(a, b2, c) {
    var d2 = a.stateNode;
    if (!d2) throw Error(p(169));
    c ? (a = bg(a, b2, Xf), d2.__reactInternalMemoizedMergedChildContext = a, E2(Wf), E2(H), G2(H, a)) : E2(Wf);
    G2(Wf, c);
  }
  var eg = null, fg = false, gg = false;
  function hg(a) {
    null === eg ? eg = [a] : eg.push(a);
  }
  function ig(a) {
    fg = true;
    hg(a);
  }
  function jg() {
    if (!gg && null !== eg) {
      gg = true;
      var a = 0, b2 = C2;
      try {
        var c = eg;
        for (C2 = 1; a < c.length; a++) {
          var d2 = c[a];
          do
            d2 = d2(true);
          while (null !== d2);
        }
        eg = null;
        fg = false;
      } catch (e) {
        throw null !== eg && (eg = eg.slice(a + 1)), ac(fc, jg), e;
      } finally {
        C2 = b2, gg = false;
      }
    }
    return null;
  }
  var kg = [], lg = 0, mg = null, ng = 0, og = [], pg = 0, qg = null, rg = 1, sg = "";
  function tg(a, b2) {
    kg[lg++] = ng;
    kg[lg++] = mg;
    mg = a;
    ng = b2;
  }
  function ug(a, b2, c) {
    og[pg++] = rg;
    og[pg++] = sg;
    og[pg++] = qg;
    qg = a;
    var d2 = rg;
    a = sg;
    var e = 32 - oc(d2) - 1;
    d2 &= ~(1 << e);
    c += 1;
    var f = 32 - oc(b2) + e;
    if (30 < f) {
      var g = e - e % 5;
      f = (d2 & (1 << g) - 1).toString(32);
      d2 >>= g;
      e -= g;
      rg = 1 << 32 - oc(b2) + e | c << e | d2;
      sg = f + a;
    } else rg = 1 << f | c << e | d2, sg = a;
  }
  function vg(a) {
    null !== a.return && (tg(a, 1), ug(a, 1, 0));
  }
  function wg(a) {
    for (; a === mg; ) mg = kg[--lg], kg[lg] = null, ng = kg[--lg], kg[lg] = null;
    for (; a === qg; ) qg = og[--pg], og[pg] = null, sg = og[--pg], og[pg] = null, rg = og[--pg], og[pg] = null;
  }
  var xg = null, yg = null, I2 = false, zg = null;
  function Ag(a, b2) {
    var c = Bg(5, null, null, 0);
    c.elementType = "DELETED";
    c.stateNode = b2;
    c.return = a;
    b2 = a.deletions;
    null === b2 ? (a.deletions = [c], a.flags |= 16) : b2.push(c);
  }
  function Cg(a, b2) {
    switch (a.tag) {
      case 5:
        var c = a.type;
        b2 = 1 !== b2.nodeType || c.toLowerCase() !== b2.nodeName.toLowerCase() ? null : b2;
        return null !== b2 ? (a.stateNode = b2, xg = a, yg = Lf(b2.firstChild), true) : false;
      case 6:
        return b2 = "" === a.pendingProps || 3 !== b2.nodeType ? null : b2, null !== b2 ? (a.stateNode = b2, xg = a, yg = null, true) : false;
      case 13:
        return b2 = 8 !== b2.nodeType ? null : b2, null !== b2 ? (c = null !== qg ? { id: rg, overflow: sg } : null, a.memoizedState = { dehydrated: b2, treeContext: c, retryLane: 1073741824 }, c = Bg(18, null, null, 0), c.stateNode = b2, c.return = a, a.child = c, xg = a, yg = null, true) : false;
      default:
        return false;
    }
  }
  function Dg(a) {
    return 0 !== (a.mode & 1) && 0 === (a.flags & 128);
  }
  function Eg(a) {
    if (I2) {
      var b2 = yg;
      if (b2) {
        var c = b2;
        if (!Cg(a, b2)) {
          if (Dg(a)) throw Error(p(418));
          b2 = Lf(c.nextSibling);
          var d2 = xg;
          b2 && Cg(a, b2) ? Ag(d2, c) : (a.flags = a.flags & -4097 | 2, I2 = false, xg = a);
        }
      } else {
        if (Dg(a)) throw Error(p(418));
        a.flags = a.flags & -4097 | 2;
        I2 = false;
        xg = a;
      }
    }
  }
  function Fg(a) {
    for (a = a.return; null !== a && 5 !== a.tag && 3 !== a.tag && 13 !== a.tag; ) a = a.return;
    xg = a;
  }
  function Gg(a) {
    if (a !== xg) return false;
    if (!I2) return Fg(a), I2 = true, false;
    var b2;
    (b2 = 3 !== a.tag) && !(b2 = 5 !== a.tag) && (b2 = a.type, b2 = "head" !== b2 && "body" !== b2 && !Ef(a.type, a.memoizedProps));
    if (b2 && (b2 = yg)) {
      if (Dg(a)) throw Hg(), Error(p(418));
      for (; b2; ) Ag(a, b2), b2 = Lf(b2.nextSibling);
    }
    Fg(a);
    if (13 === a.tag) {
      a = a.memoizedState;
      a = null !== a ? a.dehydrated : null;
      if (!a) throw Error(p(317));
      a: {
        a = a.nextSibling;
        for (b2 = 0; a; ) {
          if (8 === a.nodeType) {
            var c = a.data;
            if ("/$" === c) {
              if (0 === b2) {
                yg = Lf(a.nextSibling);
                break a;
              }
              b2--;
            } else "$" !== c && "$!" !== c && "$?" !== c || b2++;
          }
          a = a.nextSibling;
        }
        yg = null;
      }
    } else yg = xg ? Lf(a.stateNode.nextSibling) : null;
    return true;
  }
  function Hg() {
    for (var a = yg; a; ) a = Lf(a.nextSibling);
  }
  function Ig() {
    yg = xg = null;
    I2 = false;
  }
  function Jg(a) {
    null === zg ? zg = [a] : zg.push(a);
  }
  var Kg = ua.ReactCurrentBatchConfig;
  function Lg(a, b2, c) {
    a = c.ref;
    if (null !== a && "function" !== typeof a && "object" !== typeof a) {
      if (c._owner) {
        c = c._owner;
        if (c) {
          if (1 !== c.tag) throw Error(p(309));
          var d2 = c.stateNode;
        }
        if (!d2) throw Error(p(147, a));
        var e = d2, f = "" + a;
        if (null !== b2 && null !== b2.ref && "function" === typeof b2.ref && b2.ref._stringRef === f) return b2.ref;
        b2 = function(a2) {
          var b3 = e.refs;
          null === a2 ? delete b3[f] : b3[f] = a2;
        };
        b2._stringRef = f;
        return b2;
      }
      if ("string" !== typeof a) throw Error(p(284));
      if (!c._owner) throw Error(p(290, a));
    }
    return a;
  }
  function Mg(a, b2) {
    a = Object.prototype.toString.call(b2);
    throw Error(p(31, "[object Object]" === a ? "object with keys {" + Object.keys(b2).join(", ") + "}" : a));
  }
  function Ng(a) {
    var b2 = a._init;
    return b2(a._payload);
  }
  function Og(a) {
    function b2(b3, c2) {
      if (a) {
        var d3 = b3.deletions;
        null === d3 ? (b3.deletions = [c2], b3.flags |= 16) : d3.push(c2);
      }
    }
    function c(c2, d3) {
      if (!a) return null;
      for (; null !== d3; ) b2(c2, d3), d3 = d3.sibling;
      return null;
    }
    function d2(a2, b3) {
      for (a2 = /* @__PURE__ */ new Map(); null !== b3; ) null !== b3.key ? a2.set(b3.key, b3) : a2.set(b3.index, b3), b3 = b3.sibling;
      return a2;
    }
    function e(a2, b3) {
      a2 = Pg(a2, b3);
      a2.index = 0;
      a2.sibling = null;
      return a2;
    }
    function f(b3, c2, d3) {
      b3.index = d3;
      if (!a) return b3.flags |= 1048576, c2;
      d3 = b3.alternate;
      if (null !== d3) return d3 = d3.index, d3 < c2 ? (b3.flags |= 2, c2) : d3;
      b3.flags |= 2;
      return c2;
    }
    function g(b3) {
      a && null === b3.alternate && (b3.flags |= 2);
      return b3;
    }
    function h(a2, b3, c2, d3) {
      if (null === b3 || 6 !== b3.tag) return b3 = Qg(c2, a2.mode, d3), b3.return = a2, b3;
      b3 = e(b3, c2);
      b3.return = a2;
      return b3;
    }
    function k2(a2, b3, c2, d3) {
      var f2 = c2.type;
      if (f2 === ya) return m2(a2, b3, c2.props.children, d3, c2.key);
      if (null !== b3 && (b3.elementType === f2 || "object" === typeof f2 && null !== f2 && f2.$$typeof === Ha && Ng(f2) === b3.type)) return d3 = e(b3, c2.props), d3.ref = Lg(a2, b3, c2), d3.return = a2, d3;
      d3 = Rg(c2.type, c2.key, c2.props, null, a2.mode, d3);
      d3.ref = Lg(a2, b3, c2);
      d3.return = a2;
      return d3;
    }
    function l(a2, b3, c2, d3) {
      if (null === b3 || 4 !== b3.tag || b3.stateNode.containerInfo !== c2.containerInfo || b3.stateNode.implementation !== c2.implementation) return b3 = Sg(c2, a2.mode, d3), b3.return = a2, b3;
      b3 = e(b3, c2.children || []);
      b3.return = a2;
      return b3;
    }
    function m2(a2, b3, c2, d3, f2) {
      if (null === b3 || 7 !== b3.tag) return b3 = Tg(c2, a2.mode, d3, f2), b3.return = a2, b3;
      b3 = e(b3, c2);
      b3.return = a2;
      return b3;
    }
    function q2(a2, b3, c2) {
      if ("string" === typeof b3 && "" !== b3 || "number" === typeof b3) return b3 = Qg("" + b3, a2.mode, c2), b3.return = a2, b3;
      if ("object" === typeof b3 && null !== b3) {
        switch (b3.$$typeof) {
          case va:
            return c2 = Rg(b3.type, b3.key, b3.props, null, a2.mode, c2), c2.ref = Lg(a2, null, b3), c2.return = a2, c2;
          case wa:
            return b3 = Sg(b3, a2.mode, c2), b3.return = a2, b3;
          case Ha:
            var d3 = b3._init;
            return q2(a2, d3(b3._payload), c2);
        }
        if (eb(b3) || Ka(b3)) return b3 = Tg(b3, a2.mode, c2, null), b3.return = a2, b3;
        Mg(a2, b3);
      }
      return null;
    }
    function r(a2, b3, c2, d3) {
      var e2 = null !== b3 ? b3.key : null;
      if ("string" === typeof c2 && "" !== c2 || "number" === typeof c2) return null !== e2 ? null : h(a2, b3, "" + c2, d3);
      if ("object" === typeof c2 && null !== c2) {
        switch (c2.$$typeof) {
          case va:
            return c2.key === e2 ? k2(a2, b3, c2, d3) : null;
          case wa:
            return c2.key === e2 ? l(a2, b3, c2, d3) : null;
          case Ha:
            return e2 = c2._init, r(
              a2,
              b3,
              e2(c2._payload),
              d3
            );
        }
        if (eb(c2) || Ka(c2)) return null !== e2 ? null : m2(a2, b3, c2, d3, null);
        Mg(a2, c2);
      }
      return null;
    }
    function y2(a2, b3, c2, d3, e2) {
      if ("string" === typeof d3 && "" !== d3 || "number" === typeof d3) return a2 = a2.get(c2) || null, h(b3, a2, "" + d3, e2);
      if ("object" === typeof d3 && null !== d3) {
        switch (d3.$$typeof) {
          case va:
            return a2 = a2.get(null === d3.key ? c2 : d3.key) || null, k2(b3, a2, d3, e2);
          case wa:
            return a2 = a2.get(null === d3.key ? c2 : d3.key) || null, l(b3, a2, d3, e2);
          case Ha:
            var f2 = d3._init;
            return y2(a2, b3, c2, f2(d3._payload), e2);
        }
        if (eb(d3) || Ka(d3)) return a2 = a2.get(c2) || null, m2(b3, a2, d3, e2, null);
        Mg(b3, d3);
      }
      return null;
    }
    function n(e2, g2, h2, k3) {
      for (var l2 = null, m3 = null, u3 = g2, w2 = g2 = 0, x2 = null; null !== u3 && w2 < h2.length; w2++) {
        u3.index > w2 ? (x2 = u3, u3 = null) : x2 = u3.sibling;
        var n2 = r(e2, u3, h2[w2], k3);
        if (null === n2) {
          null === u3 && (u3 = x2);
          break;
        }
        a && u3 && null === n2.alternate && b2(e2, u3);
        g2 = f(n2, g2, w2);
        null === m3 ? l2 = n2 : m3.sibling = n2;
        m3 = n2;
        u3 = x2;
      }
      if (w2 === h2.length) return c(e2, u3), I2 && tg(e2, w2), l2;
      if (null === u3) {
        for (; w2 < h2.length; w2++) u3 = q2(e2, h2[w2], k3), null !== u3 && (g2 = f(u3, g2, w2), null === m3 ? l2 = u3 : m3.sibling = u3, m3 = u3);
        I2 && tg(e2, w2);
        return l2;
      }
      for (u3 = d2(e2, u3); w2 < h2.length; w2++) x2 = y2(u3, e2, w2, h2[w2], k3), null !== x2 && (a && null !== x2.alternate && u3.delete(null === x2.key ? w2 : x2.key), g2 = f(x2, g2, w2), null === m3 ? l2 = x2 : m3.sibling = x2, m3 = x2);
      a && u3.forEach(function(a2) {
        return b2(e2, a2);
      });
      I2 && tg(e2, w2);
      return l2;
    }
    function t(e2, g2, h2, k3) {
      var l2 = Ka(h2);
      if ("function" !== typeof l2) throw Error(p(150));
      h2 = l2.call(h2);
      if (null == h2) throw Error(p(151));
      for (var u3 = l2 = null, m3 = g2, w2 = g2 = 0, x2 = null, n2 = h2.next(); null !== m3 && !n2.done; w2++, n2 = h2.next()) {
        m3.index > w2 ? (x2 = m3, m3 = null) : x2 = m3.sibling;
        var t2 = r(e2, m3, n2.value, k3);
        if (null === t2) {
          null === m3 && (m3 = x2);
          break;
        }
        a && m3 && null === t2.alternate && b2(e2, m3);
        g2 = f(t2, g2, w2);
        null === u3 ? l2 = t2 : u3.sibling = t2;
        u3 = t2;
        m3 = x2;
      }
      if (n2.done) return c(
        e2,
        m3
      ), I2 && tg(e2, w2), l2;
      if (null === m3) {
        for (; !n2.done; w2++, n2 = h2.next()) n2 = q2(e2, n2.value, k3), null !== n2 && (g2 = f(n2, g2, w2), null === u3 ? l2 = n2 : u3.sibling = n2, u3 = n2);
        I2 && tg(e2, w2);
        return l2;
      }
      for (m3 = d2(e2, m3); !n2.done; w2++, n2 = h2.next()) n2 = y2(m3, e2, w2, n2.value, k3), null !== n2 && (a && null !== n2.alternate && m3.delete(null === n2.key ? w2 : n2.key), g2 = f(n2, g2, w2), null === u3 ? l2 = n2 : u3.sibling = n2, u3 = n2);
      a && m3.forEach(function(a2) {
        return b2(e2, a2);
      });
      I2 && tg(e2, w2);
      return l2;
    }
    function J2(a2, d3, f2, h2) {
      "object" === typeof f2 && null !== f2 && f2.type === ya && null === f2.key && (f2 = f2.props.children);
      if ("object" === typeof f2 && null !== f2) {
        switch (f2.$$typeof) {
          case va:
            a: {
              for (var k3 = f2.key, l2 = d3; null !== l2; ) {
                if (l2.key === k3) {
                  k3 = f2.type;
                  if (k3 === ya) {
                    if (7 === l2.tag) {
                      c(a2, l2.sibling);
                      d3 = e(l2, f2.props.children);
                      d3.return = a2;
                      a2 = d3;
                      break a;
                    }
                  } else if (l2.elementType === k3 || "object" === typeof k3 && null !== k3 && k3.$$typeof === Ha && Ng(k3) === l2.type) {
                    c(a2, l2.sibling);
                    d3 = e(l2, f2.props);
                    d3.ref = Lg(a2, l2, f2);
                    d3.return = a2;
                    a2 = d3;
                    break a;
                  }
                  c(a2, l2);
                  break;
                } else b2(a2, l2);
                l2 = l2.sibling;
              }
              f2.type === ya ? (d3 = Tg(f2.props.children, a2.mode, h2, f2.key), d3.return = a2, a2 = d3) : (h2 = Rg(f2.type, f2.key, f2.props, null, a2.mode, h2), h2.ref = Lg(a2, d3, f2), h2.return = a2, a2 = h2);
            }
            return g(a2);
          case wa:
            a: {
              for (l2 = f2.key; null !== d3; ) {
                if (d3.key === l2) if (4 === d3.tag && d3.stateNode.containerInfo === f2.containerInfo && d3.stateNode.implementation === f2.implementation) {
                  c(a2, d3.sibling);
                  d3 = e(d3, f2.children || []);
                  d3.return = a2;
                  a2 = d3;
                  break a;
                } else {
                  c(a2, d3);
                  break;
                }
                else b2(a2, d3);
                d3 = d3.sibling;
              }
              d3 = Sg(f2, a2.mode, h2);
              d3.return = a2;
              a2 = d3;
            }
            return g(a2);
          case Ha:
            return l2 = f2._init, J2(a2, d3, l2(f2._payload), h2);
        }
        if (eb(f2)) return n(a2, d3, f2, h2);
        if (Ka(f2)) return t(a2, d3, f2, h2);
        Mg(a2, f2);
      }
      return "string" === typeof f2 && "" !== f2 || "number" === typeof f2 ? (f2 = "" + f2, null !== d3 && 6 === d3.tag ? (c(a2, d3.sibling), d3 = e(d3, f2), d3.return = a2, a2 = d3) : (c(a2, d3), d3 = Qg(f2, a2.mode, h2), d3.return = a2, a2 = d3), g(a2)) : c(a2, d3);
    }
    return J2;
  }
  var Ug = Og(true), Vg = Og(false), Wg = Uf(null), Xg = null, Yg = null, Zg = null;
  function $g() {
    Zg = Yg = Xg = null;
  }
  function ah(a) {
    var b2 = Wg.current;
    E2(Wg);
    a._currentValue = b2;
  }
  function bh(a, b2, c) {
    for (; null !== a; ) {
      var d2 = a.alternate;
      (a.childLanes & b2) !== b2 ? (a.childLanes |= b2, null !== d2 && (d2.childLanes |= b2)) : null !== d2 && (d2.childLanes & b2) !== b2 && (d2.childLanes |= b2);
      if (a === c) break;
      a = a.return;
    }
  }
  function ch(a, b2) {
    Xg = a;
    Zg = Yg = null;
    a = a.dependencies;
    null !== a && null !== a.firstContext && (0 !== (a.lanes & b2) && (dh = true), a.firstContext = null);
  }
  function eh(a) {
    var b2 = a._currentValue;
    if (Zg !== a) if (a = { context: a, memoizedValue: b2, next: null }, null === Yg) {
      if (null === Xg) throw Error(p(308));
      Yg = a;
      Xg.dependencies = { lanes: 0, firstContext: a };
    } else Yg = Yg.next = a;
    return b2;
  }
  var fh = null;
  function gh(a) {
    null === fh ? fh = [a] : fh.push(a);
  }
  function hh(a, b2, c, d2) {
    var e = b2.interleaved;
    null === e ? (c.next = c, gh(b2)) : (c.next = e.next, e.next = c);
    b2.interleaved = c;
    return ih(a, d2);
  }
  function ih(a, b2) {
    a.lanes |= b2;
    var c = a.alternate;
    null !== c && (c.lanes |= b2);
    c = a;
    for (a = a.return; null !== a; ) a.childLanes |= b2, c = a.alternate, null !== c && (c.childLanes |= b2), c = a, a = a.return;
    return 3 === c.tag ? c.stateNode : null;
  }
  var jh = false;
  function kh(a) {
    a.updateQueue = { baseState: a.memoizedState, firstBaseUpdate: null, lastBaseUpdate: null, shared: { pending: null, interleaved: null, lanes: 0 }, effects: null };
  }
  function lh(a, b2) {
    a = a.updateQueue;
    b2.updateQueue === a && (b2.updateQueue = { baseState: a.baseState, firstBaseUpdate: a.firstBaseUpdate, lastBaseUpdate: a.lastBaseUpdate, shared: a.shared, effects: a.effects });
  }
  function mh(a, b2) {
    return { eventTime: a, lane: b2, tag: 0, payload: null, callback: null, next: null };
  }
  function nh(a, b2, c) {
    var d2 = a.updateQueue;
    if (null === d2) return null;
    d2 = d2.shared;
    if (0 !== (K2 & 2)) {
      var e = d2.pending;
      null === e ? b2.next = b2 : (b2.next = e.next, e.next = b2);
      d2.pending = b2;
      return ih(a, c);
    }
    e = d2.interleaved;
    null === e ? (b2.next = b2, gh(d2)) : (b2.next = e.next, e.next = b2);
    d2.interleaved = b2;
    return ih(a, c);
  }
  function oh(a, b2, c) {
    b2 = b2.updateQueue;
    if (null !== b2 && (b2 = b2.shared, 0 !== (c & 4194240))) {
      var d2 = b2.lanes;
      d2 &= a.pendingLanes;
      c |= d2;
      b2.lanes = c;
      Cc(a, c);
    }
  }
  function ph(a, b2) {
    var c = a.updateQueue, d2 = a.alternate;
    if (null !== d2 && (d2 = d2.updateQueue, c === d2)) {
      var e = null, f = null;
      c = c.firstBaseUpdate;
      if (null !== c) {
        do {
          var g = { eventTime: c.eventTime, lane: c.lane, tag: c.tag, payload: c.payload, callback: c.callback, next: null };
          null === f ? e = f = g : f = f.next = g;
          c = c.next;
        } while (null !== c);
        null === f ? e = f = b2 : f = f.next = b2;
      } else e = f = b2;
      c = { baseState: d2.baseState, firstBaseUpdate: e, lastBaseUpdate: f, shared: d2.shared, effects: d2.effects };
      a.updateQueue = c;
      return;
    }
    a = c.lastBaseUpdate;
    null === a ? c.firstBaseUpdate = b2 : a.next = b2;
    c.lastBaseUpdate = b2;
  }
  function qh(a, b2, c, d2) {
    var e = a.updateQueue;
    jh = false;
    var f = e.firstBaseUpdate, g = e.lastBaseUpdate, h = e.shared.pending;
    if (null !== h) {
      e.shared.pending = null;
      var k2 = h, l = k2.next;
      k2.next = null;
      null === g ? f = l : g.next = l;
      g = k2;
      var m2 = a.alternate;
      null !== m2 && (m2 = m2.updateQueue, h = m2.lastBaseUpdate, h !== g && (null === h ? m2.firstBaseUpdate = l : h.next = l, m2.lastBaseUpdate = k2));
    }
    if (null !== f) {
      var q2 = e.baseState;
      g = 0;
      m2 = l = k2 = null;
      h = f;
      do {
        var r = h.lane, y2 = h.eventTime;
        if ((d2 & r) === r) {
          null !== m2 && (m2 = m2.next = {
            eventTime: y2,
            lane: 0,
            tag: h.tag,
            payload: h.payload,
            callback: h.callback,
            next: null
          });
          a: {
            var n = a, t = h;
            r = b2;
            y2 = c;
            switch (t.tag) {
              case 1:
                n = t.payload;
                if ("function" === typeof n) {
                  q2 = n.call(y2, q2, r);
                  break a;
                }
                q2 = n;
                break a;
              case 3:
                n.flags = n.flags & -65537 | 128;
              case 0:
                n = t.payload;
                r = "function" === typeof n ? n.call(y2, q2, r) : n;
                if (null === r || void 0 === r) break a;
                q2 = A({}, q2, r);
                break a;
              case 2:
                jh = true;
            }
          }
          null !== h.callback && 0 !== h.lane && (a.flags |= 64, r = e.effects, null === r ? e.effects = [h] : r.push(h));
        } else y2 = { eventTime: y2, lane: r, tag: h.tag, payload: h.payload, callback: h.callback, next: null }, null === m2 ? (l = m2 = y2, k2 = q2) : m2 = m2.next = y2, g |= r;
        h = h.next;
        if (null === h) if (h = e.shared.pending, null === h) break;
        else r = h, h = r.next, r.next = null, e.lastBaseUpdate = r, e.shared.pending = null;
      } while (1);
      null === m2 && (k2 = q2);
      e.baseState = k2;
      e.firstBaseUpdate = l;
      e.lastBaseUpdate = m2;
      b2 = e.shared.interleaved;
      if (null !== b2) {
        e = b2;
        do
          g |= e.lane, e = e.next;
        while (e !== b2);
      } else null === f && (e.shared.lanes = 0);
      rh |= g;
      a.lanes = g;
      a.memoizedState = q2;
    }
  }
  function sh(a, b2, c) {
    a = b2.effects;
    b2.effects = null;
    if (null !== a) for (b2 = 0; b2 < a.length; b2++) {
      var d2 = a[b2], e = d2.callback;
      if (null !== e) {
        d2.callback = null;
        d2 = c;
        if ("function" !== typeof e) throw Error(p(191, e));
        e.call(d2);
      }
    }
  }
  var th = {}, uh = Uf(th), vh = Uf(th), wh = Uf(th);
  function xh(a) {
    if (a === th) throw Error(p(174));
    return a;
  }
  function yh(a, b2) {
    G2(wh, b2);
    G2(vh, a);
    G2(uh, th);
    a = b2.nodeType;
    switch (a) {
      case 9:
      case 11:
        b2 = (b2 = b2.documentElement) ? b2.namespaceURI : lb(null, "");
        break;
      default:
        a = 8 === a ? b2.parentNode : b2, b2 = a.namespaceURI || null, a = a.tagName, b2 = lb(b2, a);
    }
    E2(uh);
    G2(uh, b2);
  }
  function zh() {
    E2(uh);
    E2(vh);
    E2(wh);
  }
  function Ah(a) {
    xh(wh.current);
    var b2 = xh(uh.current);
    var c = lb(b2, a.type);
    b2 !== c && (G2(vh, a), G2(uh, c));
  }
  function Bh(a) {
    vh.current === a && (E2(uh), E2(vh));
  }
  var L2 = Uf(0);
  function Ch(a) {
    for (var b2 = a; null !== b2; ) {
      if (13 === b2.tag) {
        var c = b2.memoizedState;
        if (null !== c && (c = c.dehydrated, null === c || "$?" === c.data || "$!" === c.data)) return b2;
      } else if (19 === b2.tag && void 0 !== b2.memoizedProps.revealOrder) {
        if (0 !== (b2.flags & 128)) return b2;
      } else if (null !== b2.child) {
        b2.child.return = b2;
        b2 = b2.child;
        continue;
      }
      if (b2 === a) break;
      for (; null === b2.sibling; ) {
        if (null === b2.return || b2.return === a) return null;
        b2 = b2.return;
      }
      b2.sibling.return = b2.return;
      b2 = b2.sibling;
    }
    return null;
  }
  var Dh = [];
  function Eh() {
    for (var a = 0; a < Dh.length; a++) Dh[a]._workInProgressVersionPrimary = null;
    Dh.length = 0;
  }
  var Fh = ua.ReactCurrentDispatcher, Gh = ua.ReactCurrentBatchConfig, Hh = 0, M2 = null, N2 = null, O = null, Ih = false, Jh = false, Kh = 0, Lh = 0;
  function P2() {
    throw Error(p(321));
  }
  function Mh(a, b2) {
    if (null === b2) return false;
    for (var c = 0; c < b2.length && c < a.length; c++) if (!He2(a[c], b2[c])) return false;
    return true;
  }
  function Nh(a, b2, c, d2, e, f) {
    Hh = f;
    M2 = b2;
    b2.memoizedState = null;
    b2.updateQueue = null;
    b2.lanes = 0;
    Fh.current = null === a || null === a.memoizedState ? Oh : Ph;
    a = c(d2, e);
    if (Jh) {
      f = 0;
      do {
        Jh = false;
        Kh = 0;
        if (25 <= f) throw Error(p(301));
        f += 1;
        O = N2 = null;
        b2.updateQueue = null;
        Fh.current = Qh;
        a = c(d2, e);
      } while (Jh);
    }
    Fh.current = Rh;
    b2 = null !== N2 && null !== N2.next;
    Hh = 0;
    O = N2 = M2 = null;
    Ih = false;
    if (b2) throw Error(p(300));
    return a;
  }
  function Sh() {
    var a = 0 !== Kh;
    Kh = 0;
    return a;
  }
  function Th() {
    var a = { memoizedState: null, baseState: null, baseQueue: null, queue: null, next: null };
    null === O ? M2.memoizedState = O = a : O = O.next = a;
    return O;
  }
  function Uh() {
    if (null === N2) {
      var a = M2.alternate;
      a = null !== a ? a.memoizedState : null;
    } else a = N2.next;
    var b2 = null === O ? M2.memoizedState : O.next;
    if (null !== b2) O = b2, N2 = a;
    else {
      if (null === a) throw Error(p(310));
      N2 = a;
      a = { memoizedState: N2.memoizedState, baseState: N2.baseState, baseQueue: N2.baseQueue, queue: N2.queue, next: null };
      null === O ? M2.memoizedState = O = a : O = O.next = a;
    }
    return O;
  }
  function Vh(a, b2) {
    return "function" === typeof b2 ? b2(a) : b2;
  }
  function Wh(a) {
    var b2 = Uh(), c = b2.queue;
    if (null === c) throw Error(p(311));
    c.lastRenderedReducer = a;
    var d2 = N2, e = d2.baseQueue, f = c.pending;
    if (null !== f) {
      if (null !== e) {
        var g = e.next;
        e.next = f.next;
        f.next = g;
      }
      d2.baseQueue = e = f;
      c.pending = null;
    }
    if (null !== e) {
      f = e.next;
      d2 = d2.baseState;
      var h = g = null, k2 = null, l = f;
      do {
        var m2 = l.lane;
        if ((Hh & m2) === m2) null !== k2 && (k2 = k2.next = { lane: 0, action: l.action, hasEagerState: l.hasEagerState, eagerState: l.eagerState, next: null }), d2 = l.hasEagerState ? l.eagerState : a(d2, l.action);
        else {
          var q2 = {
            lane: m2,
            action: l.action,
            hasEagerState: l.hasEagerState,
            eagerState: l.eagerState,
            next: null
          };
          null === k2 ? (h = k2 = q2, g = d2) : k2 = k2.next = q2;
          M2.lanes |= m2;
          rh |= m2;
        }
        l = l.next;
      } while (null !== l && l !== f);
      null === k2 ? g = d2 : k2.next = h;
      He2(d2, b2.memoizedState) || (dh = true);
      b2.memoizedState = d2;
      b2.baseState = g;
      b2.baseQueue = k2;
      c.lastRenderedState = d2;
    }
    a = c.interleaved;
    if (null !== a) {
      e = a;
      do
        f = e.lane, M2.lanes |= f, rh |= f, e = e.next;
      while (e !== a);
    } else null === e && (c.lanes = 0);
    return [b2.memoizedState, c.dispatch];
  }
  function Xh(a) {
    var b2 = Uh(), c = b2.queue;
    if (null === c) throw Error(p(311));
    c.lastRenderedReducer = a;
    var d2 = c.dispatch, e = c.pending, f = b2.memoizedState;
    if (null !== e) {
      c.pending = null;
      var g = e = e.next;
      do
        f = a(f, g.action), g = g.next;
      while (g !== e);
      He2(f, b2.memoizedState) || (dh = true);
      b2.memoizedState = f;
      null === b2.baseQueue && (b2.baseState = f);
      c.lastRenderedState = f;
    }
    return [f, d2];
  }
  function Yh() {
  }
  function Zh(a, b2) {
    var c = M2, d2 = Uh(), e = b2(), f = !He2(d2.memoizedState, e);
    f && (d2.memoizedState = e, dh = true);
    d2 = d2.queue;
    $h(ai.bind(null, c, d2, a), [a]);
    if (d2.getSnapshot !== b2 || f || null !== O && O.memoizedState.tag & 1) {
      c.flags |= 2048;
      bi(9, ci.bind(null, c, d2, e, b2), void 0, null);
      if (null === Q2) throw Error(p(349));
      0 !== (Hh & 30) || di(c, b2, e);
    }
    return e;
  }
  function di(a, b2, c) {
    a.flags |= 16384;
    a = { getSnapshot: b2, value: c };
    b2 = M2.updateQueue;
    null === b2 ? (b2 = { lastEffect: null, stores: null }, M2.updateQueue = b2, b2.stores = [a]) : (c = b2.stores, null === c ? b2.stores = [a] : c.push(a));
  }
  function ci(a, b2, c, d2) {
    b2.value = c;
    b2.getSnapshot = d2;
    ei(b2) && fi(a);
  }
  function ai(a, b2, c) {
    return c(function() {
      ei(b2) && fi(a);
    });
  }
  function ei(a) {
    var b2 = a.getSnapshot;
    a = a.value;
    try {
      var c = b2();
      return !He2(a, c);
    } catch (d2) {
      return true;
    }
  }
  function fi(a) {
    var b2 = ih(a, 1);
    null !== b2 && gi(b2, a, 1, -1);
  }
  function hi(a) {
    var b2 = Th();
    "function" === typeof a && (a = a());
    b2.memoizedState = b2.baseState = a;
    a = { pending: null, interleaved: null, lanes: 0, dispatch: null, lastRenderedReducer: Vh, lastRenderedState: a };
    b2.queue = a;
    a = a.dispatch = ii.bind(null, M2, a);
    return [b2.memoizedState, a];
  }
  function bi(a, b2, c, d2) {
    a = { tag: a, create: b2, destroy: c, deps: d2, next: null };
    b2 = M2.updateQueue;
    null === b2 ? (b2 = { lastEffect: null, stores: null }, M2.updateQueue = b2, b2.lastEffect = a.next = a) : (c = b2.lastEffect, null === c ? b2.lastEffect = a.next = a : (d2 = c.next, c.next = a, a.next = d2, b2.lastEffect = a));
    return a;
  }
  function ji() {
    return Uh().memoizedState;
  }
  function ki(a, b2, c, d2) {
    var e = Th();
    M2.flags |= a;
    e.memoizedState = bi(1 | b2, c, void 0, void 0 === d2 ? null : d2);
  }
  function li(a, b2, c, d2) {
    var e = Uh();
    d2 = void 0 === d2 ? null : d2;
    var f = void 0;
    if (null !== N2) {
      var g = N2.memoizedState;
      f = g.destroy;
      if (null !== d2 && Mh(d2, g.deps)) {
        e.memoizedState = bi(b2, c, f, d2);
        return;
      }
    }
    M2.flags |= a;
    e.memoizedState = bi(1 | b2, c, f, d2);
  }
  function mi(a, b2) {
    return ki(8390656, 8, a, b2);
  }
  function $h(a, b2) {
    return li(2048, 8, a, b2);
  }
  function ni(a, b2) {
    return li(4, 2, a, b2);
  }
  function oi(a, b2) {
    return li(4, 4, a, b2);
  }
  function pi(a, b2) {
    if ("function" === typeof b2) return a = a(), b2(a), function() {
      b2(null);
    };
    if (null !== b2 && void 0 !== b2) return a = a(), b2.current = a, function() {
      b2.current = null;
    };
  }
  function qi(a, b2, c) {
    c = null !== c && void 0 !== c ? c.concat([a]) : null;
    return li(4, 4, pi.bind(null, b2, a), c);
  }
  function ri() {
  }
  function si(a, b2) {
    var c = Uh();
    b2 = void 0 === b2 ? null : b2;
    var d2 = c.memoizedState;
    if (null !== d2 && null !== b2 && Mh(b2, d2[1])) return d2[0];
    c.memoizedState = [a, b2];
    return a;
  }
  function ti(a, b2) {
    var c = Uh();
    b2 = void 0 === b2 ? null : b2;
    var d2 = c.memoizedState;
    if (null !== d2 && null !== b2 && Mh(b2, d2[1])) return d2[0];
    a = a();
    c.memoizedState = [a, b2];
    return a;
  }
  function ui(a, b2, c) {
    if (0 === (Hh & 21)) return a.baseState && (a.baseState = false, dh = true), a.memoizedState = c;
    He2(c, b2) || (c = yc(), M2.lanes |= c, rh |= c, a.baseState = true);
    return b2;
  }
  function vi(a, b2) {
    var c = C2;
    C2 = 0 !== c && 4 > c ? c : 4;
    a(true);
    var d2 = Gh.transition;
    Gh.transition = {};
    try {
      a(false), b2();
    } finally {
      C2 = c, Gh.transition = d2;
    }
  }
  function wi() {
    return Uh().memoizedState;
  }
  function xi(a, b2, c) {
    var d2 = yi(a);
    c = { lane: d2, action: c, hasEagerState: false, eagerState: null, next: null };
    if (zi(a)) Ai(b2, c);
    else if (c = hh(a, b2, c, d2), null !== c) {
      var e = R();
      gi(c, a, d2, e);
      Bi(c, b2, d2);
    }
  }
  function ii(a, b2, c) {
    var d2 = yi(a), e = { lane: d2, action: c, hasEagerState: false, eagerState: null, next: null };
    if (zi(a)) Ai(b2, e);
    else {
      var f = a.alternate;
      if (0 === a.lanes && (null === f || 0 === f.lanes) && (f = b2.lastRenderedReducer, null !== f)) try {
        var g = b2.lastRenderedState, h = f(g, c);
        e.hasEagerState = true;
        e.eagerState = h;
        if (He2(h, g)) {
          var k2 = b2.interleaved;
          null === k2 ? (e.next = e, gh(b2)) : (e.next = k2.next, k2.next = e);
          b2.interleaved = e;
          return;
        }
      } catch (l) {
      } finally {
      }
      c = hh(a, b2, e, d2);
      null !== c && (e = R(), gi(c, a, d2, e), Bi(c, b2, d2));
    }
  }
  function zi(a) {
    var b2 = a.alternate;
    return a === M2 || null !== b2 && b2 === M2;
  }
  function Ai(a, b2) {
    Jh = Ih = true;
    var c = a.pending;
    null === c ? b2.next = b2 : (b2.next = c.next, c.next = b2);
    a.pending = b2;
  }
  function Bi(a, b2, c) {
    if (0 !== (c & 4194240)) {
      var d2 = b2.lanes;
      d2 &= a.pendingLanes;
      c |= d2;
      b2.lanes = c;
      Cc(a, c);
    }
  }
  var Rh = { readContext: eh, useCallback: P2, useContext: P2, useEffect: P2, useImperativeHandle: P2, useInsertionEffect: P2, useLayoutEffect: P2, useMemo: P2, useReducer: P2, useRef: P2, useState: P2, useDebugValue: P2, useDeferredValue: P2, useTransition: P2, useMutableSource: P2, useSyncExternalStore: P2, useId: P2, unstable_isNewReconciler: false }, Oh = { readContext: eh, useCallback: function(a, b2) {
    Th().memoizedState = [a, void 0 === b2 ? null : b2];
    return a;
  }, useContext: eh, useEffect: mi, useImperativeHandle: function(a, b2, c) {
    c = null !== c && void 0 !== c ? c.concat([a]) : null;
    return ki(
      4194308,
      4,
      pi.bind(null, b2, a),
      c
    );
  }, useLayoutEffect: function(a, b2) {
    return ki(4194308, 4, a, b2);
  }, useInsertionEffect: function(a, b2) {
    return ki(4, 2, a, b2);
  }, useMemo: function(a, b2) {
    var c = Th();
    b2 = void 0 === b2 ? null : b2;
    a = a();
    c.memoizedState = [a, b2];
    return a;
  }, useReducer: function(a, b2, c) {
    var d2 = Th();
    b2 = void 0 !== c ? c(b2) : b2;
    d2.memoizedState = d2.baseState = b2;
    a = { pending: null, interleaved: null, lanes: 0, dispatch: null, lastRenderedReducer: a, lastRenderedState: b2 };
    d2.queue = a;
    a = a.dispatch = xi.bind(null, M2, a);
    return [d2.memoizedState, a];
  }, useRef: function(a) {
    var b2 = Th();
    a = { current: a };
    return b2.memoizedState = a;
  }, useState: hi, useDebugValue: ri, useDeferredValue: function(a) {
    return Th().memoizedState = a;
  }, useTransition: function() {
    var a = hi(false), b2 = a[0];
    a = vi.bind(null, a[1]);
    Th().memoizedState = a;
    return [b2, a];
  }, useMutableSource: function() {
  }, useSyncExternalStore: function(a, b2, c) {
    var d2 = M2, e = Th();
    if (I2) {
      if (void 0 === c) throw Error(p(407));
      c = c();
    } else {
      c = b2();
      if (null === Q2) throw Error(p(349));
      0 !== (Hh & 30) || di(d2, b2, c);
    }
    e.memoizedState = c;
    var f = { value: c, getSnapshot: b2 };
    e.queue = f;
    mi(ai.bind(
      null,
      d2,
      f,
      a
    ), [a]);
    d2.flags |= 2048;
    bi(9, ci.bind(null, d2, f, c, b2), void 0, null);
    return c;
  }, useId: function() {
    var a = Th(), b2 = Q2.identifierPrefix;
    if (I2) {
      var c = sg;
      var d2 = rg;
      c = (d2 & ~(1 << 32 - oc(d2) - 1)).toString(32) + c;
      b2 = ":" + b2 + "R" + c;
      c = Kh++;
      0 < c && (b2 += "H" + c.toString(32));
      b2 += ":";
    } else c = Lh++, b2 = ":" + b2 + "r" + c.toString(32) + ":";
    return a.memoizedState = b2;
  }, unstable_isNewReconciler: false }, Ph = {
    readContext: eh,
    useCallback: si,
    useContext: eh,
    useEffect: $h,
    useImperativeHandle: qi,
    useInsertionEffect: ni,
    useLayoutEffect: oi,
    useMemo: ti,
    useReducer: Wh,
    useRef: ji,
    useState: function() {
      return Wh(Vh);
    },
    useDebugValue: ri,
    useDeferredValue: function(a) {
      var b2 = Uh();
      return ui(b2, N2.memoizedState, a);
    },
    useTransition: function() {
      var a = Wh(Vh)[0], b2 = Uh().memoizedState;
      return [a, b2];
    },
    useMutableSource: Yh,
    useSyncExternalStore: Zh,
    useId: wi,
    unstable_isNewReconciler: false
  }, Qh = { readContext: eh, useCallback: si, useContext: eh, useEffect: $h, useImperativeHandle: qi, useInsertionEffect: ni, useLayoutEffect: oi, useMemo: ti, useReducer: Xh, useRef: ji, useState: function() {
    return Xh(Vh);
  }, useDebugValue: ri, useDeferredValue: function(a) {
    var b2 = Uh();
    return null === N2 ? b2.memoizedState = a : ui(b2, N2.memoizedState, a);
  }, useTransition: function() {
    var a = Xh(Vh)[0], b2 = Uh().memoizedState;
    return [a, b2];
  }, useMutableSource: Yh, useSyncExternalStore: Zh, useId: wi, unstable_isNewReconciler: false };
  function Ci(a, b2) {
    if (a && a.defaultProps) {
      b2 = A({}, b2);
      a = a.defaultProps;
      for (var c in a) void 0 === b2[c] && (b2[c] = a[c]);
      return b2;
    }
    return b2;
  }
  function Di(a, b2, c, d2) {
    b2 = a.memoizedState;
    c = c(d2, b2);
    c = null === c || void 0 === c ? b2 : A({}, b2, c);
    a.memoizedState = c;
    0 === a.lanes && (a.updateQueue.baseState = c);
  }
  var Ei = { isMounted: function(a) {
    return (a = a._reactInternals) ? Vb(a) === a : false;
  }, enqueueSetState: function(a, b2, c) {
    a = a._reactInternals;
    var d2 = R(), e = yi(a), f = mh(d2, e);
    f.payload = b2;
    void 0 !== c && null !== c && (f.callback = c);
    b2 = nh(a, f, e);
    null !== b2 && (gi(b2, a, e, d2), oh(b2, a, e));
  }, enqueueReplaceState: function(a, b2, c) {
    a = a._reactInternals;
    var d2 = R(), e = yi(a), f = mh(d2, e);
    f.tag = 1;
    f.payload = b2;
    void 0 !== c && null !== c && (f.callback = c);
    b2 = nh(a, f, e);
    null !== b2 && (gi(b2, a, e, d2), oh(b2, a, e));
  }, enqueueForceUpdate: function(a, b2) {
    a = a._reactInternals;
    var c = R(), d2 = yi(a), e = mh(c, d2);
    e.tag = 2;
    void 0 !== b2 && null !== b2 && (e.callback = b2);
    b2 = nh(a, e, d2);
    null !== b2 && (gi(b2, a, d2, c), oh(b2, a, d2));
  } };
  function Fi(a, b2, c, d2, e, f, g) {
    a = a.stateNode;
    return "function" === typeof a.shouldComponentUpdate ? a.shouldComponentUpdate(d2, f, g) : b2.prototype && b2.prototype.isPureReactComponent ? !Ie2(c, d2) || !Ie2(e, f) : true;
  }
  function Gi(a, b2, c) {
    var d2 = false, e = Vf;
    var f = b2.contextType;
    "object" === typeof f && null !== f ? f = eh(f) : (e = Zf(b2) ? Xf : H.current, d2 = b2.contextTypes, f = (d2 = null !== d2 && void 0 !== d2) ? Yf(a, e) : Vf);
    b2 = new b2(c, f);
    a.memoizedState = null !== b2.state && void 0 !== b2.state ? b2.state : null;
    b2.updater = Ei;
    a.stateNode = b2;
    b2._reactInternals = a;
    d2 && (a = a.stateNode, a.__reactInternalMemoizedUnmaskedChildContext = e, a.__reactInternalMemoizedMaskedChildContext = f);
    return b2;
  }
  function Hi(a, b2, c, d2) {
    a = b2.state;
    "function" === typeof b2.componentWillReceiveProps && b2.componentWillReceiveProps(c, d2);
    "function" === typeof b2.UNSAFE_componentWillReceiveProps && b2.UNSAFE_componentWillReceiveProps(c, d2);
    b2.state !== a && Ei.enqueueReplaceState(b2, b2.state, null);
  }
  function Ii(a, b2, c, d2) {
    var e = a.stateNode;
    e.props = c;
    e.state = a.memoizedState;
    e.refs = {};
    kh(a);
    var f = b2.contextType;
    "object" === typeof f && null !== f ? e.context = eh(f) : (f = Zf(b2) ? Xf : H.current, e.context = Yf(a, f));
    e.state = a.memoizedState;
    f = b2.getDerivedStateFromProps;
    "function" === typeof f && (Di(a, b2, f, c), e.state = a.memoizedState);
    "function" === typeof b2.getDerivedStateFromProps || "function" === typeof e.getSnapshotBeforeUpdate || "function" !== typeof e.UNSAFE_componentWillMount && "function" !== typeof e.componentWillMount || (b2 = e.state, "function" === typeof e.componentWillMount && e.componentWillMount(), "function" === typeof e.UNSAFE_componentWillMount && e.UNSAFE_componentWillMount(), b2 !== e.state && Ei.enqueueReplaceState(e, e.state, null), qh(a, c, e, d2), e.state = a.memoizedState);
    "function" === typeof e.componentDidMount && (a.flags |= 4194308);
  }
  function Ji(a, b2) {
    try {
      var c = "", d2 = b2;
      do
        c += Pa(d2), d2 = d2.return;
      while (d2);
      var e = c;
    } catch (f) {
      e = "\nError generating stack: " + f.message + "\n" + f.stack;
    }
    return { value: a, source: b2, stack: e, digest: null };
  }
  function Ki(a, b2, c) {
    return { value: a, source: null, stack: null != c ? c : null, digest: null != b2 ? b2 : null };
  }
  function Li(a, b2) {
    try {
      console.error(b2.value);
    } catch (c) {
      setTimeout(function() {
        throw c;
      });
    }
  }
  var Mi = "function" === typeof WeakMap ? WeakMap : Map;
  function Ni(a, b2, c) {
    c = mh(-1, c);
    c.tag = 3;
    c.payload = { element: null };
    var d2 = b2.value;
    c.callback = function() {
      Oi || (Oi = true, Pi = d2);
      Li(a, b2);
    };
    return c;
  }
  function Qi(a, b2, c) {
    c = mh(-1, c);
    c.tag = 3;
    var d2 = a.type.getDerivedStateFromError;
    if ("function" === typeof d2) {
      var e = b2.value;
      c.payload = function() {
        return d2(e);
      };
      c.callback = function() {
        Li(a, b2);
      };
    }
    var f = a.stateNode;
    null !== f && "function" === typeof f.componentDidCatch && (c.callback = function() {
      Li(a, b2);
      "function" !== typeof d2 && (null === Ri ? Ri = /* @__PURE__ */ new Set([this]) : Ri.add(this));
      var c2 = b2.stack;
      this.componentDidCatch(b2.value, { componentStack: null !== c2 ? c2 : "" });
    });
    return c;
  }
  function Si(a, b2, c) {
    var d2 = a.pingCache;
    if (null === d2) {
      d2 = a.pingCache = new Mi();
      var e = /* @__PURE__ */ new Set();
      d2.set(b2, e);
    } else e = d2.get(b2), void 0 === e && (e = /* @__PURE__ */ new Set(), d2.set(b2, e));
    e.has(c) || (e.add(c), a = Ti.bind(null, a, b2, c), b2.then(a, a));
  }
  function Ui(a) {
    do {
      var b2;
      if (b2 = 13 === a.tag) b2 = a.memoizedState, b2 = null !== b2 ? null !== b2.dehydrated ? true : false : true;
      if (b2) return a;
      a = a.return;
    } while (null !== a);
    return null;
  }
  function Vi(a, b2, c, d2, e) {
    if (0 === (a.mode & 1)) return a === b2 ? a.flags |= 65536 : (a.flags |= 128, c.flags |= 131072, c.flags &= -52805, 1 === c.tag && (null === c.alternate ? c.tag = 17 : (b2 = mh(-1, 1), b2.tag = 2, nh(c, b2, 1))), c.lanes |= 1), a;
    a.flags |= 65536;
    a.lanes = e;
    return a;
  }
  var Wi = ua.ReactCurrentOwner, dh = false;
  function Xi(a, b2, c, d2) {
    b2.child = null === a ? Vg(b2, null, c, d2) : Ug(b2, a.child, c, d2);
  }
  function Yi(a, b2, c, d2, e) {
    c = c.render;
    var f = b2.ref;
    ch(b2, e);
    d2 = Nh(a, b2, c, d2, f, e);
    c = Sh();
    if (null !== a && !dh) return b2.updateQueue = a.updateQueue, b2.flags &= -2053, a.lanes &= ~e, Zi(a, b2, e);
    I2 && c && vg(b2);
    b2.flags |= 1;
    Xi(a, b2, d2, e);
    return b2.child;
  }
  function $i(a, b2, c, d2, e) {
    if (null === a) {
      var f = c.type;
      if ("function" === typeof f && !aj(f) && void 0 === f.defaultProps && null === c.compare && void 0 === c.defaultProps) return b2.tag = 15, b2.type = f, bj(a, b2, f, d2, e);
      a = Rg(c.type, null, d2, b2, b2.mode, e);
      a.ref = b2.ref;
      a.return = b2;
      return b2.child = a;
    }
    f = a.child;
    if (0 === (a.lanes & e)) {
      var g = f.memoizedProps;
      c = c.compare;
      c = null !== c ? c : Ie2;
      if (c(g, d2) && a.ref === b2.ref) return Zi(a, b2, e);
    }
    b2.flags |= 1;
    a = Pg(f, d2);
    a.ref = b2.ref;
    a.return = b2;
    return b2.child = a;
  }
  function bj(a, b2, c, d2, e) {
    if (null !== a) {
      var f = a.memoizedProps;
      if (Ie2(f, d2) && a.ref === b2.ref) if (dh = false, b2.pendingProps = d2 = f, 0 !== (a.lanes & e)) 0 !== (a.flags & 131072) && (dh = true);
      else return b2.lanes = a.lanes, Zi(a, b2, e);
    }
    return cj(a, b2, c, d2, e);
  }
  function dj(a, b2, c) {
    var d2 = b2.pendingProps, e = d2.children, f = null !== a ? a.memoizedState : null;
    if ("hidden" === d2.mode) if (0 === (b2.mode & 1)) b2.memoizedState = { baseLanes: 0, cachePool: null, transitions: null }, G2(ej, fj), fj |= c;
    else {
      if (0 === (c & 1073741824)) return a = null !== f ? f.baseLanes | c : c, b2.lanes = b2.childLanes = 1073741824, b2.memoizedState = { baseLanes: a, cachePool: null, transitions: null }, b2.updateQueue = null, G2(ej, fj), fj |= a, null;
      b2.memoizedState = { baseLanes: 0, cachePool: null, transitions: null };
      d2 = null !== f ? f.baseLanes : c;
      G2(ej, fj);
      fj |= d2;
    }
    else null !== f ? (d2 = f.baseLanes | c, b2.memoizedState = null) : d2 = c, G2(ej, fj), fj |= d2;
    Xi(a, b2, e, c);
    return b2.child;
  }
  function gj(a, b2) {
    var c = b2.ref;
    if (null === a && null !== c || null !== a && a.ref !== c) b2.flags |= 512, b2.flags |= 2097152;
  }
  function cj(a, b2, c, d2, e) {
    var f = Zf(c) ? Xf : H.current;
    f = Yf(b2, f);
    ch(b2, e);
    c = Nh(a, b2, c, d2, f, e);
    d2 = Sh();
    if (null !== a && !dh) return b2.updateQueue = a.updateQueue, b2.flags &= -2053, a.lanes &= ~e, Zi(a, b2, e);
    I2 && d2 && vg(b2);
    b2.flags |= 1;
    Xi(a, b2, c, e);
    return b2.child;
  }
  function hj(a, b2, c, d2, e) {
    if (Zf(c)) {
      var f = true;
      cg(b2);
    } else f = false;
    ch(b2, e);
    if (null === b2.stateNode) ij(a, b2), Gi(b2, c, d2), Ii(b2, c, d2, e), d2 = true;
    else if (null === a) {
      var g = b2.stateNode, h = b2.memoizedProps;
      g.props = h;
      var k2 = g.context, l = c.contextType;
      "object" === typeof l && null !== l ? l = eh(l) : (l = Zf(c) ? Xf : H.current, l = Yf(b2, l));
      var m2 = c.getDerivedStateFromProps, q2 = "function" === typeof m2 || "function" === typeof g.getSnapshotBeforeUpdate;
      q2 || "function" !== typeof g.UNSAFE_componentWillReceiveProps && "function" !== typeof g.componentWillReceiveProps || (h !== d2 || k2 !== l) && Hi(b2, g, d2, l);
      jh = false;
      var r = b2.memoizedState;
      g.state = r;
      qh(b2, d2, g, e);
      k2 = b2.memoizedState;
      h !== d2 || r !== k2 || Wf.current || jh ? ("function" === typeof m2 && (Di(b2, c, m2, d2), k2 = b2.memoizedState), (h = jh || Fi(b2, c, h, d2, r, k2, l)) ? (q2 || "function" !== typeof g.UNSAFE_componentWillMount && "function" !== typeof g.componentWillMount || ("function" === typeof g.componentWillMount && g.componentWillMount(), "function" === typeof g.UNSAFE_componentWillMount && g.UNSAFE_componentWillMount()), "function" === typeof g.componentDidMount && (b2.flags |= 4194308)) : ("function" === typeof g.componentDidMount && (b2.flags |= 4194308), b2.memoizedProps = d2, b2.memoizedState = k2), g.props = d2, g.state = k2, g.context = l, d2 = h) : ("function" === typeof g.componentDidMount && (b2.flags |= 4194308), d2 = false);
    } else {
      g = b2.stateNode;
      lh(a, b2);
      h = b2.memoizedProps;
      l = b2.type === b2.elementType ? h : Ci(b2.type, h);
      g.props = l;
      q2 = b2.pendingProps;
      r = g.context;
      k2 = c.contextType;
      "object" === typeof k2 && null !== k2 ? k2 = eh(k2) : (k2 = Zf(c) ? Xf : H.current, k2 = Yf(b2, k2));
      var y2 = c.getDerivedStateFromProps;
      (m2 = "function" === typeof y2 || "function" === typeof g.getSnapshotBeforeUpdate) || "function" !== typeof g.UNSAFE_componentWillReceiveProps && "function" !== typeof g.componentWillReceiveProps || (h !== q2 || r !== k2) && Hi(b2, g, d2, k2);
      jh = false;
      r = b2.memoizedState;
      g.state = r;
      qh(b2, d2, g, e);
      var n = b2.memoizedState;
      h !== q2 || r !== n || Wf.current || jh ? ("function" === typeof y2 && (Di(b2, c, y2, d2), n = b2.memoizedState), (l = jh || Fi(b2, c, l, d2, r, n, k2) || false) ? (m2 || "function" !== typeof g.UNSAFE_componentWillUpdate && "function" !== typeof g.componentWillUpdate || ("function" === typeof g.componentWillUpdate && g.componentWillUpdate(d2, n, k2), "function" === typeof g.UNSAFE_componentWillUpdate && g.UNSAFE_componentWillUpdate(d2, n, k2)), "function" === typeof g.componentDidUpdate && (b2.flags |= 4), "function" === typeof g.getSnapshotBeforeUpdate && (b2.flags |= 1024)) : ("function" !== typeof g.componentDidUpdate || h === a.memoizedProps && r === a.memoizedState || (b2.flags |= 4), "function" !== typeof g.getSnapshotBeforeUpdate || h === a.memoizedProps && r === a.memoizedState || (b2.flags |= 1024), b2.memoizedProps = d2, b2.memoizedState = n), g.props = d2, g.state = n, g.context = k2, d2 = l) : ("function" !== typeof g.componentDidUpdate || h === a.memoizedProps && r === a.memoizedState || (b2.flags |= 4), "function" !== typeof g.getSnapshotBeforeUpdate || h === a.memoizedProps && r === a.memoizedState || (b2.flags |= 1024), d2 = false);
    }
    return jj(a, b2, c, d2, f, e);
  }
  function jj(a, b2, c, d2, e, f) {
    gj(a, b2);
    var g = 0 !== (b2.flags & 128);
    if (!d2 && !g) return e && dg(b2, c, false), Zi(a, b2, f);
    d2 = b2.stateNode;
    Wi.current = b2;
    var h = g && "function" !== typeof c.getDerivedStateFromError ? null : d2.render();
    b2.flags |= 1;
    null !== a && g ? (b2.child = Ug(b2, a.child, null, f), b2.child = Ug(b2, null, h, f)) : Xi(a, b2, h, f);
    b2.memoizedState = d2.state;
    e && dg(b2, c, true);
    return b2.child;
  }
  function kj(a) {
    var b2 = a.stateNode;
    b2.pendingContext ? ag(a, b2.pendingContext, b2.pendingContext !== b2.context) : b2.context && ag(a, b2.context, false);
    yh(a, b2.containerInfo);
  }
  function lj(a, b2, c, d2, e) {
    Ig();
    Jg(e);
    b2.flags |= 256;
    Xi(a, b2, c, d2);
    return b2.child;
  }
  var mj = { dehydrated: null, treeContext: null, retryLane: 0 };
  function nj(a) {
    return { baseLanes: a, cachePool: null, transitions: null };
  }
  function oj(a, b2, c) {
    var d2 = b2.pendingProps, e = L2.current, f = false, g = 0 !== (b2.flags & 128), h;
    (h = g) || (h = null !== a && null === a.memoizedState ? false : 0 !== (e & 2));
    if (h) f = true, b2.flags &= -129;
    else if (null === a || null !== a.memoizedState) e |= 1;
    G2(L2, e & 1);
    if (null === a) {
      Eg(b2);
      a = b2.memoizedState;
      if (null !== a && (a = a.dehydrated, null !== a)) return 0 === (b2.mode & 1) ? b2.lanes = 1 : "$!" === a.data ? b2.lanes = 8 : b2.lanes = 1073741824, null;
      g = d2.children;
      a = d2.fallback;
      return f ? (d2 = b2.mode, f = b2.child, g = { mode: "hidden", children: g }, 0 === (d2 & 1) && null !== f ? (f.childLanes = 0, f.pendingProps = g) : f = pj(g, d2, 0, null), a = Tg(a, d2, c, null), f.return = b2, a.return = b2, f.sibling = a, b2.child = f, b2.child.memoizedState = nj(c), b2.memoizedState = mj, a) : qj(b2, g);
    }
    e = a.memoizedState;
    if (null !== e && (h = e.dehydrated, null !== h)) return rj(a, b2, g, d2, h, e, c);
    if (f) {
      f = d2.fallback;
      g = b2.mode;
      e = a.child;
      h = e.sibling;
      var k2 = { mode: "hidden", children: d2.children };
      0 === (g & 1) && b2.child !== e ? (d2 = b2.child, d2.childLanes = 0, d2.pendingProps = k2, b2.deletions = null) : (d2 = Pg(e, k2), d2.subtreeFlags = e.subtreeFlags & 14680064);
      null !== h ? f = Pg(h, f) : (f = Tg(f, g, c, null), f.flags |= 2);
      f.return = b2;
      d2.return = b2;
      d2.sibling = f;
      b2.child = d2;
      d2 = f;
      f = b2.child;
      g = a.child.memoizedState;
      g = null === g ? nj(c) : { baseLanes: g.baseLanes | c, cachePool: null, transitions: g.transitions };
      f.memoizedState = g;
      f.childLanes = a.childLanes & ~c;
      b2.memoizedState = mj;
      return d2;
    }
    f = a.child;
    a = f.sibling;
    d2 = Pg(f, { mode: "visible", children: d2.children });
    0 === (b2.mode & 1) && (d2.lanes = c);
    d2.return = b2;
    d2.sibling = null;
    null !== a && (c = b2.deletions, null === c ? (b2.deletions = [a], b2.flags |= 16) : c.push(a));
    b2.child = d2;
    b2.memoizedState = null;
    return d2;
  }
  function qj(a, b2) {
    b2 = pj({ mode: "visible", children: b2 }, a.mode, 0, null);
    b2.return = a;
    return a.child = b2;
  }
  function sj(a, b2, c, d2) {
    null !== d2 && Jg(d2);
    Ug(b2, a.child, null, c);
    a = qj(b2, b2.pendingProps.children);
    a.flags |= 2;
    b2.memoizedState = null;
    return a;
  }
  function rj(a, b2, c, d2, e, f, g) {
    if (c) {
      if (b2.flags & 256) return b2.flags &= -257, d2 = Ki(Error(p(422))), sj(a, b2, g, d2);
      if (null !== b2.memoizedState) return b2.child = a.child, b2.flags |= 128, null;
      f = d2.fallback;
      e = b2.mode;
      d2 = pj({ mode: "visible", children: d2.children }, e, 0, null);
      f = Tg(f, e, g, null);
      f.flags |= 2;
      d2.return = b2;
      f.return = b2;
      d2.sibling = f;
      b2.child = d2;
      0 !== (b2.mode & 1) && Ug(b2, a.child, null, g);
      b2.child.memoizedState = nj(g);
      b2.memoizedState = mj;
      return f;
    }
    if (0 === (b2.mode & 1)) return sj(a, b2, g, null);
    if ("$!" === e.data) {
      d2 = e.nextSibling && e.nextSibling.dataset;
      if (d2) var h = d2.dgst;
      d2 = h;
      f = Error(p(419));
      d2 = Ki(f, d2, void 0);
      return sj(a, b2, g, d2);
    }
    h = 0 !== (g & a.childLanes);
    if (dh || h) {
      d2 = Q2;
      if (null !== d2) {
        switch (g & -g) {
          case 4:
            e = 2;
            break;
          case 16:
            e = 8;
            break;
          case 64:
          case 128:
          case 256:
          case 512:
          case 1024:
          case 2048:
          case 4096:
          case 8192:
          case 16384:
          case 32768:
          case 65536:
          case 131072:
          case 262144:
          case 524288:
          case 1048576:
          case 2097152:
          case 4194304:
          case 8388608:
          case 16777216:
          case 33554432:
          case 67108864:
            e = 32;
            break;
          case 536870912:
            e = 268435456;
            break;
          default:
            e = 0;
        }
        e = 0 !== (e & (d2.suspendedLanes | g)) ? 0 : e;
        0 !== e && e !== f.retryLane && (f.retryLane = e, ih(a, e), gi(d2, a, e, -1));
      }
      tj();
      d2 = Ki(Error(p(421)));
      return sj(a, b2, g, d2);
    }
    if ("$?" === e.data) return b2.flags |= 128, b2.child = a.child, b2 = uj.bind(null, a), e._reactRetry = b2, null;
    a = f.treeContext;
    yg = Lf(e.nextSibling);
    xg = b2;
    I2 = true;
    zg = null;
    null !== a && (og[pg++] = rg, og[pg++] = sg, og[pg++] = qg, rg = a.id, sg = a.overflow, qg = b2);
    b2 = qj(b2, d2.children);
    b2.flags |= 4096;
    return b2;
  }
  function vj(a, b2, c) {
    a.lanes |= b2;
    var d2 = a.alternate;
    null !== d2 && (d2.lanes |= b2);
    bh(a.return, b2, c);
  }
  function wj(a, b2, c, d2, e) {
    var f = a.memoizedState;
    null === f ? a.memoizedState = { isBackwards: b2, rendering: null, renderingStartTime: 0, last: d2, tail: c, tailMode: e } : (f.isBackwards = b2, f.rendering = null, f.renderingStartTime = 0, f.last = d2, f.tail = c, f.tailMode = e);
  }
  function xj(a, b2, c) {
    var d2 = b2.pendingProps, e = d2.revealOrder, f = d2.tail;
    Xi(a, b2, d2.children, c);
    d2 = L2.current;
    if (0 !== (d2 & 2)) d2 = d2 & 1 | 2, b2.flags |= 128;
    else {
      if (null !== a && 0 !== (a.flags & 128)) a: for (a = b2.child; null !== a; ) {
        if (13 === a.tag) null !== a.memoizedState && vj(a, c, b2);
        else if (19 === a.tag) vj(a, c, b2);
        else if (null !== a.child) {
          a.child.return = a;
          a = a.child;
          continue;
        }
        if (a === b2) break a;
        for (; null === a.sibling; ) {
          if (null === a.return || a.return === b2) break a;
          a = a.return;
        }
        a.sibling.return = a.return;
        a = a.sibling;
      }
      d2 &= 1;
    }
    G2(L2, d2);
    if (0 === (b2.mode & 1)) b2.memoizedState = null;
    else switch (e) {
      case "forwards":
        c = b2.child;
        for (e = null; null !== c; ) a = c.alternate, null !== a && null === Ch(a) && (e = c), c = c.sibling;
        c = e;
        null === c ? (e = b2.child, b2.child = null) : (e = c.sibling, c.sibling = null);
        wj(b2, false, e, c, f);
        break;
      case "backwards":
        c = null;
        e = b2.child;
        for (b2.child = null; null !== e; ) {
          a = e.alternate;
          if (null !== a && null === Ch(a)) {
            b2.child = e;
            break;
          }
          a = e.sibling;
          e.sibling = c;
          c = e;
          e = a;
        }
        wj(b2, true, c, null, f);
        break;
      case "together":
        wj(b2, false, null, null, void 0);
        break;
      default:
        b2.memoizedState = null;
    }
    return b2.child;
  }
  function ij(a, b2) {
    0 === (b2.mode & 1) && null !== a && (a.alternate = null, b2.alternate = null, b2.flags |= 2);
  }
  function Zi(a, b2, c) {
    null !== a && (b2.dependencies = a.dependencies);
    rh |= b2.lanes;
    if (0 === (c & b2.childLanes)) return null;
    if (null !== a && b2.child !== a.child) throw Error(p(153));
    if (null !== b2.child) {
      a = b2.child;
      c = Pg(a, a.pendingProps);
      b2.child = c;
      for (c.return = b2; null !== a.sibling; ) a = a.sibling, c = c.sibling = Pg(a, a.pendingProps), c.return = b2;
      c.sibling = null;
    }
    return b2.child;
  }
  function yj(a, b2, c) {
    switch (b2.tag) {
      case 3:
        kj(b2);
        Ig();
        break;
      case 5:
        Ah(b2);
        break;
      case 1:
        Zf(b2.type) && cg(b2);
        break;
      case 4:
        yh(b2, b2.stateNode.containerInfo);
        break;
      case 10:
        var d2 = b2.type._context, e = b2.memoizedProps.value;
        G2(Wg, d2._currentValue);
        d2._currentValue = e;
        break;
      case 13:
        d2 = b2.memoizedState;
        if (null !== d2) {
          if (null !== d2.dehydrated) return G2(L2, L2.current & 1), b2.flags |= 128, null;
          if (0 !== (c & b2.child.childLanes)) return oj(a, b2, c);
          G2(L2, L2.current & 1);
          a = Zi(a, b2, c);
          return null !== a ? a.sibling : null;
        }
        G2(L2, L2.current & 1);
        break;
      case 19:
        d2 = 0 !== (c & b2.childLanes);
        if (0 !== (a.flags & 128)) {
          if (d2) return xj(a, b2, c);
          b2.flags |= 128;
        }
        e = b2.memoizedState;
        null !== e && (e.rendering = null, e.tail = null, e.lastEffect = null);
        G2(L2, L2.current);
        if (d2) break;
        else return null;
      case 22:
      case 23:
        return b2.lanes = 0, dj(a, b2, c);
    }
    return Zi(a, b2, c);
  }
  var zj, Aj, Bj, Cj;
  zj = function(a, b2) {
    for (var c = b2.child; null !== c; ) {
      if (5 === c.tag || 6 === c.tag) a.appendChild(c.stateNode);
      else if (4 !== c.tag && null !== c.child) {
        c.child.return = c;
        c = c.child;
        continue;
      }
      if (c === b2) break;
      for (; null === c.sibling; ) {
        if (null === c.return || c.return === b2) return;
        c = c.return;
      }
      c.sibling.return = c.return;
      c = c.sibling;
    }
  };
  Aj = function() {
  };
  Bj = function(a, b2, c, d2) {
    var e = a.memoizedProps;
    if (e !== d2) {
      a = b2.stateNode;
      xh(uh.current);
      var f = null;
      switch (c) {
        case "input":
          e = Ya(a, e);
          d2 = Ya(a, d2);
          f = [];
          break;
        case "select":
          e = A({}, e, { value: void 0 });
          d2 = A({}, d2, { value: void 0 });
          f = [];
          break;
        case "textarea":
          e = gb(a, e);
          d2 = gb(a, d2);
          f = [];
          break;
        default:
          "function" !== typeof e.onClick && "function" === typeof d2.onClick && (a.onclick = Bf);
      }
      ub(c, d2);
      var g;
      c = null;
      for (l in e) if (!d2.hasOwnProperty(l) && e.hasOwnProperty(l) && null != e[l]) if ("style" === l) {
        var h = e[l];
        for (g in h) h.hasOwnProperty(g) && (c || (c = {}), c[g] = "");
      } else "dangerouslySetInnerHTML" !== l && "children" !== l && "suppressContentEditableWarning" !== l && "suppressHydrationWarning" !== l && "autoFocus" !== l && (ea.hasOwnProperty(l) ? f || (f = []) : (f = f || []).push(l, null));
      for (l in d2) {
        var k2 = d2[l];
        h = null != e ? e[l] : void 0;
        if (d2.hasOwnProperty(l) && k2 !== h && (null != k2 || null != h)) if ("style" === l) if (h) {
          for (g in h) !h.hasOwnProperty(g) || k2 && k2.hasOwnProperty(g) || (c || (c = {}), c[g] = "");
          for (g in k2) k2.hasOwnProperty(g) && h[g] !== k2[g] && (c || (c = {}), c[g] = k2[g]);
        } else c || (f || (f = []), f.push(
          l,
          c
        )), c = k2;
        else "dangerouslySetInnerHTML" === l ? (k2 = k2 ? k2.__html : void 0, h = h ? h.__html : void 0, null != k2 && h !== k2 && (f = f || []).push(l, k2)) : "children" === l ? "string" !== typeof k2 && "number" !== typeof k2 || (f = f || []).push(l, "" + k2) : "suppressContentEditableWarning" !== l && "suppressHydrationWarning" !== l && (ea.hasOwnProperty(l) ? (null != k2 && "onScroll" === l && D2("scroll", a), f || h === k2 || (f = [])) : (f = f || []).push(l, k2));
      }
      c && (f = f || []).push("style", c);
      var l = f;
      if (b2.updateQueue = l) b2.flags |= 4;
    }
  };
  Cj = function(a, b2, c, d2) {
    c !== d2 && (b2.flags |= 4);
  };
  function Dj(a, b2) {
    if (!I2) switch (a.tailMode) {
      case "hidden":
        b2 = a.tail;
        for (var c = null; null !== b2; ) null !== b2.alternate && (c = b2), b2 = b2.sibling;
        null === c ? a.tail = null : c.sibling = null;
        break;
      case "collapsed":
        c = a.tail;
        for (var d2 = null; null !== c; ) null !== c.alternate && (d2 = c), c = c.sibling;
        null === d2 ? b2 || null === a.tail ? a.tail = null : a.tail.sibling = null : d2.sibling = null;
    }
  }
  function S2(a) {
    var b2 = null !== a.alternate && a.alternate.child === a.child, c = 0, d2 = 0;
    if (b2) for (var e = a.child; null !== e; ) c |= e.lanes | e.childLanes, d2 |= e.subtreeFlags & 14680064, d2 |= e.flags & 14680064, e.return = a, e = e.sibling;
    else for (e = a.child; null !== e; ) c |= e.lanes | e.childLanes, d2 |= e.subtreeFlags, d2 |= e.flags, e.return = a, e = e.sibling;
    a.subtreeFlags |= d2;
    a.childLanes = c;
    return b2;
  }
  function Ej(a, b2, c) {
    var d2 = b2.pendingProps;
    wg(b2);
    switch (b2.tag) {
      case 2:
      case 16:
      case 15:
      case 0:
      case 11:
      case 7:
      case 8:
      case 12:
      case 9:
      case 14:
        return S2(b2), null;
      case 1:
        return Zf(b2.type) && $f(), S2(b2), null;
      case 3:
        d2 = b2.stateNode;
        zh();
        E2(Wf);
        E2(H);
        Eh();
        d2.pendingContext && (d2.context = d2.pendingContext, d2.pendingContext = null);
        if (null === a || null === a.child) Gg(b2) ? b2.flags |= 4 : null === a || a.memoizedState.isDehydrated && 0 === (b2.flags & 256) || (b2.flags |= 1024, null !== zg && (Fj(zg), zg = null));
        Aj(a, b2);
        S2(b2);
        return null;
      case 5:
        Bh(b2);
        var e = xh(wh.current);
        c = b2.type;
        if (null !== a && null != b2.stateNode) Bj(a, b2, c, d2, e), a.ref !== b2.ref && (b2.flags |= 512, b2.flags |= 2097152);
        else {
          if (!d2) {
            if (null === b2.stateNode) throw Error(p(166));
            S2(b2);
            return null;
          }
          a = xh(uh.current);
          if (Gg(b2)) {
            d2 = b2.stateNode;
            c = b2.type;
            var f = b2.memoizedProps;
            d2[Of] = b2;
            d2[Pf] = f;
            a = 0 !== (b2.mode & 1);
            switch (c) {
              case "dialog":
                D2("cancel", d2);
                D2("close", d2);
                break;
              case "iframe":
              case "object":
              case "embed":
                D2("load", d2);
                break;
              case "video":
              case "audio":
                for (e = 0; e < lf.length; e++) D2(lf[e], d2);
                break;
              case "source":
                D2("error", d2);
                break;
              case "img":
              case "image":
              case "link":
                D2(
                  "error",
                  d2
                );
                D2("load", d2);
                break;
              case "details":
                D2("toggle", d2);
                break;
              case "input":
                Za(d2, f);
                D2("invalid", d2);
                break;
              case "select":
                d2._wrapperState = { wasMultiple: !!f.multiple };
                D2("invalid", d2);
                break;
              case "textarea":
                hb(d2, f), D2("invalid", d2);
            }
            ub(c, f);
            e = null;
            for (var g in f) if (f.hasOwnProperty(g)) {
              var h = f[g];
              "children" === g ? "string" === typeof h ? d2.textContent !== h && (true !== f.suppressHydrationWarning && Af(d2.textContent, h, a), e = ["children", h]) : "number" === typeof h && d2.textContent !== "" + h && (true !== f.suppressHydrationWarning && Af(
                d2.textContent,
                h,
                a
              ), e = ["children", "" + h]) : ea.hasOwnProperty(g) && null != h && "onScroll" === g && D2("scroll", d2);
            }
            switch (c) {
              case "input":
                Va(d2);
                db(d2, f, true);
                break;
              case "textarea":
                Va(d2);
                jb(d2);
                break;
              case "select":
              case "option":
                break;
              default:
                "function" === typeof f.onClick && (d2.onclick = Bf);
            }
            d2 = e;
            b2.updateQueue = d2;
            null !== d2 && (b2.flags |= 4);
          } else {
            g = 9 === e.nodeType ? e : e.ownerDocument;
            "http://www.w3.org/1999/xhtml" === a && (a = kb(c));
            "http://www.w3.org/1999/xhtml" === a ? "script" === c ? (a = g.createElement("div"), a.innerHTML = "<script><\/script>", a = a.removeChild(a.firstChild)) : "string" === typeof d2.is ? a = g.createElement(c, { is: d2.is }) : (a = g.createElement(c), "select" === c && (g = a, d2.multiple ? g.multiple = true : d2.size && (g.size = d2.size))) : a = g.createElementNS(a, c);
            a[Of] = b2;
            a[Pf] = d2;
            zj(a, b2, false, false);
            b2.stateNode = a;
            a: {
              g = vb(c, d2);
              switch (c) {
                case "dialog":
                  D2("cancel", a);
                  D2("close", a);
                  e = d2;
                  break;
                case "iframe":
                case "object":
                case "embed":
                  D2("load", a);
                  e = d2;
                  break;
                case "video":
                case "audio":
                  for (e = 0; e < lf.length; e++) D2(lf[e], a);
                  e = d2;
                  break;
                case "source":
                  D2("error", a);
                  e = d2;
                  break;
                case "img":
                case "image":
                case "link":
                  D2(
                    "error",
                    a
                  );
                  D2("load", a);
                  e = d2;
                  break;
                case "details":
                  D2("toggle", a);
                  e = d2;
                  break;
                case "input":
                  Za(a, d2);
                  e = Ya(a, d2);
                  D2("invalid", a);
                  break;
                case "option":
                  e = d2;
                  break;
                case "select":
                  a._wrapperState = { wasMultiple: !!d2.multiple };
                  e = A({}, d2, { value: void 0 });
                  D2("invalid", a);
                  break;
                case "textarea":
                  hb(a, d2);
                  e = gb(a, d2);
                  D2("invalid", a);
                  break;
                default:
                  e = d2;
              }
              ub(c, e);
              h = e;
              for (f in h) if (h.hasOwnProperty(f)) {
                var k2 = h[f];
                "style" === f ? sb(a, k2) : "dangerouslySetInnerHTML" === f ? (k2 = k2 ? k2.__html : void 0, null != k2 && nb(a, k2)) : "children" === f ? "string" === typeof k2 ? ("textarea" !== c || "" !== k2) && ob(a, k2) : "number" === typeof k2 && ob(a, "" + k2) : "suppressContentEditableWarning" !== f && "suppressHydrationWarning" !== f && "autoFocus" !== f && (ea.hasOwnProperty(f) ? null != k2 && "onScroll" === f && D2("scroll", a) : null != k2 && ta(a, f, k2, g));
              }
              switch (c) {
                case "input":
                  Va(a);
                  db(a, d2, false);
                  break;
                case "textarea":
                  Va(a);
                  jb(a);
                  break;
                case "option":
                  null != d2.value && a.setAttribute("value", "" + Sa(d2.value));
                  break;
                case "select":
                  a.multiple = !!d2.multiple;
                  f = d2.value;
                  null != f ? fb(a, !!d2.multiple, f, false) : null != d2.defaultValue && fb(
                    a,
                    !!d2.multiple,
                    d2.defaultValue,
                    true
                  );
                  break;
                default:
                  "function" === typeof e.onClick && (a.onclick = Bf);
              }
              switch (c) {
                case "button":
                case "input":
                case "select":
                case "textarea":
                  d2 = !!d2.autoFocus;
                  break a;
                case "img":
                  d2 = true;
                  break a;
                default:
                  d2 = false;
              }
            }
            d2 && (b2.flags |= 4);
          }
          null !== b2.ref && (b2.flags |= 512, b2.flags |= 2097152);
        }
        S2(b2);
        return null;
      case 6:
        if (a && null != b2.stateNode) Cj(a, b2, a.memoizedProps, d2);
        else {
          if ("string" !== typeof d2 && null === b2.stateNode) throw Error(p(166));
          c = xh(wh.current);
          xh(uh.current);
          if (Gg(b2)) {
            d2 = b2.stateNode;
            c = b2.memoizedProps;
            d2[Of] = b2;
            if (f = d2.nodeValue !== c) {
              if (a = xg, null !== a) switch (a.tag) {
                case 3:
                  Af(d2.nodeValue, c, 0 !== (a.mode & 1));
                  break;
                case 5:
                  true !== a.memoizedProps.suppressHydrationWarning && Af(d2.nodeValue, c, 0 !== (a.mode & 1));
              }
            }
            f && (b2.flags |= 4);
          } else d2 = (9 === c.nodeType ? c : c.ownerDocument).createTextNode(d2), d2[Of] = b2, b2.stateNode = d2;
        }
        S2(b2);
        return null;
      case 13:
        E2(L2);
        d2 = b2.memoizedState;
        if (null === a || null !== a.memoizedState && null !== a.memoizedState.dehydrated) {
          if (I2 && null !== yg && 0 !== (b2.mode & 1) && 0 === (b2.flags & 128)) Hg(), Ig(), b2.flags |= 98560, f = false;
          else if (f = Gg(b2), null !== d2 && null !== d2.dehydrated) {
            if (null === a) {
              if (!f) throw Error(p(318));
              f = b2.memoizedState;
              f = null !== f ? f.dehydrated : null;
              if (!f) throw Error(p(317));
              f[Of] = b2;
            } else Ig(), 0 === (b2.flags & 128) && (b2.memoizedState = null), b2.flags |= 4;
            S2(b2);
            f = false;
          } else null !== zg && (Fj(zg), zg = null), f = true;
          if (!f) return b2.flags & 65536 ? b2 : null;
        }
        if (0 !== (b2.flags & 128)) return b2.lanes = c, b2;
        d2 = null !== d2;
        d2 !== (null !== a && null !== a.memoizedState) && d2 && (b2.child.flags |= 8192, 0 !== (b2.mode & 1) && (null === a || 0 !== (L2.current & 1) ? 0 === T2 && (T2 = 3) : tj()));
        null !== b2.updateQueue && (b2.flags |= 4);
        S2(b2);
        return null;
      case 4:
        return zh(), Aj(a, b2), null === a && sf(b2.stateNode.containerInfo), S2(b2), null;
      case 10:
        return ah(b2.type._context), S2(b2), null;
      case 17:
        return Zf(b2.type) && $f(), S2(b2), null;
      case 19:
        E2(L2);
        f = b2.memoizedState;
        if (null === f) return S2(b2), null;
        d2 = 0 !== (b2.flags & 128);
        g = f.rendering;
        if (null === g) if (d2) Dj(f, false);
        else {
          if (0 !== T2 || null !== a && 0 !== (a.flags & 128)) for (a = b2.child; null !== a; ) {
            g = Ch(a);
            if (null !== g) {
              b2.flags |= 128;
              Dj(f, false);
              d2 = g.updateQueue;
              null !== d2 && (b2.updateQueue = d2, b2.flags |= 4);
              b2.subtreeFlags = 0;
              d2 = c;
              for (c = b2.child; null !== c; ) f = c, a = d2, f.flags &= 14680066, g = f.alternate, null === g ? (f.childLanes = 0, f.lanes = a, f.child = null, f.subtreeFlags = 0, f.memoizedProps = null, f.memoizedState = null, f.updateQueue = null, f.dependencies = null, f.stateNode = null) : (f.childLanes = g.childLanes, f.lanes = g.lanes, f.child = g.child, f.subtreeFlags = 0, f.deletions = null, f.memoizedProps = g.memoizedProps, f.memoizedState = g.memoizedState, f.updateQueue = g.updateQueue, f.type = g.type, a = g.dependencies, f.dependencies = null === a ? null : { lanes: a.lanes, firstContext: a.firstContext }), c = c.sibling;
              G2(L2, L2.current & 1 | 2);
              return b2.child;
            }
            a = a.sibling;
          }
          null !== f.tail && B2() > Gj && (b2.flags |= 128, d2 = true, Dj(f, false), b2.lanes = 4194304);
        }
        else {
          if (!d2) if (a = Ch(g), null !== a) {
            if (b2.flags |= 128, d2 = true, c = a.updateQueue, null !== c && (b2.updateQueue = c, b2.flags |= 4), Dj(f, true), null === f.tail && "hidden" === f.tailMode && !g.alternate && !I2) return S2(b2), null;
          } else 2 * B2() - f.renderingStartTime > Gj && 1073741824 !== c && (b2.flags |= 128, d2 = true, Dj(f, false), b2.lanes = 4194304);
          f.isBackwards ? (g.sibling = b2.child, b2.child = g) : (c = f.last, null !== c ? c.sibling = g : b2.child = g, f.last = g);
        }
        if (null !== f.tail) return b2 = f.tail, f.rendering = b2, f.tail = b2.sibling, f.renderingStartTime = B2(), b2.sibling = null, c = L2.current, G2(L2, d2 ? c & 1 | 2 : c & 1), b2;
        S2(b2);
        return null;
      case 22:
      case 23:
        return Hj(), d2 = null !== b2.memoizedState, null !== a && null !== a.memoizedState !== d2 && (b2.flags |= 8192), d2 && 0 !== (b2.mode & 1) ? 0 !== (fj & 1073741824) && (S2(b2), b2.subtreeFlags & 6 && (b2.flags |= 8192)) : S2(b2), null;
      case 24:
        return null;
      case 25:
        return null;
    }
    throw Error(p(156, b2.tag));
  }
  function Ij(a, b2) {
    wg(b2);
    switch (b2.tag) {
      case 1:
        return Zf(b2.type) && $f(), a = b2.flags, a & 65536 ? (b2.flags = a & -65537 | 128, b2) : null;
      case 3:
        return zh(), E2(Wf), E2(H), Eh(), a = b2.flags, 0 !== (a & 65536) && 0 === (a & 128) ? (b2.flags = a & -65537 | 128, b2) : null;
      case 5:
        return Bh(b2), null;
      case 13:
        E2(L2);
        a = b2.memoizedState;
        if (null !== a && null !== a.dehydrated) {
          if (null === b2.alternate) throw Error(p(340));
          Ig();
        }
        a = b2.flags;
        return a & 65536 ? (b2.flags = a & -65537 | 128, b2) : null;
      case 19:
        return E2(L2), null;
      case 4:
        return zh(), null;
      case 10:
        return ah(b2.type._context), null;
      case 22:
      case 23:
        return Hj(), null;
      case 24:
        return null;
      default:
        return null;
    }
  }
  var Jj = false, U2 = false, Kj = "function" === typeof WeakSet ? WeakSet : Set, V2 = null;
  function Lj(a, b2) {
    var c = a.ref;
    if (null !== c) if ("function" === typeof c) try {
      c(null);
    } catch (d2) {
      W2(a, b2, d2);
    }
    else c.current = null;
  }
  function Mj(a, b2, c) {
    try {
      c();
    } catch (d2) {
      W2(a, b2, d2);
    }
  }
  var Nj = false;
  function Oj(a, b2) {
    Cf = dd;
    a = Me2();
    if (Ne2(a)) {
      if ("selectionStart" in a) var c = { start: a.selectionStart, end: a.selectionEnd };
      else a: {
        c = (c = a.ownerDocument) && c.defaultView || window;
        var d2 = c.getSelection && c.getSelection();
        if (d2 && 0 !== d2.rangeCount) {
          c = d2.anchorNode;
          var e = d2.anchorOffset, f = d2.focusNode;
          d2 = d2.focusOffset;
          try {
            c.nodeType, f.nodeType;
          } catch (F2) {
            c = null;
            break a;
          }
          var g = 0, h = -1, k2 = -1, l = 0, m2 = 0, q2 = a, r = null;
          b: for (; ; ) {
            for (var y2; ; ) {
              q2 !== c || 0 !== e && 3 !== q2.nodeType || (h = g + e);
              q2 !== f || 0 !== d2 && 3 !== q2.nodeType || (k2 = g + d2);
              3 === q2.nodeType && (g += q2.nodeValue.length);
              if (null === (y2 = q2.firstChild)) break;
              r = q2;
              q2 = y2;
            }
            for (; ; ) {
              if (q2 === a) break b;
              r === c && ++l === e && (h = g);
              r === f && ++m2 === d2 && (k2 = g);
              if (null !== (y2 = q2.nextSibling)) break;
              q2 = r;
              r = q2.parentNode;
            }
            q2 = y2;
          }
          c = -1 === h || -1 === k2 ? null : { start: h, end: k2 };
        } else c = null;
      }
      c = c || { start: 0, end: 0 };
    } else c = null;
    Df = { focusedElem: a, selectionRange: c };
    dd = false;
    for (V2 = b2; null !== V2; ) if (b2 = V2, a = b2.child, 0 !== (b2.subtreeFlags & 1028) && null !== a) a.return = b2, V2 = a;
    else for (; null !== V2; ) {
      b2 = V2;
      try {
        var n = b2.alternate;
        if (0 !== (b2.flags & 1024)) switch (b2.tag) {
          case 0:
          case 11:
          case 15:
            break;
          case 1:
            if (null !== n) {
              var t = n.memoizedProps, J2 = n.memoizedState, x2 = b2.stateNode, w2 = x2.getSnapshotBeforeUpdate(b2.elementType === b2.type ? t : Ci(b2.type, t), J2);
              x2.__reactInternalSnapshotBeforeUpdate = w2;
            }
            break;
          case 3:
            var u3 = b2.stateNode.containerInfo;
            1 === u3.nodeType ? u3.textContent = "" : 9 === u3.nodeType && u3.documentElement && u3.removeChild(u3.documentElement);
            break;
          case 5:
          case 6:
          case 4:
          case 17:
            break;
          default:
            throw Error(p(163));
        }
      } catch (F2) {
        W2(b2, b2.return, F2);
      }
      a = b2.sibling;
      if (null !== a) {
        a.return = b2.return;
        V2 = a;
        break;
      }
      V2 = b2.return;
    }
    n = Nj;
    Nj = false;
    return n;
  }
  function Pj(a, b2, c) {
    var d2 = b2.updateQueue;
    d2 = null !== d2 ? d2.lastEffect : null;
    if (null !== d2) {
      var e = d2 = d2.next;
      do {
        if ((e.tag & a) === a) {
          var f = e.destroy;
          e.destroy = void 0;
          void 0 !== f && Mj(b2, c, f);
        }
        e = e.next;
      } while (e !== d2);
    }
  }
  function Qj(a, b2) {
    b2 = b2.updateQueue;
    b2 = null !== b2 ? b2.lastEffect : null;
    if (null !== b2) {
      var c = b2 = b2.next;
      do {
        if ((c.tag & a) === a) {
          var d2 = c.create;
          c.destroy = d2();
        }
        c = c.next;
      } while (c !== b2);
    }
  }
  function Rj(a) {
    var b2 = a.ref;
    if (null !== b2) {
      var c = a.stateNode;
      switch (a.tag) {
        case 5:
          a = c;
          break;
        default:
          a = c;
      }
      "function" === typeof b2 ? b2(a) : b2.current = a;
    }
  }
  function Sj(a) {
    var b2 = a.alternate;
    null !== b2 && (a.alternate = null, Sj(b2));
    a.child = null;
    a.deletions = null;
    a.sibling = null;
    5 === a.tag && (b2 = a.stateNode, null !== b2 && (delete b2[Of], delete b2[Pf], delete b2[of], delete b2[Qf], delete b2[Rf]));
    a.stateNode = null;
    a.return = null;
    a.dependencies = null;
    a.memoizedProps = null;
    a.memoizedState = null;
    a.pendingProps = null;
    a.stateNode = null;
    a.updateQueue = null;
  }
  function Tj(a) {
    return 5 === a.tag || 3 === a.tag || 4 === a.tag;
  }
  function Uj(a) {
    a: for (; ; ) {
      for (; null === a.sibling; ) {
        if (null === a.return || Tj(a.return)) return null;
        a = a.return;
      }
      a.sibling.return = a.return;
      for (a = a.sibling; 5 !== a.tag && 6 !== a.tag && 18 !== a.tag; ) {
        if (a.flags & 2) continue a;
        if (null === a.child || 4 === a.tag) continue a;
        else a.child.return = a, a = a.child;
      }
      if (!(a.flags & 2)) return a.stateNode;
    }
  }
  function Vj(a, b2, c) {
    var d2 = a.tag;
    if (5 === d2 || 6 === d2) a = a.stateNode, b2 ? 8 === c.nodeType ? c.parentNode.insertBefore(a, b2) : c.insertBefore(a, b2) : (8 === c.nodeType ? (b2 = c.parentNode, b2.insertBefore(a, c)) : (b2 = c, b2.appendChild(a)), c = c._reactRootContainer, null !== c && void 0 !== c || null !== b2.onclick || (b2.onclick = Bf));
    else if (4 !== d2 && (a = a.child, null !== a)) for (Vj(a, b2, c), a = a.sibling; null !== a; ) Vj(a, b2, c), a = a.sibling;
  }
  function Wj(a, b2, c) {
    var d2 = a.tag;
    if (5 === d2 || 6 === d2) a = a.stateNode, b2 ? c.insertBefore(a, b2) : c.appendChild(a);
    else if (4 !== d2 && (a = a.child, null !== a)) for (Wj(a, b2, c), a = a.sibling; null !== a; ) Wj(a, b2, c), a = a.sibling;
  }
  var X2 = null, Xj = false;
  function Yj(a, b2, c) {
    for (c = c.child; null !== c; ) Zj(a, b2, c), c = c.sibling;
  }
  function Zj(a, b2, c) {
    if (lc && "function" === typeof lc.onCommitFiberUnmount) try {
      lc.onCommitFiberUnmount(kc, c);
    } catch (h) {
    }
    switch (c.tag) {
      case 5:
        U2 || Lj(c, b2);
      case 6:
        var d2 = X2, e = Xj;
        X2 = null;
        Yj(a, b2, c);
        X2 = d2;
        Xj = e;
        null !== X2 && (Xj ? (a = X2, c = c.stateNode, 8 === a.nodeType ? a.parentNode.removeChild(c) : a.removeChild(c)) : X2.removeChild(c.stateNode));
        break;
      case 18:
        null !== X2 && (Xj ? (a = X2, c = c.stateNode, 8 === a.nodeType ? Kf(a.parentNode, c) : 1 === a.nodeType && Kf(a, c), bd(a)) : Kf(X2, c.stateNode));
        break;
      case 4:
        d2 = X2;
        e = Xj;
        X2 = c.stateNode.containerInfo;
        Xj = true;
        Yj(a, b2, c);
        X2 = d2;
        Xj = e;
        break;
      case 0:
      case 11:
      case 14:
      case 15:
        if (!U2 && (d2 = c.updateQueue, null !== d2 && (d2 = d2.lastEffect, null !== d2))) {
          e = d2 = d2.next;
          do {
            var f = e, g = f.destroy;
            f = f.tag;
            void 0 !== g && (0 !== (f & 2) ? Mj(c, b2, g) : 0 !== (f & 4) && Mj(c, b2, g));
            e = e.next;
          } while (e !== d2);
        }
        Yj(a, b2, c);
        break;
      case 1:
        if (!U2 && (Lj(c, b2), d2 = c.stateNode, "function" === typeof d2.componentWillUnmount)) try {
          d2.props = c.memoizedProps, d2.state = c.memoizedState, d2.componentWillUnmount();
        } catch (h) {
          W2(c, b2, h);
        }
        Yj(a, b2, c);
        break;
      case 21:
        Yj(a, b2, c);
        break;
      case 22:
        c.mode & 1 ? (U2 = (d2 = U2) || null !== c.memoizedState, Yj(a, b2, c), U2 = d2) : Yj(a, b2, c);
        break;
      default:
        Yj(a, b2, c);
    }
  }
  function ak(a) {
    var b2 = a.updateQueue;
    if (null !== b2) {
      a.updateQueue = null;
      var c = a.stateNode;
      null === c && (c = a.stateNode = new Kj());
      b2.forEach(function(b3) {
        var d2 = bk.bind(null, a, b3);
        c.has(b3) || (c.add(b3), b3.then(d2, d2));
      });
    }
  }
  function ck(a, b2) {
    var c = b2.deletions;
    if (null !== c) for (var d2 = 0; d2 < c.length; d2++) {
      var e = c[d2];
      try {
        var f = a, g = b2, h = g;
        a: for (; null !== h; ) {
          switch (h.tag) {
            case 5:
              X2 = h.stateNode;
              Xj = false;
              break a;
            case 3:
              X2 = h.stateNode.containerInfo;
              Xj = true;
              break a;
            case 4:
              X2 = h.stateNode.containerInfo;
              Xj = true;
              break a;
          }
          h = h.return;
        }
        if (null === X2) throw Error(p(160));
        Zj(f, g, e);
        X2 = null;
        Xj = false;
        var k2 = e.alternate;
        null !== k2 && (k2.return = null);
        e.return = null;
      } catch (l) {
        W2(e, b2, l);
      }
    }
    if (b2.subtreeFlags & 12854) for (b2 = b2.child; null !== b2; ) dk(b2, a), b2 = b2.sibling;
  }
  function dk(a, b2) {
    var c = a.alternate, d2 = a.flags;
    switch (a.tag) {
      case 0:
      case 11:
      case 14:
      case 15:
        ck(b2, a);
        ek(a);
        if (d2 & 4) {
          try {
            Pj(3, a, a.return), Qj(3, a);
          } catch (t) {
            W2(a, a.return, t);
          }
          try {
            Pj(5, a, a.return);
          } catch (t) {
            W2(a, a.return, t);
          }
        }
        break;
      case 1:
        ck(b2, a);
        ek(a);
        d2 & 512 && null !== c && Lj(c, c.return);
        break;
      case 5:
        ck(b2, a);
        ek(a);
        d2 & 512 && null !== c && Lj(c, c.return);
        if (a.flags & 32) {
          var e = a.stateNode;
          try {
            ob(e, "");
          } catch (t) {
            W2(a, a.return, t);
          }
        }
        if (d2 & 4 && (e = a.stateNode, null != e)) {
          var f = a.memoizedProps, g = null !== c ? c.memoizedProps : f, h = a.type, k2 = a.updateQueue;
          a.updateQueue = null;
          if (null !== k2) try {
            "input" === h && "radio" === f.type && null != f.name && ab(e, f);
            vb(h, g);
            var l = vb(h, f);
            for (g = 0; g < k2.length; g += 2) {
              var m2 = k2[g], q2 = k2[g + 1];
              "style" === m2 ? sb(e, q2) : "dangerouslySetInnerHTML" === m2 ? nb(e, q2) : "children" === m2 ? ob(e, q2) : ta(e, m2, q2, l);
            }
            switch (h) {
              case "input":
                bb(e, f);
                break;
              case "textarea":
                ib(e, f);
                break;
              case "select":
                var r = e._wrapperState.wasMultiple;
                e._wrapperState.wasMultiple = !!f.multiple;
                var y2 = f.value;
                null != y2 ? fb(e, !!f.multiple, y2, false) : r !== !!f.multiple && (null != f.defaultValue ? fb(
                  e,
                  !!f.multiple,
                  f.defaultValue,
                  true
                ) : fb(e, !!f.multiple, f.multiple ? [] : "", false));
            }
            e[Pf] = f;
          } catch (t) {
            W2(a, a.return, t);
          }
        }
        break;
      case 6:
        ck(b2, a);
        ek(a);
        if (d2 & 4) {
          if (null === a.stateNode) throw Error(p(162));
          e = a.stateNode;
          f = a.memoizedProps;
          try {
            e.nodeValue = f;
          } catch (t) {
            W2(a, a.return, t);
          }
        }
        break;
      case 3:
        ck(b2, a);
        ek(a);
        if (d2 & 4 && null !== c && c.memoizedState.isDehydrated) try {
          bd(b2.containerInfo);
        } catch (t) {
          W2(a, a.return, t);
        }
        break;
      case 4:
        ck(b2, a);
        ek(a);
        break;
      case 13:
        ck(b2, a);
        ek(a);
        e = a.child;
        e.flags & 8192 && (f = null !== e.memoizedState, e.stateNode.isHidden = f, !f || null !== e.alternate && null !== e.alternate.memoizedState || (fk = B2()));
        d2 & 4 && ak(a);
        break;
      case 22:
        m2 = null !== c && null !== c.memoizedState;
        a.mode & 1 ? (U2 = (l = U2) || m2, ck(b2, a), U2 = l) : ck(b2, a);
        ek(a);
        if (d2 & 8192) {
          l = null !== a.memoizedState;
          if ((a.stateNode.isHidden = l) && !m2 && 0 !== (a.mode & 1)) for (V2 = a, m2 = a.child; null !== m2; ) {
            for (q2 = V2 = m2; null !== V2; ) {
              r = V2;
              y2 = r.child;
              switch (r.tag) {
                case 0:
                case 11:
                case 14:
                case 15:
                  Pj(4, r, r.return);
                  break;
                case 1:
                  Lj(r, r.return);
                  var n = r.stateNode;
                  if ("function" === typeof n.componentWillUnmount) {
                    d2 = r;
                    c = r.return;
                    try {
                      b2 = d2, n.props = b2.memoizedProps, n.state = b2.memoizedState, n.componentWillUnmount();
                    } catch (t) {
                      W2(d2, c, t);
                    }
                  }
                  break;
                case 5:
                  Lj(r, r.return);
                  break;
                case 22:
                  if (null !== r.memoizedState) {
                    gk(q2);
                    continue;
                  }
              }
              null !== y2 ? (y2.return = r, V2 = y2) : gk(q2);
            }
            m2 = m2.sibling;
          }
          a: for (m2 = null, q2 = a; ; ) {
            if (5 === q2.tag) {
              if (null === m2) {
                m2 = q2;
                try {
                  e = q2.stateNode, l ? (f = e.style, "function" === typeof f.setProperty ? f.setProperty("display", "none", "important") : f.display = "none") : (h = q2.stateNode, k2 = q2.memoizedProps.style, g = void 0 !== k2 && null !== k2 && k2.hasOwnProperty("display") ? k2.display : null, h.style.display = rb("display", g));
                } catch (t) {
                  W2(a, a.return, t);
                }
              }
            } else if (6 === q2.tag) {
              if (null === m2) try {
                q2.stateNode.nodeValue = l ? "" : q2.memoizedProps;
              } catch (t) {
                W2(a, a.return, t);
              }
            } else if ((22 !== q2.tag && 23 !== q2.tag || null === q2.memoizedState || q2 === a) && null !== q2.child) {
              q2.child.return = q2;
              q2 = q2.child;
              continue;
            }
            if (q2 === a) break a;
            for (; null === q2.sibling; ) {
              if (null === q2.return || q2.return === a) break a;
              m2 === q2 && (m2 = null);
              q2 = q2.return;
            }
            m2 === q2 && (m2 = null);
            q2.sibling.return = q2.return;
            q2 = q2.sibling;
          }
        }
        break;
      case 19:
        ck(b2, a);
        ek(a);
        d2 & 4 && ak(a);
        break;
      case 21:
        break;
      default:
        ck(
          b2,
          a
        ), ek(a);
    }
  }
  function ek(a) {
    var b2 = a.flags;
    if (b2 & 2) {
      try {
        a: {
          for (var c = a.return; null !== c; ) {
            if (Tj(c)) {
              var d2 = c;
              break a;
            }
            c = c.return;
          }
          throw Error(p(160));
        }
        switch (d2.tag) {
          case 5:
            var e = d2.stateNode;
            d2.flags & 32 && (ob(e, ""), d2.flags &= -33);
            var f = Uj(a);
            Wj(a, f, e);
            break;
          case 3:
          case 4:
            var g = d2.stateNode.containerInfo, h = Uj(a);
            Vj(a, h, g);
            break;
          default:
            throw Error(p(161));
        }
      } catch (k2) {
        W2(a, a.return, k2);
      }
      a.flags &= -3;
    }
    b2 & 4096 && (a.flags &= -4097);
  }
  function hk(a, b2, c) {
    V2 = a;
    ik(a);
  }
  function ik(a, b2, c) {
    for (var d2 = 0 !== (a.mode & 1); null !== V2; ) {
      var e = V2, f = e.child;
      if (22 === e.tag && d2) {
        var g = null !== e.memoizedState || Jj;
        if (!g) {
          var h = e.alternate, k2 = null !== h && null !== h.memoizedState || U2;
          h = Jj;
          var l = U2;
          Jj = g;
          if ((U2 = k2) && !l) for (V2 = e; null !== V2; ) g = V2, k2 = g.child, 22 === g.tag && null !== g.memoizedState ? jk(e) : null !== k2 ? (k2.return = g, V2 = k2) : jk(e);
          for (; null !== f; ) V2 = f, ik(f), f = f.sibling;
          V2 = e;
          Jj = h;
          U2 = l;
        }
        kk(a);
      } else 0 !== (e.subtreeFlags & 8772) && null !== f ? (f.return = e, V2 = f) : kk(a);
    }
  }
  function kk(a) {
    for (; null !== V2; ) {
      var b2 = V2;
      if (0 !== (b2.flags & 8772)) {
        var c = b2.alternate;
        try {
          if (0 !== (b2.flags & 8772)) switch (b2.tag) {
            case 0:
            case 11:
            case 15:
              U2 || Qj(5, b2);
              break;
            case 1:
              var d2 = b2.stateNode;
              if (b2.flags & 4 && !U2) if (null === c) d2.componentDidMount();
              else {
                var e = b2.elementType === b2.type ? c.memoizedProps : Ci(b2.type, c.memoizedProps);
                d2.componentDidUpdate(e, c.memoizedState, d2.__reactInternalSnapshotBeforeUpdate);
              }
              var f = b2.updateQueue;
              null !== f && sh(b2, f, d2);
              break;
            case 3:
              var g = b2.updateQueue;
              if (null !== g) {
                c = null;
                if (null !== b2.child) switch (b2.child.tag) {
                  case 5:
                    c = b2.child.stateNode;
                    break;
                  case 1:
                    c = b2.child.stateNode;
                }
                sh(b2, g, c);
              }
              break;
            case 5:
              var h = b2.stateNode;
              if (null === c && b2.flags & 4) {
                c = h;
                var k2 = b2.memoizedProps;
                switch (b2.type) {
                  case "button":
                  case "input":
                  case "select":
                  case "textarea":
                    k2.autoFocus && c.focus();
                    break;
                  case "img":
                    k2.src && (c.src = k2.src);
                }
              }
              break;
            case 6:
              break;
            case 4:
              break;
            case 12:
              break;
            case 13:
              if (null === b2.memoizedState) {
                var l = b2.alternate;
                if (null !== l) {
                  var m2 = l.memoizedState;
                  if (null !== m2) {
                    var q2 = m2.dehydrated;
                    null !== q2 && bd(q2);
                  }
                }
              }
              break;
            case 19:
            case 17:
            case 21:
            case 22:
            case 23:
            case 25:
              break;
            default:
              throw Error(p(163));
          }
          U2 || b2.flags & 512 && Rj(b2);
        } catch (r) {
          W2(b2, b2.return, r);
        }
      }
      if (b2 === a) {
        V2 = null;
        break;
      }
      c = b2.sibling;
      if (null !== c) {
        c.return = b2.return;
        V2 = c;
        break;
      }
      V2 = b2.return;
    }
  }
  function gk(a) {
    for (; null !== V2; ) {
      var b2 = V2;
      if (b2 === a) {
        V2 = null;
        break;
      }
      var c = b2.sibling;
      if (null !== c) {
        c.return = b2.return;
        V2 = c;
        break;
      }
      V2 = b2.return;
    }
  }
  function jk(a) {
    for (; null !== V2; ) {
      var b2 = V2;
      try {
        switch (b2.tag) {
          case 0:
          case 11:
          case 15:
            var c = b2.return;
            try {
              Qj(4, b2);
            } catch (k2) {
              W2(b2, c, k2);
            }
            break;
          case 1:
            var d2 = b2.stateNode;
            if ("function" === typeof d2.componentDidMount) {
              var e = b2.return;
              try {
                d2.componentDidMount();
              } catch (k2) {
                W2(b2, e, k2);
              }
            }
            var f = b2.return;
            try {
              Rj(b2);
            } catch (k2) {
              W2(b2, f, k2);
            }
            break;
          case 5:
            var g = b2.return;
            try {
              Rj(b2);
            } catch (k2) {
              W2(b2, g, k2);
            }
        }
      } catch (k2) {
        W2(b2, b2.return, k2);
      }
      if (b2 === a) {
        V2 = null;
        break;
      }
      var h = b2.sibling;
      if (null !== h) {
        h.return = b2.return;
        V2 = h;
        break;
      }
      V2 = b2.return;
    }
  }
  var lk = Math.ceil, mk = ua.ReactCurrentDispatcher, nk = ua.ReactCurrentOwner, ok = ua.ReactCurrentBatchConfig, K2 = 0, Q2 = null, Y = null, Z = 0, fj = 0, ej = Uf(0), T2 = 0, pk = null, rh = 0, qk = 0, rk = 0, sk = null, tk = null, fk = 0, Gj = Infinity, uk = null, Oi = false, Pi = null, Ri = null, vk = false, wk = null, xk = 0, yk = 0, zk = null, Ak = -1, Bk = 0;
  function R() {
    return 0 !== (K2 & 6) ? B2() : -1 !== Ak ? Ak : Ak = B2();
  }
  function yi(a) {
    if (0 === (a.mode & 1)) return 1;
    if (0 !== (K2 & 2) && 0 !== Z) return Z & -Z;
    if (null !== Kg.transition) return 0 === Bk && (Bk = yc()), Bk;
    a = C2;
    if (0 !== a) return a;
    a = window.event;
    a = void 0 === a ? 16 : jd(a.type);
    return a;
  }
  function gi(a, b2, c, d2) {
    if (50 < yk) throw yk = 0, zk = null, Error(p(185));
    Ac(a, c, d2);
    if (0 === (K2 & 2) || a !== Q2) a === Q2 && (0 === (K2 & 2) && (qk |= c), 4 === T2 && Ck(a, Z)), Dk(a, d2), 1 === c && 0 === K2 && 0 === (b2.mode & 1) && (Gj = B2() + 500, fg && jg());
  }
  function Dk(a, b2) {
    var c = a.callbackNode;
    wc(a, b2);
    var d2 = uc(a, a === Q2 ? Z : 0);
    if (0 === d2) null !== c && bc(c), a.callbackNode = null, a.callbackPriority = 0;
    else if (b2 = d2 & -d2, a.callbackPriority !== b2) {
      null != c && bc(c);
      if (1 === b2) 0 === a.tag ? ig(Ek.bind(null, a)) : hg(Ek.bind(null, a)), Jf(function() {
        0 === (K2 & 6) && jg();
      }), c = null;
      else {
        switch (Dc(d2)) {
          case 1:
            c = fc;
            break;
          case 4:
            c = gc;
            break;
          case 16:
            c = hc;
            break;
          case 536870912:
            c = jc;
            break;
          default:
            c = hc;
        }
        c = Fk(c, Gk.bind(null, a));
      }
      a.callbackPriority = b2;
      a.callbackNode = c;
    }
  }
  function Gk(a, b2) {
    Ak = -1;
    Bk = 0;
    if (0 !== (K2 & 6)) throw Error(p(327));
    var c = a.callbackNode;
    if (Hk() && a.callbackNode !== c) return null;
    var d2 = uc(a, a === Q2 ? Z : 0);
    if (0 === d2) return null;
    if (0 !== (d2 & 30) || 0 !== (d2 & a.expiredLanes) || b2) b2 = Ik(a, d2);
    else {
      b2 = d2;
      var e = K2;
      K2 |= 2;
      var f = Jk();
      if (Q2 !== a || Z !== b2) uk = null, Gj = B2() + 500, Kk(a, b2);
      do
        try {
          Lk();
          break;
        } catch (h) {
          Mk(a, h);
        }
      while (1);
      $g();
      mk.current = f;
      K2 = e;
      null !== Y ? b2 = 0 : (Q2 = null, Z = 0, b2 = T2);
    }
    if (0 !== b2) {
      2 === b2 && (e = xc(a), 0 !== e && (d2 = e, b2 = Nk(a, e)));
      if (1 === b2) throw c = pk, Kk(a, 0), Ck(a, d2), Dk(a, B2()), c;
      if (6 === b2) Ck(a, d2);
      else {
        e = a.current.alternate;
        if (0 === (d2 & 30) && !Ok(e) && (b2 = Ik(a, d2), 2 === b2 && (f = xc(a), 0 !== f && (d2 = f, b2 = Nk(a, f))), 1 === b2)) throw c = pk, Kk(a, 0), Ck(a, d2), Dk(a, B2()), c;
        a.finishedWork = e;
        a.finishedLanes = d2;
        switch (b2) {
          case 0:
          case 1:
            throw Error(p(345));
          case 2:
            Pk(a, tk, uk);
            break;
          case 3:
            Ck(a, d2);
            if ((d2 & 130023424) === d2 && (b2 = fk + 500 - B2(), 10 < b2)) {
              if (0 !== uc(a, 0)) break;
              e = a.suspendedLanes;
              if ((e & d2) !== d2) {
                R();
                a.pingedLanes |= a.suspendedLanes & e;
                break;
              }
              a.timeoutHandle = Ff(Pk.bind(null, a, tk, uk), b2);
              break;
            }
            Pk(a, tk, uk);
            break;
          case 4:
            Ck(a, d2);
            if ((d2 & 4194240) === d2) break;
            b2 = a.eventTimes;
            for (e = -1; 0 < d2; ) {
              var g = 31 - oc(d2);
              f = 1 << g;
              g = b2[g];
              g > e && (e = g);
              d2 &= ~f;
            }
            d2 = e;
            d2 = B2() - d2;
            d2 = (120 > d2 ? 120 : 480 > d2 ? 480 : 1080 > d2 ? 1080 : 1920 > d2 ? 1920 : 3e3 > d2 ? 3e3 : 4320 > d2 ? 4320 : 1960 * lk(d2 / 1960)) - d2;
            if (10 < d2) {
              a.timeoutHandle = Ff(Pk.bind(null, a, tk, uk), d2);
              break;
            }
            Pk(a, tk, uk);
            break;
          case 5:
            Pk(a, tk, uk);
            break;
          default:
            throw Error(p(329));
        }
      }
    }
    Dk(a, B2());
    return a.callbackNode === c ? Gk.bind(null, a) : null;
  }
  function Nk(a, b2) {
    var c = sk;
    a.current.memoizedState.isDehydrated && (Kk(a, b2).flags |= 256);
    a = Ik(a, b2);
    2 !== a && (b2 = tk, tk = c, null !== b2 && Fj(b2));
    return a;
  }
  function Fj(a) {
    null === tk ? tk = a : tk.push.apply(tk, a);
  }
  function Ok(a) {
    for (var b2 = a; ; ) {
      if (b2.flags & 16384) {
        var c = b2.updateQueue;
        if (null !== c && (c = c.stores, null !== c)) for (var d2 = 0; d2 < c.length; d2++) {
          var e = c[d2], f = e.getSnapshot;
          e = e.value;
          try {
            if (!He2(f(), e)) return false;
          } catch (g) {
            return false;
          }
        }
      }
      c = b2.child;
      if (b2.subtreeFlags & 16384 && null !== c) c.return = b2, b2 = c;
      else {
        if (b2 === a) break;
        for (; null === b2.sibling; ) {
          if (null === b2.return || b2.return === a) return true;
          b2 = b2.return;
        }
        b2.sibling.return = b2.return;
        b2 = b2.sibling;
      }
    }
    return true;
  }
  function Ck(a, b2) {
    b2 &= ~rk;
    b2 &= ~qk;
    a.suspendedLanes |= b2;
    a.pingedLanes &= ~b2;
    for (a = a.expirationTimes; 0 < b2; ) {
      var c = 31 - oc(b2), d2 = 1 << c;
      a[c] = -1;
      b2 &= ~d2;
    }
  }
  function Ek(a) {
    if (0 !== (K2 & 6)) throw Error(p(327));
    Hk();
    var b2 = uc(a, 0);
    if (0 === (b2 & 1)) return Dk(a, B2()), null;
    var c = Ik(a, b2);
    if (0 !== a.tag && 2 === c) {
      var d2 = xc(a);
      0 !== d2 && (b2 = d2, c = Nk(a, d2));
    }
    if (1 === c) throw c = pk, Kk(a, 0), Ck(a, b2), Dk(a, B2()), c;
    if (6 === c) throw Error(p(345));
    a.finishedWork = a.current.alternate;
    a.finishedLanes = b2;
    Pk(a, tk, uk);
    Dk(a, B2());
    return null;
  }
  function Qk(a, b2) {
    var c = K2;
    K2 |= 1;
    try {
      return a(b2);
    } finally {
      K2 = c, 0 === K2 && (Gj = B2() + 500, fg && jg());
    }
  }
  function Rk(a) {
    null !== wk && 0 === wk.tag && 0 === (K2 & 6) && Hk();
    var b2 = K2;
    K2 |= 1;
    var c = ok.transition, d2 = C2;
    try {
      if (ok.transition = null, C2 = 1, a) return a();
    } finally {
      C2 = d2, ok.transition = c, K2 = b2, 0 === (K2 & 6) && jg();
    }
  }
  function Hj() {
    fj = ej.current;
    E2(ej);
  }
  function Kk(a, b2) {
    a.finishedWork = null;
    a.finishedLanes = 0;
    var c = a.timeoutHandle;
    -1 !== c && (a.timeoutHandle = -1, Gf(c));
    if (null !== Y) for (c = Y.return; null !== c; ) {
      var d2 = c;
      wg(d2);
      switch (d2.tag) {
        case 1:
          d2 = d2.type.childContextTypes;
          null !== d2 && void 0 !== d2 && $f();
          break;
        case 3:
          zh();
          E2(Wf);
          E2(H);
          Eh();
          break;
        case 5:
          Bh(d2);
          break;
        case 4:
          zh();
          break;
        case 13:
          E2(L2);
          break;
        case 19:
          E2(L2);
          break;
        case 10:
          ah(d2.type._context);
          break;
        case 22:
        case 23:
          Hj();
      }
      c = c.return;
    }
    Q2 = a;
    Y = a = Pg(a.current, null);
    Z = fj = b2;
    T2 = 0;
    pk = null;
    rk = qk = rh = 0;
    tk = sk = null;
    if (null !== fh) {
      for (b2 = 0; b2 < fh.length; b2++) if (c = fh[b2], d2 = c.interleaved, null !== d2) {
        c.interleaved = null;
        var e = d2.next, f = c.pending;
        if (null !== f) {
          var g = f.next;
          f.next = e;
          d2.next = g;
        }
        c.pending = d2;
      }
      fh = null;
    }
    return a;
  }
  function Mk(a, b2) {
    do {
      var c = Y;
      try {
        $g();
        Fh.current = Rh;
        if (Ih) {
          for (var d2 = M2.memoizedState; null !== d2; ) {
            var e = d2.queue;
            null !== e && (e.pending = null);
            d2 = d2.next;
          }
          Ih = false;
        }
        Hh = 0;
        O = N2 = M2 = null;
        Jh = false;
        Kh = 0;
        nk.current = null;
        if (null === c || null === c.return) {
          T2 = 1;
          pk = b2;
          Y = null;
          break;
        }
        a: {
          var f = a, g = c.return, h = c, k2 = b2;
          b2 = Z;
          h.flags |= 32768;
          if (null !== k2 && "object" === typeof k2 && "function" === typeof k2.then) {
            var l = k2, m2 = h, q2 = m2.tag;
            if (0 === (m2.mode & 1) && (0 === q2 || 11 === q2 || 15 === q2)) {
              var r = m2.alternate;
              r ? (m2.updateQueue = r.updateQueue, m2.memoizedState = r.memoizedState, m2.lanes = r.lanes) : (m2.updateQueue = null, m2.memoizedState = null);
            }
            var y2 = Ui(g);
            if (null !== y2) {
              y2.flags &= -257;
              Vi(y2, g, h, f, b2);
              y2.mode & 1 && Si(f, l, b2);
              b2 = y2;
              k2 = l;
              var n = b2.updateQueue;
              if (null === n) {
                var t = /* @__PURE__ */ new Set();
                t.add(k2);
                b2.updateQueue = t;
              } else n.add(k2);
              break a;
            } else {
              if (0 === (b2 & 1)) {
                Si(f, l, b2);
                tj();
                break a;
              }
              k2 = Error(p(426));
            }
          } else if (I2 && h.mode & 1) {
            var J2 = Ui(g);
            if (null !== J2) {
              0 === (J2.flags & 65536) && (J2.flags |= 256);
              Vi(J2, g, h, f, b2);
              Jg(Ji(k2, h));
              break a;
            }
          }
          f = k2 = Ji(k2, h);
          4 !== T2 && (T2 = 2);
          null === sk ? sk = [f] : sk.push(f);
          f = g;
          do {
            switch (f.tag) {
              case 3:
                f.flags |= 65536;
                b2 &= -b2;
                f.lanes |= b2;
                var x2 = Ni(f, k2, b2);
                ph(f, x2);
                break a;
              case 1:
                h = k2;
                var w2 = f.type, u3 = f.stateNode;
                if (0 === (f.flags & 128) && ("function" === typeof w2.getDerivedStateFromError || null !== u3 && "function" === typeof u3.componentDidCatch && (null === Ri || !Ri.has(u3)))) {
                  f.flags |= 65536;
                  b2 &= -b2;
                  f.lanes |= b2;
                  var F2 = Qi(f, h, b2);
                  ph(f, F2);
                  break a;
                }
            }
            f = f.return;
          } while (null !== f);
        }
        Sk(c);
      } catch (na) {
        b2 = na;
        Y === c && null !== c && (Y = c = c.return);
        continue;
      }
      break;
    } while (1);
  }
  function Jk() {
    var a = mk.current;
    mk.current = Rh;
    return null === a ? Rh : a;
  }
  function tj() {
    if (0 === T2 || 3 === T2 || 2 === T2) T2 = 4;
    null === Q2 || 0 === (rh & 268435455) && 0 === (qk & 268435455) || Ck(Q2, Z);
  }
  function Ik(a, b2) {
    var c = K2;
    K2 |= 2;
    var d2 = Jk();
    if (Q2 !== a || Z !== b2) uk = null, Kk(a, b2);
    do
      try {
        Tk();
        break;
      } catch (e) {
        Mk(a, e);
      }
    while (1);
    $g();
    K2 = c;
    mk.current = d2;
    if (null !== Y) throw Error(p(261));
    Q2 = null;
    Z = 0;
    return T2;
  }
  function Tk() {
    for (; null !== Y; ) Uk(Y);
  }
  function Lk() {
    for (; null !== Y && !cc(); ) Uk(Y);
  }
  function Uk(a) {
    var b2 = Vk(a.alternate, a, fj);
    a.memoizedProps = a.pendingProps;
    null === b2 ? Sk(a) : Y = b2;
    nk.current = null;
  }
  function Sk(a) {
    var b2 = a;
    do {
      var c = b2.alternate;
      a = b2.return;
      if (0 === (b2.flags & 32768)) {
        if (c = Ej(c, b2, fj), null !== c) {
          Y = c;
          return;
        }
      } else {
        c = Ij(c, b2);
        if (null !== c) {
          c.flags &= 32767;
          Y = c;
          return;
        }
        if (null !== a) a.flags |= 32768, a.subtreeFlags = 0, a.deletions = null;
        else {
          T2 = 6;
          Y = null;
          return;
        }
      }
      b2 = b2.sibling;
      if (null !== b2) {
        Y = b2;
        return;
      }
      Y = b2 = a;
    } while (null !== b2);
    0 === T2 && (T2 = 5);
  }
  function Pk(a, b2, c) {
    var d2 = C2, e = ok.transition;
    try {
      ok.transition = null, C2 = 1, Wk(a, b2, c, d2);
    } finally {
      ok.transition = e, C2 = d2;
    }
    return null;
  }
  function Wk(a, b2, c, d2) {
    do
      Hk();
    while (null !== wk);
    if (0 !== (K2 & 6)) throw Error(p(327));
    c = a.finishedWork;
    var e = a.finishedLanes;
    if (null === c) return null;
    a.finishedWork = null;
    a.finishedLanes = 0;
    if (c === a.current) throw Error(p(177));
    a.callbackNode = null;
    a.callbackPriority = 0;
    var f = c.lanes | c.childLanes;
    Bc(a, f);
    a === Q2 && (Y = Q2 = null, Z = 0);
    0 === (c.subtreeFlags & 2064) && 0 === (c.flags & 2064) || vk || (vk = true, Fk(hc, function() {
      Hk();
      return null;
    }));
    f = 0 !== (c.flags & 15990);
    if (0 !== (c.subtreeFlags & 15990) || f) {
      f = ok.transition;
      ok.transition = null;
      var g = C2;
      C2 = 1;
      var h = K2;
      K2 |= 4;
      nk.current = null;
      Oj(a, c);
      dk(c, a);
      Oe2(Df);
      dd = !!Cf;
      Df = Cf = null;
      a.current = c;
      hk(c);
      dc();
      K2 = h;
      C2 = g;
      ok.transition = f;
    } else a.current = c;
    vk && (vk = false, wk = a, xk = e);
    f = a.pendingLanes;
    0 === f && (Ri = null);
    mc(c.stateNode);
    Dk(a, B2());
    if (null !== b2) for (d2 = a.onRecoverableError, c = 0; c < b2.length; c++) e = b2[c], d2(e.value, { componentStack: e.stack, digest: e.digest });
    if (Oi) throw Oi = false, a = Pi, Pi = null, a;
    0 !== (xk & 1) && 0 !== a.tag && Hk();
    f = a.pendingLanes;
    0 !== (f & 1) ? a === zk ? yk++ : (yk = 0, zk = a) : yk = 0;
    jg();
    return null;
  }
  function Hk() {
    if (null !== wk) {
      var a = Dc(xk), b2 = ok.transition, c = C2;
      try {
        ok.transition = null;
        C2 = 16 > a ? 16 : a;
        if (null === wk) var d2 = false;
        else {
          a = wk;
          wk = null;
          xk = 0;
          if (0 !== (K2 & 6)) throw Error(p(331));
          var e = K2;
          K2 |= 4;
          for (V2 = a.current; null !== V2; ) {
            var f = V2, g = f.child;
            if (0 !== (V2.flags & 16)) {
              var h = f.deletions;
              if (null !== h) {
                for (var k2 = 0; k2 < h.length; k2++) {
                  var l = h[k2];
                  for (V2 = l; null !== V2; ) {
                    var m2 = V2;
                    switch (m2.tag) {
                      case 0:
                      case 11:
                      case 15:
                        Pj(8, m2, f);
                    }
                    var q2 = m2.child;
                    if (null !== q2) q2.return = m2, V2 = q2;
                    else for (; null !== V2; ) {
                      m2 = V2;
                      var r = m2.sibling, y2 = m2.return;
                      Sj(m2);
                      if (m2 === l) {
                        V2 = null;
                        break;
                      }
                      if (null !== r) {
                        r.return = y2;
                        V2 = r;
                        break;
                      }
                      V2 = y2;
                    }
                  }
                }
                var n = f.alternate;
                if (null !== n) {
                  var t = n.child;
                  if (null !== t) {
                    n.child = null;
                    do {
                      var J2 = t.sibling;
                      t.sibling = null;
                      t = J2;
                    } while (null !== t);
                  }
                }
                V2 = f;
              }
            }
            if (0 !== (f.subtreeFlags & 2064) && null !== g) g.return = f, V2 = g;
            else b: for (; null !== V2; ) {
              f = V2;
              if (0 !== (f.flags & 2048)) switch (f.tag) {
                case 0:
                case 11:
                case 15:
                  Pj(9, f, f.return);
              }
              var x2 = f.sibling;
              if (null !== x2) {
                x2.return = f.return;
                V2 = x2;
                break b;
              }
              V2 = f.return;
            }
          }
          var w2 = a.current;
          for (V2 = w2; null !== V2; ) {
            g = V2;
            var u3 = g.child;
            if (0 !== (g.subtreeFlags & 2064) && null !== u3) u3.return = g, V2 = u3;
            else b: for (g = w2; null !== V2; ) {
              h = V2;
              if (0 !== (h.flags & 2048)) try {
                switch (h.tag) {
                  case 0:
                  case 11:
                  case 15:
                    Qj(9, h);
                }
              } catch (na) {
                W2(h, h.return, na);
              }
              if (h === g) {
                V2 = null;
                break b;
              }
              var F2 = h.sibling;
              if (null !== F2) {
                F2.return = h.return;
                V2 = F2;
                break b;
              }
              V2 = h.return;
            }
          }
          K2 = e;
          jg();
          if (lc && "function" === typeof lc.onPostCommitFiberRoot) try {
            lc.onPostCommitFiberRoot(kc, a);
          } catch (na) {
          }
          d2 = true;
        }
        return d2;
      } finally {
        C2 = c, ok.transition = b2;
      }
    }
    return false;
  }
  function Xk(a, b2, c) {
    b2 = Ji(c, b2);
    b2 = Ni(a, b2, 1);
    a = nh(a, b2, 1);
    b2 = R();
    null !== a && (Ac(a, 1, b2), Dk(a, b2));
  }
  function W2(a, b2, c) {
    if (3 === a.tag) Xk(a, a, c);
    else for (; null !== b2; ) {
      if (3 === b2.tag) {
        Xk(b2, a, c);
        break;
      } else if (1 === b2.tag) {
        var d2 = b2.stateNode;
        if ("function" === typeof b2.type.getDerivedStateFromError || "function" === typeof d2.componentDidCatch && (null === Ri || !Ri.has(d2))) {
          a = Ji(c, a);
          a = Qi(b2, a, 1);
          b2 = nh(b2, a, 1);
          a = R();
          null !== b2 && (Ac(b2, 1, a), Dk(b2, a));
          break;
        }
      }
      b2 = b2.return;
    }
  }
  function Ti(a, b2, c) {
    var d2 = a.pingCache;
    null !== d2 && d2.delete(b2);
    b2 = R();
    a.pingedLanes |= a.suspendedLanes & c;
    Q2 === a && (Z & c) === c && (4 === T2 || 3 === T2 && (Z & 130023424) === Z && 500 > B2() - fk ? Kk(a, 0) : rk |= c);
    Dk(a, b2);
  }
  function Yk(a, b2) {
    0 === b2 && (0 === (a.mode & 1) ? b2 = 1 : (b2 = sc, sc <<= 1, 0 === (sc & 130023424) && (sc = 4194304)));
    var c = R();
    a = ih(a, b2);
    null !== a && (Ac(a, b2, c), Dk(a, c));
  }
  function uj(a) {
    var b2 = a.memoizedState, c = 0;
    null !== b2 && (c = b2.retryLane);
    Yk(a, c);
  }
  function bk(a, b2) {
    var c = 0;
    switch (a.tag) {
      case 13:
        var d2 = a.stateNode;
        var e = a.memoizedState;
        null !== e && (c = e.retryLane);
        break;
      case 19:
        d2 = a.stateNode;
        break;
      default:
        throw Error(p(314));
    }
    null !== d2 && d2.delete(b2);
    Yk(a, c);
  }
  var Vk;
  Vk = function(a, b2, c) {
    if (null !== a) if (a.memoizedProps !== b2.pendingProps || Wf.current) dh = true;
    else {
      if (0 === (a.lanes & c) && 0 === (b2.flags & 128)) return dh = false, yj(a, b2, c);
      dh = 0 !== (a.flags & 131072) ? true : false;
    }
    else dh = false, I2 && 0 !== (b2.flags & 1048576) && ug(b2, ng, b2.index);
    b2.lanes = 0;
    switch (b2.tag) {
      case 2:
        var d2 = b2.type;
        ij(a, b2);
        a = b2.pendingProps;
        var e = Yf(b2, H.current);
        ch(b2, c);
        e = Nh(null, b2, d2, a, e, c);
        var f = Sh();
        b2.flags |= 1;
        "object" === typeof e && null !== e && "function" === typeof e.render && void 0 === e.$$typeof ? (b2.tag = 1, b2.memoizedState = null, b2.updateQueue = null, Zf(d2) ? (f = true, cg(b2)) : f = false, b2.memoizedState = null !== e.state && void 0 !== e.state ? e.state : null, kh(b2), e.updater = Ei, b2.stateNode = e, e._reactInternals = b2, Ii(b2, d2, a, c), b2 = jj(null, b2, d2, true, f, c)) : (b2.tag = 0, I2 && f && vg(b2), Xi(null, b2, e, c), b2 = b2.child);
        return b2;
      case 16:
        d2 = b2.elementType;
        a: {
          ij(a, b2);
          a = b2.pendingProps;
          e = d2._init;
          d2 = e(d2._payload);
          b2.type = d2;
          e = b2.tag = Zk(d2);
          a = Ci(d2, a);
          switch (e) {
            case 0:
              b2 = cj(null, b2, d2, a, c);
              break a;
            case 1:
              b2 = hj(null, b2, d2, a, c);
              break a;
            case 11:
              b2 = Yi(null, b2, d2, a, c);
              break a;
            case 14:
              b2 = $i(null, b2, d2, Ci(d2.type, a), c);
              break a;
          }
          throw Error(p(
            306,
            d2,
            ""
          ));
        }
        return b2;
      case 0:
        return d2 = b2.type, e = b2.pendingProps, e = b2.elementType === d2 ? e : Ci(d2, e), cj(a, b2, d2, e, c);
      case 1:
        return d2 = b2.type, e = b2.pendingProps, e = b2.elementType === d2 ? e : Ci(d2, e), hj(a, b2, d2, e, c);
      case 3:
        a: {
          kj(b2);
          if (null === a) throw Error(p(387));
          d2 = b2.pendingProps;
          f = b2.memoizedState;
          e = f.element;
          lh(a, b2);
          qh(b2, d2, null, c);
          var g = b2.memoizedState;
          d2 = g.element;
          if (f.isDehydrated) if (f = { element: d2, isDehydrated: false, cache: g.cache, pendingSuspenseBoundaries: g.pendingSuspenseBoundaries, transitions: g.transitions }, b2.updateQueue.baseState = f, b2.memoizedState = f, b2.flags & 256) {
            e = Ji(Error(p(423)), b2);
            b2 = lj(a, b2, d2, c, e);
            break a;
          } else if (d2 !== e) {
            e = Ji(Error(p(424)), b2);
            b2 = lj(a, b2, d2, c, e);
            break a;
          } else for (yg = Lf(b2.stateNode.containerInfo.firstChild), xg = b2, I2 = true, zg = null, c = Vg(b2, null, d2, c), b2.child = c; c; ) c.flags = c.flags & -3 | 4096, c = c.sibling;
          else {
            Ig();
            if (d2 === e) {
              b2 = Zi(a, b2, c);
              break a;
            }
            Xi(a, b2, d2, c);
          }
          b2 = b2.child;
        }
        return b2;
      case 5:
        return Ah(b2), null === a && Eg(b2), d2 = b2.type, e = b2.pendingProps, f = null !== a ? a.memoizedProps : null, g = e.children, Ef(d2, e) ? g = null : null !== f && Ef(d2, f) && (b2.flags |= 32), gj(a, b2), Xi(a, b2, g, c), b2.child;
      case 6:
        return null === a && Eg(b2), null;
      case 13:
        return oj(a, b2, c);
      case 4:
        return yh(b2, b2.stateNode.containerInfo), d2 = b2.pendingProps, null === a ? b2.child = Ug(b2, null, d2, c) : Xi(a, b2, d2, c), b2.child;
      case 11:
        return d2 = b2.type, e = b2.pendingProps, e = b2.elementType === d2 ? e : Ci(d2, e), Yi(a, b2, d2, e, c);
      case 7:
        return Xi(a, b2, b2.pendingProps, c), b2.child;
      case 8:
        return Xi(a, b2, b2.pendingProps.children, c), b2.child;
      case 12:
        return Xi(a, b2, b2.pendingProps.children, c), b2.child;
      case 10:
        a: {
          d2 = b2.type._context;
          e = b2.pendingProps;
          f = b2.memoizedProps;
          g = e.value;
          G2(Wg, d2._currentValue);
          d2._currentValue = g;
          if (null !== f) if (He2(f.value, g)) {
            if (f.children === e.children && !Wf.current) {
              b2 = Zi(a, b2, c);
              break a;
            }
          } else for (f = b2.child, null !== f && (f.return = b2); null !== f; ) {
            var h = f.dependencies;
            if (null !== h) {
              g = f.child;
              for (var k2 = h.firstContext; null !== k2; ) {
                if (k2.context === d2) {
                  if (1 === f.tag) {
                    k2 = mh(-1, c & -c);
                    k2.tag = 2;
                    var l = f.updateQueue;
                    if (null !== l) {
                      l = l.shared;
                      var m2 = l.pending;
                      null === m2 ? k2.next = k2 : (k2.next = m2.next, m2.next = k2);
                      l.pending = k2;
                    }
                  }
                  f.lanes |= c;
                  k2 = f.alternate;
                  null !== k2 && (k2.lanes |= c);
                  bh(
                    f.return,
                    c,
                    b2
                  );
                  h.lanes |= c;
                  break;
                }
                k2 = k2.next;
              }
            } else if (10 === f.tag) g = f.type === b2.type ? null : f.child;
            else if (18 === f.tag) {
              g = f.return;
              if (null === g) throw Error(p(341));
              g.lanes |= c;
              h = g.alternate;
              null !== h && (h.lanes |= c);
              bh(g, c, b2);
              g = f.sibling;
            } else g = f.child;
            if (null !== g) g.return = f;
            else for (g = f; null !== g; ) {
              if (g === b2) {
                g = null;
                break;
              }
              f = g.sibling;
              if (null !== f) {
                f.return = g.return;
                g = f;
                break;
              }
              g = g.return;
            }
            f = g;
          }
          Xi(a, b2, e.children, c);
          b2 = b2.child;
        }
        return b2;
      case 9:
        return e = b2.type, d2 = b2.pendingProps.children, ch(b2, c), e = eh(e), d2 = d2(e), b2.flags |= 1, Xi(a, b2, d2, c), b2.child;
      case 14:
        return d2 = b2.type, e = Ci(d2, b2.pendingProps), e = Ci(d2.type, e), $i(a, b2, d2, e, c);
      case 15:
        return bj(a, b2, b2.type, b2.pendingProps, c);
      case 17:
        return d2 = b2.type, e = b2.pendingProps, e = b2.elementType === d2 ? e : Ci(d2, e), ij(a, b2), b2.tag = 1, Zf(d2) ? (a = true, cg(b2)) : a = false, ch(b2, c), Gi(b2, d2, e), Ii(b2, d2, e, c), jj(null, b2, d2, true, a, c);
      case 19:
        return xj(a, b2, c);
      case 22:
        return dj(a, b2, c);
    }
    throw Error(p(156, b2.tag));
  };
  function Fk(a, b2) {
    return ac(a, b2);
  }
  function $k(a, b2, c, d2) {
    this.tag = a;
    this.key = c;
    this.sibling = this.child = this.return = this.stateNode = this.type = this.elementType = null;
    this.index = 0;
    this.ref = null;
    this.pendingProps = b2;
    this.dependencies = this.memoizedState = this.updateQueue = this.memoizedProps = null;
    this.mode = d2;
    this.subtreeFlags = this.flags = 0;
    this.deletions = null;
    this.childLanes = this.lanes = 0;
    this.alternate = null;
  }
  function Bg(a, b2, c, d2) {
    return new $k(a, b2, c, d2);
  }
  function aj(a) {
    a = a.prototype;
    return !(!a || !a.isReactComponent);
  }
  function Zk(a) {
    if ("function" === typeof a) return aj(a) ? 1 : 0;
    if (void 0 !== a && null !== a) {
      a = a.$$typeof;
      if (a === Da) return 11;
      if (a === Ga) return 14;
    }
    return 2;
  }
  function Pg(a, b2) {
    var c = a.alternate;
    null === c ? (c = Bg(a.tag, b2, a.key, a.mode), c.elementType = a.elementType, c.type = a.type, c.stateNode = a.stateNode, c.alternate = a, a.alternate = c) : (c.pendingProps = b2, c.type = a.type, c.flags = 0, c.subtreeFlags = 0, c.deletions = null);
    c.flags = a.flags & 14680064;
    c.childLanes = a.childLanes;
    c.lanes = a.lanes;
    c.child = a.child;
    c.memoizedProps = a.memoizedProps;
    c.memoizedState = a.memoizedState;
    c.updateQueue = a.updateQueue;
    b2 = a.dependencies;
    c.dependencies = null === b2 ? null : { lanes: b2.lanes, firstContext: b2.firstContext };
    c.sibling = a.sibling;
    c.index = a.index;
    c.ref = a.ref;
    return c;
  }
  function Rg(a, b2, c, d2, e, f) {
    var g = 2;
    d2 = a;
    if ("function" === typeof a) aj(a) && (g = 1);
    else if ("string" === typeof a) g = 5;
    else a: switch (a) {
      case ya:
        return Tg(c.children, e, f, b2);
      case za:
        g = 8;
        e |= 8;
        break;
      case Aa:
        return a = Bg(12, c, b2, e | 2), a.elementType = Aa, a.lanes = f, a;
      case Ea:
        return a = Bg(13, c, b2, e), a.elementType = Ea, a.lanes = f, a;
      case Fa:
        return a = Bg(19, c, b2, e), a.elementType = Fa, a.lanes = f, a;
      case Ia:
        return pj(c, e, f, b2);
      default:
        if ("object" === typeof a && null !== a) switch (a.$$typeof) {
          case Ba:
            g = 10;
            break a;
          case Ca:
            g = 9;
            break a;
          case Da:
            g = 11;
            break a;
          case Ga:
            g = 14;
            break a;
          case Ha:
            g = 16;
            d2 = null;
            break a;
        }
        throw Error(p(130, null == a ? a : typeof a, ""));
    }
    b2 = Bg(g, c, b2, e);
    b2.elementType = a;
    b2.type = d2;
    b2.lanes = f;
    return b2;
  }
  function Tg(a, b2, c, d2) {
    a = Bg(7, a, d2, b2);
    a.lanes = c;
    return a;
  }
  function pj(a, b2, c, d2) {
    a = Bg(22, a, d2, b2);
    a.elementType = Ia;
    a.lanes = c;
    a.stateNode = { isHidden: false };
    return a;
  }
  function Qg(a, b2, c) {
    a = Bg(6, a, null, b2);
    a.lanes = c;
    return a;
  }
  function Sg(a, b2, c) {
    b2 = Bg(4, null !== a.children ? a.children : [], a.key, b2);
    b2.lanes = c;
    b2.stateNode = { containerInfo: a.containerInfo, pendingChildren: null, implementation: a.implementation };
    return b2;
  }
  function al(a, b2, c, d2, e) {
    this.tag = b2;
    this.containerInfo = a;
    this.finishedWork = this.pingCache = this.current = this.pendingChildren = null;
    this.timeoutHandle = -1;
    this.callbackNode = this.pendingContext = this.context = null;
    this.callbackPriority = 0;
    this.eventTimes = zc(0);
    this.expirationTimes = zc(-1);
    this.entangledLanes = this.finishedLanes = this.mutableReadLanes = this.expiredLanes = this.pingedLanes = this.suspendedLanes = this.pendingLanes = 0;
    this.entanglements = zc(0);
    this.identifierPrefix = d2;
    this.onRecoverableError = e;
    this.mutableSourceEagerHydrationData = null;
  }
  function bl(a, b2, c, d2, e, f, g, h, k2) {
    a = new al(a, b2, c, h, k2);
    1 === b2 ? (b2 = 1, true === f && (b2 |= 8)) : b2 = 0;
    f = Bg(3, null, null, b2);
    a.current = f;
    f.stateNode = a;
    f.memoizedState = { element: d2, isDehydrated: c, cache: null, transitions: null, pendingSuspenseBoundaries: null };
    kh(f);
    return a;
  }
  function cl(a, b2, c) {
    var d2 = 3 < arguments.length && void 0 !== arguments[3] ? arguments[3] : null;
    return { $$typeof: wa, key: null == d2 ? null : "" + d2, children: a, containerInfo: b2, implementation: c };
  }
  function dl(a) {
    if (!a) return Vf;
    a = a._reactInternals;
    a: {
      if (Vb(a) !== a || 1 !== a.tag) throw Error(p(170));
      var b2 = a;
      do {
        switch (b2.tag) {
          case 3:
            b2 = b2.stateNode.context;
            break a;
          case 1:
            if (Zf(b2.type)) {
              b2 = b2.stateNode.__reactInternalMemoizedMergedChildContext;
              break a;
            }
        }
        b2 = b2.return;
      } while (null !== b2);
      throw Error(p(171));
    }
    if (1 === a.tag) {
      var c = a.type;
      if (Zf(c)) return bg(a, c, b2);
    }
    return b2;
  }
  function el(a, b2, c, d2, e, f, g, h, k2) {
    a = bl(c, d2, true, a, e, f, g, h, k2);
    a.context = dl(null);
    c = a.current;
    d2 = R();
    e = yi(c);
    f = mh(d2, e);
    f.callback = void 0 !== b2 && null !== b2 ? b2 : null;
    nh(c, f, e);
    a.current.lanes = e;
    Ac(a, e, d2);
    Dk(a, d2);
    return a;
  }
  function fl(a, b2, c, d2) {
    var e = b2.current, f = R(), g = yi(e);
    c = dl(c);
    null === b2.context ? b2.context = c : b2.pendingContext = c;
    b2 = mh(f, g);
    b2.payload = { element: a };
    d2 = void 0 === d2 ? null : d2;
    null !== d2 && (b2.callback = d2);
    a = nh(e, b2, g);
    null !== a && (gi(a, e, g, f), oh(a, e, g));
    return g;
  }
  function gl(a) {
    a = a.current;
    if (!a.child) return null;
    switch (a.child.tag) {
      case 5:
        return a.child.stateNode;
      default:
        return a.child.stateNode;
    }
  }
  function hl(a, b2) {
    a = a.memoizedState;
    if (null !== a && null !== a.dehydrated) {
      var c = a.retryLane;
      a.retryLane = 0 !== c && c < b2 ? c : b2;
    }
  }
  function il(a, b2) {
    hl(a, b2);
    (a = a.alternate) && hl(a, b2);
  }
  function jl() {
    return null;
  }
  var kl = "function" === typeof reportError ? reportError : function(a) {
    console.error(a);
  };
  function ll(a) {
    this._internalRoot = a;
  }
  ml.prototype.render = ll.prototype.render = function(a) {
    var b2 = this._internalRoot;
    if (null === b2) throw Error(p(409));
    fl(a, b2, null, null);
  };
  ml.prototype.unmount = ll.prototype.unmount = function() {
    var a = this._internalRoot;
    if (null !== a) {
      this._internalRoot = null;
      var b2 = a.containerInfo;
      Rk(function() {
        fl(null, a, null, null);
      });
      b2[uf] = null;
    }
  };
  function ml(a) {
    this._internalRoot = a;
  }
  ml.prototype.unstable_scheduleHydration = function(a) {
    if (a) {
      var b2 = Hc();
      a = { blockedOn: null, target: a, priority: b2 };
      for (var c = 0; c < Qc.length && 0 !== b2 && b2 < Qc[c].priority; c++) ;
      Qc.splice(c, 0, a);
      0 === c && Vc(a);
    }
  };
  function nl(a) {
    return !(!a || 1 !== a.nodeType && 9 !== a.nodeType && 11 !== a.nodeType);
  }
  function ol(a) {
    return !(!a || 1 !== a.nodeType && 9 !== a.nodeType && 11 !== a.nodeType && (8 !== a.nodeType || " react-mount-point-unstable " !== a.nodeValue));
  }
  function pl() {
  }
  function ql(a, b2, c, d2, e) {
    if (e) {
      if ("function" === typeof d2) {
        var f = d2;
        d2 = function() {
          var a2 = gl(g);
          f.call(a2);
        };
      }
      var g = el(b2, d2, a, 0, null, false, false, "", pl);
      a._reactRootContainer = g;
      a[uf] = g.current;
      sf(8 === a.nodeType ? a.parentNode : a);
      Rk();
      return g;
    }
    for (; e = a.lastChild; ) a.removeChild(e);
    if ("function" === typeof d2) {
      var h = d2;
      d2 = function() {
        var a2 = gl(k2);
        h.call(a2);
      };
    }
    var k2 = bl(a, 0, false, null, null, false, false, "", pl);
    a._reactRootContainer = k2;
    a[uf] = k2.current;
    sf(8 === a.nodeType ? a.parentNode : a);
    Rk(function() {
      fl(b2, k2, c, d2);
    });
    return k2;
  }
  function rl(a, b2, c, d2, e) {
    var f = c._reactRootContainer;
    if (f) {
      var g = f;
      if ("function" === typeof e) {
        var h = e;
        e = function() {
          var a2 = gl(g);
          h.call(a2);
        };
      }
      fl(b2, g, a, e);
    } else g = ql(c, b2, a, e, d2);
    return gl(g);
  }
  Ec = function(a) {
    switch (a.tag) {
      case 3:
        var b2 = a.stateNode;
        if (b2.current.memoizedState.isDehydrated) {
          var c = tc(b2.pendingLanes);
          0 !== c && (Cc(b2, c | 1), Dk(b2, B2()), 0 === (K2 & 6) && (Gj = B2() + 500, jg()));
        }
        break;
      case 13:
        Rk(function() {
          var b3 = ih(a, 1);
          if (null !== b3) {
            var c2 = R();
            gi(b3, a, 1, c2);
          }
        }), il(a, 1);
    }
  };
  Fc = function(a) {
    if (13 === a.tag) {
      var b2 = ih(a, 134217728);
      if (null !== b2) {
        var c = R();
        gi(b2, a, 134217728, c);
      }
      il(a, 134217728);
    }
  };
  Gc = function(a) {
    if (13 === a.tag) {
      var b2 = yi(a), c = ih(a, b2);
      if (null !== c) {
        var d2 = R();
        gi(c, a, b2, d2);
      }
      il(a, b2);
    }
  };
  Hc = function() {
    return C2;
  };
  Ic = function(a, b2) {
    var c = C2;
    try {
      return C2 = a, b2();
    } finally {
      C2 = c;
    }
  };
  yb = function(a, b2, c) {
    switch (b2) {
      case "input":
        bb(a, c);
        b2 = c.name;
        if ("radio" === c.type && null != b2) {
          for (c = a; c.parentNode; ) c = c.parentNode;
          c = c.querySelectorAll("input[name=" + JSON.stringify("" + b2) + '][type="radio"]');
          for (b2 = 0; b2 < c.length; b2++) {
            var d2 = c[b2];
            if (d2 !== a && d2.form === a.form) {
              var e = Db(d2);
              if (!e) throw Error(p(90));
              Wa(d2);
              bb(d2, e);
            }
          }
        }
        break;
      case "textarea":
        ib(a, c);
        break;
      case "select":
        b2 = c.value, null != b2 && fb(a, !!c.multiple, b2, false);
    }
  };
  Gb = Qk;
  Hb = Rk;
  var sl = { usingClientEntryPoint: false, Events: [Cb, ue2, Db, Eb, Fb, Qk] }, tl = { findFiberByHostInstance: Wc, bundleType: 0, version: "18.3.1", rendererPackageName: "react-dom" };
  var ul = { bundleType: tl.bundleType, version: tl.version, rendererPackageName: tl.rendererPackageName, rendererConfig: tl.rendererConfig, overrideHookState: null, overrideHookStateDeletePath: null, overrideHookStateRenamePath: null, overrideProps: null, overridePropsDeletePath: null, overridePropsRenamePath: null, setErrorHandler: null, setSuspenseHandler: null, scheduleUpdate: null, currentDispatcherRef: ua.ReactCurrentDispatcher, findHostInstanceByFiber: function(a) {
    a = Zb(a);
    return null === a ? null : a.stateNode;
  }, findFiberByHostInstance: tl.findFiberByHostInstance || jl, findHostInstancesForRefresh: null, scheduleRefresh: null, scheduleRoot: null, setRefreshHandler: null, getCurrentFiber: null, reconcilerVersion: "18.3.1-next-f1338f8080-20240426" };
  if ("undefined" !== typeof __REACT_DEVTOOLS_GLOBAL_HOOK__) {
    var vl = __REACT_DEVTOOLS_GLOBAL_HOOK__;
    if (!vl.isDisabled && vl.supportsFiber) try {
      kc = vl.inject(ul), lc = vl;
    } catch (a) {
    }
  }
  reactDom_production_min.__SECRET_INTERNALS_DO_NOT_USE_OR_YOU_WILL_BE_FIRED = sl;
  reactDom_production_min.createPortal = function(a, b2) {
    var c = 2 < arguments.length && void 0 !== arguments[2] ? arguments[2] : null;
    if (!nl(b2)) throw Error(p(200));
    return cl(a, b2, null, c);
  };
  reactDom_production_min.createRoot = function(a, b2) {
    if (!nl(a)) throw Error(p(299));
    var c = false, d2 = "", e = kl;
    null !== b2 && void 0 !== b2 && (true === b2.unstable_strictMode && (c = true), void 0 !== b2.identifierPrefix && (d2 = b2.identifierPrefix), void 0 !== b2.onRecoverableError && (e = b2.onRecoverableError));
    b2 = bl(a, 1, false, null, null, c, false, d2, e);
    a[uf] = b2.current;
    sf(8 === a.nodeType ? a.parentNode : a);
    return new ll(b2);
  };
  reactDom_production_min.findDOMNode = function(a) {
    if (null == a) return null;
    if (1 === a.nodeType) return a;
    var b2 = a._reactInternals;
    if (void 0 === b2) {
      if ("function" === typeof a.render) throw Error(p(188));
      a = Object.keys(a).join(",");
      throw Error(p(268, a));
    }
    a = Zb(b2);
    a = null === a ? null : a.stateNode;
    return a;
  };
  reactDom_production_min.flushSync = function(a) {
    return Rk(a);
  };
  reactDom_production_min.hydrate = function(a, b2, c) {
    if (!ol(b2)) throw Error(p(200));
    return rl(null, a, b2, true, c);
  };
  reactDom_production_min.hydrateRoot = function(a, b2, c) {
    if (!nl(a)) throw Error(p(405));
    var d2 = null != c && c.hydratedSources || null, e = false, f = "", g = kl;
    null !== c && void 0 !== c && (true === c.unstable_strictMode && (e = true), void 0 !== c.identifierPrefix && (f = c.identifierPrefix), void 0 !== c.onRecoverableError && (g = c.onRecoverableError));
    b2 = el(b2, null, a, 1, null != c ? c : null, e, false, f, g);
    a[uf] = b2.current;
    sf(a);
    if (d2) for (a = 0; a < d2.length; a++) c = d2[a], e = c._getVersion, e = e(c._source), null == b2.mutableSourceEagerHydrationData ? b2.mutableSourceEagerHydrationData = [c, e] : b2.mutableSourceEagerHydrationData.push(
      c,
      e
    );
    return new ml(b2);
  };
  reactDom_production_min.render = function(a, b2, c) {
    if (!ol(b2)) throw Error(p(200));
    return rl(null, a, b2, false, c);
  };
  reactDom_production_min.unmountComponentAtNode = function(a) {
    if (!ol(a)) throw Error(p(40));
    return a._reactRootContainer ? (Rk(function() {
      rl(null, null, a, false, function() {
        a._reactRootContainer = null;
        a[uf] = null;
      });
    }), true) : false;
  };
  reactDom_production_min.unstable_batchedUpdates = Qk;
  reactDom_production_min.unstable_renderSubtreeIntoContainer = function(a, b2, c, d2) {
    if (!ol(c)) throw Error(p(200));
    if (null == a || void 0 === a._reactInternals) throw Error(p(38));
    return rl(a, b2, c, false, d2);
  };
  reactDom_production_min.version = "18.3.1-next-f1338f8080-20240426";
  return reactDom_production_min;
}
var hasRequiredReactDom;
function requireReactDom() {
  if (hasRequiredReactDom) return reactDom.exports;
  hasRequiredReactDom = 1;
  function checkDCE() {
    if (typeof __REACT_DEVTOOLS_GLOBAL_HOOK__ === "undefined" || typeof __REACT_DEVTOOLS_GLOBAL_HOOK__.checkDCE !== "function") {
      return;
    }
    try {
      __REACT_DEVTOOLS_GLOBAL_HOOK__.checkDCE(checkDCE);
    } catch (err) {
      console.error(err);
    }
  }
  {
    checkDCE();
    reactDom.exports = requireReactDom_production_min();
  }
  return reactDom.exports;
}
var hasRequiredClient;
function requireClient() {
  if (hasRequiredClient) return client;
  hasRequiredClient = 1;
  var m2 = requireReactDom();
  {
    client.createRoot = m2.createRoot;
    client.hydrateRoot = m2.hydrateRoot;
  }
  return client;
}
var clientExports = requireClient();
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const mergeClasses = (...classes) => classes.filter((className, index, array) => {
  return Boolean(className) && className.trim() !== "" && array.indexOf(className) === index;
}).join(" ").trim();
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const toKebabCase = (string) => string.replace(/([a-z0-9])([A-Z])/g, "$1-$2").toLowerCase();
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const toCamelCase = (string) => string.replace(
  /^([A-Z])|[\s-_]+(\w)/g,
  (match, p1, p2) => p2 ? p2.toUpperCase() : p1.toLowerCase()
);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const toPascalCase = (string) => {
  const camelCase = toCamelCase(string);
  return camelCase.charAt(0).toUpperCase() + camelCase.slice(1);
};
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
var defaultAttributes = {
  xmlns: "http://www.w3.org/2000/svg",
  width: 24,
  height: 24,
  viewBox: "0 0 24 24",
  fill: "none",
  stroke: "currentColor",
  strokeWidth: 2,
  strokeLinecap: "round",
  strokeLinejoin: "round"
};
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const hasA11yProp = (props) => {
  for (const prop in props) {
    if (prop.startsWith("aria-") || prop === "role" || prop === "title") {
      return true;
    }
  }
  return false;
};
const LucideContext = reactExports.createContext({});
const useLucideContext = () => reactExports.useContext(LucideContext);
const Icon = reactExports.forwardRef(
  ({ color, size, strokeWidth, absoluteStrokeWidth, className = "", children, iconNode, ...rest }, ref) => {
    const {
      size: contextSize = 24,
      strokeWidth: contextStrokeWidth = 2,
      absoluteStrokeWidth: contextAbsoluteStrokeWidth = false,
      color: contextColor = "currentColor",
      className: contextClass = ""
    } = useLucideContext() ?? {};
    const calculatedStrokeWidth = absoluteStrokeWidth ?? contextAbsoluteStrokeWidth ? Number(strokeWidth ?? contextStrokeWidth) * 24 / Number(size ?? contextSize) : strokeWidth ?? contextStrokeWidth;
    return reactExports.createElement(
      "svg",
      {
        ref,
        ...defaultAttributes,
        width: size ?? contextSize ?? defaultAttributes.width,
        height: size ?? contextSize ?? defaultAttributes.height,
        stroke: color ?? contextColor,
        strokeWidth: calculatedStrokeWidth,
        className: mergeClasses("lucide", contextClass, className),
        ...!children && !hasA11yProp(rest) && { "aria-hidden": "true" },
        ...rest
      },
      [
        ...iconNode.map(([tag, attrs]) => reactExports.createElement(tag, attrs)),
        ...Array.isArray(children) ? children : [children]
      ]
    );
  }
);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const createLucideIcon = (iconName, iconNode) => {
  const Component = reactExports.forwardRef(
    ({ className, ...props }, ref) => reactExports.createElement(Icon, {
      ref,
      iconNode,
      className: mergeClasses(
        `lucide-${toKebabCase(toPascalCase(iconName))}`,
        `lucide-${iconName}`,
        className
      ),
      ...props
    })
  );
  Component.displayName = toPascalCase(iconName);
  return Component;
};
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$y = [
  [
    "path",
    {
      d: "M17 3a2 2 0 0 1 2 2v15a1 1 0 0 1-1.496.868l-4.512-2.578a2 2 0 0 0-1.984 0l-4.512 2.578A1 1 0 0 1 5 20V5a2 2 0 0 1 2-2z",
      key: "oz39mx"
    }
  ]
];
const Bookmark = createLucideIcon("bookmark", __iconNode$y);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$x = [
  ["path", { d: "M5 21v-6", key: "1hz6c0" }],
  ["path", { d: "M12 21V3", key: "1lcnhd" }],
  ["path", { d: "M19 21V9", key: "unv183" }]
];
const ChartNoAxesColumn = createLucideIcon("chart-no-axes-column", __iconNode$x);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$w = [["path", { d: "m6 9 6 6 6-6", key: "qrunsl" }]];
const ChevronDown = createLucideIcon("chevron-down", __iconNode$w);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$v = [
  ["circle", { cx: "12", cy: "12", r: "10", key: "1mglay" }],
  ["line", { x1: "12", x2: "12", y1: "8", y2: "12", key: "1pkeuh" }],
  ["line", { x1: "12", x2: "12.01", y1: "16", y2: "16", key: "4dfq90" }]
];
const CircleAlert = createLucideIcon("circle-alert", __iconNode$v);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$u = [
  ["circle", { cx: "12", cy: "12", r: "10", key: "1mglay" }],
  ["path", { d: "m9 12 2 2 4-4", key: "dzmm74" }]
];
const CircleCheck = createLucideIcon("circle-check", __iconNode$u);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$t = [
  ["rect", { width: "8", height: "4", x: "8", y: "2", rx: "1", ry: "1", key: "tgr4d6" }],
  ["path", { d: "M8 4H6a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2v-2", key: "4jdomd" }],
  ["path", { d: "M16 4h2a2 2 0 0 1 2 2v4", key: "3hqy98" }],
  ["path", { d: "M21 14H11", key: "1bme5i" }],
  ["path", { d: "m15 10-4 4 4 4", key: "5dvupr" }]
];
const ClipboardCopy = createLucideIcon("clipboard-copy", __iconNode$t);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$s = [
  ["path", { d: "M11 14h10", key: "1w8e9d" }],
  ["path", { d: "M16 4h2a2 2 0 0 1 2 2v1.344", key: "1e62lh" }],
  ["path", { d: "m17 18 4-4-4-4", key: "z2g111" }],
  ["path", { d: "M8 4H6a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h12a2 2 0 0 0 1.793-1.113", key: "bjbb7m" }],
  ["rect", { x: "8", y: "2", width: "8", height: "4", rx: "1", key: "ublpy" }]
];
const ClipboardPaste = createLucideIcon("clipboard-paste", __iconNode$s);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$r = [
  ["circle", { cx: "12", cy: "12", r: "10", key: "1mglay" }],
  ["path", { d: "M12 6v6l4 2", key: "mmk7yg" }]
];
const Clock = createLucideIcon("clock", __iconNode$r);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$q = [
  ["rect", { width: "14", height: "14", x: "8", y: "8", rx: "2", ry: "2", key: "17jyea" }],
  ["path", { d: "M4 16c-1.1 0-2-.9-2-2V4c0-1.1.9-2 2-2h10c1.1 0 2 .9 2 2", key: "zix9uf" }]
];
const Copy = createLucideIcon("copy", __iconNode$q);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$p = [
  ["path", { d: "M12 15V3", key: "m9g1x1" }],
  ["path", { d: "M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4", key: "ih7n3h" }],
  ["path", { d: "m7 10 5 5 5-5", key: "brsn70" }]
];
const Download = createLucideIcon("download", __iconNode$p);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$o = [
  ["path", { d: "M15 3h6v6", key: "1q9fwt" }],
  ["path", { d: "M10 14 21 3", key: "gplh6r" }],
  ["path", { d: "M18 13v6a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V8a2 2 0 0 1 2-2h6", key: "a6xqqp" }]
];
const ExternalLink = createLucideIcon("external-link", __iconNode$o);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$n = [
  [
    "path",
    {
      d: "M10.733 5.076a10.744 10.744 0 0 1 11.205 6.575 1 1 0 0 1 0 .696 10.747 10.747 0 0 1-1.444 2.49",
      key: "ct8e1f"
    }
  ],
  ["path", { d: "M14.084 14.158a3 3 0 0 1-4.242-4.242", key: "151rxh" }],
  [
    "path",
    {
      d: "M17.479 17.499a10.75 10.75 0 0 1-15.417-5.151 1 1 0 0 1 0-.696 10.75 10.75 0 0 1 4.446-5.143",
      key: "13bj9a"
    }
  ],
  ["path", { d: "m2 2 20 20", key: "1ooewy" }]
];
const EyeOff = createLucideIcon("eye-off", __iconNode$n);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$m = [
  [
    "path",
    {
      d: "M2.062 12.348a1 1 0 0 1 0-.696 10.75 10.75 0 0 1 19.876 0 1 1 0 0 1 0 .696 10.75 10.75 0 0 1-19.876 0",
      key: "1nclc0"
    }
  ],
  ["circle", { cx: "12", cy: "12", r: "3", key: "1v7zrd" }]
];
const Eye = createLucideIcon("eye", __iconNode$m);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$l = [
  [
    "path",
    {
      d: "M6 22a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h8a2.4 2.4 0 0 1 1.704.706l3.588 3.588A2.4 2.4 0 0 1 20 8v12a2 2 0 0 1-2 2z",
      key: "1oefj6"
    }
  ],
  ["path", { d: "M14 2v5a1 1 0 0 0 1 1h5", key: "wfsgrz" }],
  ["path", { d: "M10 9H8", key: "b1mrlr" }],
  ["path", { d: "M16 13H8", key: "t4e002" }],
  ["path", { d: "M16 17H8", key: "z1uh3a" }]
];
const FileText = createLucideIcon("file-text", __iconNode$l);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$k = [
  ["line", { x1: "4", x2: "20", y1: "9", y2: "9", key: "4lhtct" }],
  ["line", { x1: "4", x2: "20", y1: "15", y2: "15", key: "vyu0kd" }],
  ["line", { x1: "10", x2: "8", y1: "3", y2: "21", key: "1ggp8o" }],
  ["line", { x1: "16", x2: "14", y1: "3", y2: "21", key: "weycgp" }]
];
const Hash = createLucideIcon("hash", __iconNode$k);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$j = [
  ["circle", { cx: "12", cy: "12", r: "10", key: "1mglay" }],
  ["path", { d: "M12 16v-4", key: "1dtifu" }],
  ["path", { d: "M12 8h.01", key: "e9boi3" }]
];
const Info = createLucideIcon("info", __iconNode$j);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$i = [
  ["rect", { width: "7", height: "7", x: "3", y: "3", rx: "1", key: "1g98yp" }],
  ["rect", { width: "7", height: "7", x: "14", y: "3", rx: "1", key: "6d4xhi" }],
  ["rect", { width: "7", height: "7", x: "14", y: "14", rx: "1", key: "nxv5o0" }],
  ["rect", { width: "7", height: "7", x: "3", y: "14", rx: "1", key: "1bb6yr" }]
];
const LayoutGrid = createLucideIcon("layout-grid", __iconNode$i);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$h = [
  ["path", { d: "m16 6 4 14", key: "ji33uf" }],
  ["path", { d: "M12 6v14", key: "1n7gus" }],
  ["path", { d: "M8 8v12", key: "1gg7y9" }],
  ["path", { d: "M4 4v16", key: "6qkkli" }]
];
const Library = createLucideIcon("library", __iconNode$h);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$g = [
  ["path", { d: "M9 17H7A5 5 0 0 1 7 7h2", key: "8i5ue5" }],
  ["path", { d: "M15 7h2a5 5 0 1 1 0 10h-2", key: "1b9ql8" }],
  ["line", { x1: "8", x2: "16", y1: "12", y2: "12", key: "1jonct" }]
];
const Link2 = createLucideIcon("link-2", __iconNode$g);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$f = [
  ["path", { d: "m16 17 5-5-5-5", key: "1bji2h" }],
  ["path", { d: "M21 12H9", key: "dn1m92" }],
  ["path", { d: "M9 21H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h4", key: "1uf3rs" }]
];
const LogOut = createLucideIcon("log-out", __iconNode$f);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$e = [
  [
    "path",
    {
      d: "M20.985 12.486a9 9 0 1 1-9.473-9.472c.405-.022.617.46.402.803a6 6 0 0 0 8.268 8.268c.344-.215.825-.004.803.401",
      key: "kfwtm"
    }
  ]
];
const Moon = createLucideIcon("moon", __iconNode$e);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$d = [
  ["rect", { width: "18", height: "18", x: "3", y: "3", rx: "2", key: "afitv7" }],
  ["path", { d: "M15 3v18", key: "14nvp0" }]
];
const PanelRight = createLucideIcon("panel-right", __iconNode$d);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$c = [
  ["path", { d: "M13 21h8", key: "1jsn5i" }],
  [
    "path",
    {
      d: "M21.174 6.812a1 1 0 0 0-3.986-3.987L3.842 16.174a2 2 0 0 0-.5.83l-1.321 4.352a.5.5 0 0 0 .623.622l4.353-1.32a2 2 0 0 0 .83-.497z",
      key: "1a8usu"
    }
  ]
];
const PenLine = createLucideIcon("pen-line", __iconNode$c);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$b = [
  ["path", { d: "M3 12a9 9 0 0 1 9-9 9.75 9.75 0 0 1 6.74 2.74L21 8", key: "v9h5vc" }],
  ["path", { d: "M21 3v5h-5", key: "1q7to0" }],
  ["path", { d: "M21 12a9 9 0 0 1-9 9 9.75 9.75 0 0 1-6.74-2.74L3 16", key: "3uifl3" }],
  ["path", { d: "M8 16H3v5", key: "1cv678" }]
];
const RefreshCw = createLucideIcon("refresh-cw", __iconNode$b);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$a = [
  ["path", { d: "M3 12a9 9 0 1 0 9-9 9.75 9.75 0 0 0-6.74 2.74L3 8", key: "1357e3" }],
  ["path", { d: "M3 3v5h5", key: "1xhq8a" }]
];
const RotateCcw = createLucideIcon("rotate-ccw", __iconNode$a);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$9 = [
  ["path", { d: "m21 21-4.34-4.34", key: "14j7rj" }],
  ["circle", { cx: "11", cy: "11", r: "8", key: "4ej97u" }]
];
const Search = createLucideIcon("search", __iconNode$9);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$8 = [
  [
    "path",
    {
      d: "M9.671 4.136a2.34 2.34 0 0 1 4.659 0 2.34 2.34 0 0 0 3.319 1.915 2.34 2.34 0 0 1 2.33 4.033 2.34 2.34 0 0 0 0 3.831 2.34 2.34 0 0 1-2.33 4.033 2.34 2.34 0 0 0-3.319 1.915 2.34 2.34 0 0 1-4.659 0 2.34 2.34 0 0 0-3.32-1.915 2.34 2.34 0 0 1-2.33-4.033 2.34 2.34 0 0 0 0-3.831A2.34 2.34 0 0 1 6.35 6.051a2.34 2.34 0 0 0 3.319-1.915",
      key: "1i5ecw"
    }
  ],
  ["circle", { cx: "12", cy: "12", r: "3", key: "1v7zrd" }]
];
const Settings = createLucideIcon("settings", __iconNode$8);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$7 = [
  ["circle", { cx: "18", cy: "5", r: "3", key: "gq8acd" }],
  ["circle", { cx: "6", cy: "12", r: "3", key: "w7nqdw" }],
  ["circle", { cx: "18", cy: "19", r: "3", key: "1xt0gg" }],
  ["line", { x1: "8.59", x2: "15.42", y1: "13.51", y2: "17.49", key: "47mynk" }],
  ["line", { x1: "15.41", x2: "8.59", y1: "6.51", y2: "10.49", key: "1n3mei" }]
];
const Share2 = createLucideIcon("share-2", __iconNode$7);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$6 = [
  ["circle", { cx: "12", cy: "12", r: "4", key: "4exip2" }],
  ["path", { d: "M12 2v2", key: "tus03m" }],
  ["path", { d: "M12 20v2", key: "1lh1kg" }],
  ["path", { d: "m4.93 4.93 1.41 1.41", key: "149t6j" }],
  ["path", { d: "m17.66 17.66 1.41 1.41", key: "ptbguv" }],
  ["path", { d: "M2 12h2", key: "1t8f8n" }],
  ["path", { d: "M20 12h2", key: "1q8mjw" }],
  ["path", { d: "m6.34 17.66-1.41 1.41", key: "1m8zz5" }],
  ["path", { d: "m19.07 4.93-1.41 1.41", key: "1shlcs" }]
];
const Sun = createLucideIcon("sun", __iconNode$6);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$5 = [
  ["path", { d: "M10 11v6", key: "nco0om" }],
  ["path", { d: "M14 11v6", key: "outv1u" }],
  ["path", { d: "M19 6v14a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2V6", key: "miytrc" }],
  ["path", { d: "M3 6h18", key: "d0wm0j" }],
  ["path", { d: "M8 6V4a2 2 0 0 1 2-2h4a2 2 0 0 1 2 2v2", key: "e791ji" }]
];
const Trash2 = createLucideIcon("trash-2", __iconNode$5);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$4 = [
  ["path", { d: "M16 7h6v6", key: "box55l" }],
  ["path", { d: "m22 7-8.5 8.5-5-5L2 17", key: "1t1m79" }]
];
const TrendingUp = createLucideIcon("trending-up", __iconNode$4);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$3 = [
  [
    "path",
    {
      d: "m21.73 18-8-14a2 2 0 0 0-3.48 0l-8 14A2 2 0 0 0 4 21h16a2 2 0 0 0 1.73-3",
      key: "wmoenq"
    }
  ],
  ["path", { d: "M12 9v4", key: "juzpu7" }],
  ["path", { d: "M12 17h.01", key: "p32p05" }]
];
const TriangleAlert = createLucideIcon("triangle-alert", __iconNode$3);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$2 = [
  ["path", { d: "M12 4v16", key: "1654pz" }],
  ["path", { d: "M4 7V5a1 1 0 0 1 1-1h14a1 1 0 0 1 1 1v2", key: "e0r10z" }],
  ["path", { d: "M9 20h6", key: "s66wpe" }]
];
const Type = createLucideIcon("type", __iconNode$2);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode$1 = [
  ["path", { d: "M18 6 6 18", key: "1bl5f8" }],
  ["path", { d: "m6 6 12 12", key: "d8bk6v" }]
];
const X$1 = createLucideIcon("x", __iconNode$1);
/**
 * @license lucide-react v1.16.0 - ISC
 *
 * This source code is licensed under the ISC license.
 * See the LICENSE file in the root directory of this source tree.
 */
const __iconNode = [
  [
    "path",
    {
      d: "M4 14a1 1 0 0 1-.78-1.63l9.9-10.2a.5.5 0 0 1 .86.46l-1.92 6.02A1 1 0 0 0 13 10h7a1 1 0 0 1 .78 1.63l-9.9 10.2a.5.5 0 0 1-.86-.46l1.92-6.02A1 1 0 0 0 11 14z",
      key: "1xq2db"
    }
  ]
];
const Zap = createLucideIcon("zap", __iconNode);
class StorageService {
  static STORAGE_KEYS = {
    API_KEY: "get_tldr_api_key",
    USER_STATS: "get_tldr_user_stats",
    LAST_USAGE_CHECK: "get_tldr_last_usage_check",
    SAVED_SUMMARIES: "get_tldr_saved_summaries",
    THEME: "get_tldr_theme_pref",
    LAST_PROMPT: "get_tldr_last_prompt",
    UI_PREFS: "get_tldr_ui_prefs"
  };
  /**
   * Save API key to chrome.storage.local
   */
  static async saveApiKey(apiKey) {
    try {
      await chrome.storage.local.set({ [this.STORAGE_KEYS.API_KEY]: apiKey });
    } catch (error) {
      console.error("Failed to save API key:", error);
      throw new Error("Failed to save API key to storage");
    }
  }
  /**
   * Retrieve API key from chrome.storage.local
   */
  static async getApiKey() {
    try {
      const result = await chrome.storage.local.get([this.STORAGE_KEYS.API_KEY]);
      return result[this.STORAGE_KEYS.API_KEY] || null;
    } catch (error) {
      console.error("Failed to retrieve API key:", error);
      return null;
    }
  }
  /**
   * Clear API key from storage
   */
  static async clearApiKey() {
    try {
      await chrome.storage.local.remove([this.STORAGE_KEYS.API_KEY]);
    } catch (error) {
      console.error("Failed to clear API key:", error);
      throw new Error("Failed to clear API key from storage");
    }
  }
  /**
   * Save user statistics
   */
  static async saveUserStats(stats) {
    try {
      const statsToSave = {
        ...stats,
        lastUpdated: (/* @__PURE__ */ new Date()).toISOString()
      };
      await chrome.storage.local.set({ [this.STORAGE_KEYS.USER_STATS]: statsToSave });
    } catch (error) {
      console.error("Failed to save user stats:", error);
      throw new Error("Failed to save user statistics");
    }
  }
  /**
   * Retrieve user statistics
   */
  static async getUserStats() {
    try {
      const result = await chrome.storage.local.get([this.STORAGE_KEYS.USER_STATS]);
      return result[this.STORAGE_KEYS.USER_STATS] || null;
    } catch (error) {
      console.error("Failed to retrieve user stats:", error);
      return null;
    }
  }
  /**
   * Update user statistics incrementally
   */
  static async updateUserStats(updates) {
    try {
      const currentStats = await this.getUserStats();
      const newStats = {
        totalSummaries: currentStats?.totalSummaries || 0,
        wordsProcessed: currentStats?.wordsProcessed || 0,
        tokensUsed: currentStats?.tokensUsed || 0,
        lastUpdated: (/* @__PURE__ */ new Date()).toISOString(),
        ...updates
      };
      if (updates.totalSummaries !== void 0) {
        newStats.totalSummaries = (currentStats?.totalSummaries || 0) + updates.totalSummaries;
      }
      if (updates.wordsProcessed !== void 0) {
        newStats.wordsProcessed = (currentStats?.wordsProcessed || 0) + updates.wordsProcessed;
      }
      if (updates.tokensUsed !== void 0) {
        newStats.tokensUsed = (currentStats?.tokensUsed || 0) + updates.tokensUsed;
      }
      await this.saveUserStats(newStats);
    } catch (error) {
      console.error("Failed to update user stats:", error);
      throw new Error("Failed to update user statistics");
    }
  }
  /**
   * Save last usage check timestamp
   */
  static async saveLastUsageCheck() {
    try {
      await chrome.storage.local.set({ [this.STORAGE_KEYS.LAST_USAGE_CHECK]: (/* @__PURE__ */ new Date()).toISOString() });
    } catch (error) {
      console.error("Failed to save last usage check:", error);
    }
  }
  /**
   * Get last usage check timestamp
   */
  static async getLastUsageCheck() {
    try {
      const result = await chrome.storage.local.get([this.STORAGE_KEYS.LAST_USAGE_CHECK]);
      return result[this.STORAGE_KEYS.LAST_USAGE_CHECK] || null;
    } catch (error) {
      console.error("Failed to retrieve last usage check:", error);
      return null;
    }
  }
  /**
   * Clear all stored data
   */
  static async clearAllData() {
    try {
      await chrome.storage.local.remove(Object.values(this.STORAGE_KEYS));
    } catch (error) {
      console.error("Failed to clear all data:", error);
      throw new Error("Failed to clear all stored data");
    }
  }
  /**
   * Save a summary to storage
   */
  static async saveSummary(summary) {
    try {
      const savedSummary = {
        ...summary,
        id: `summary_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`,
        createdAt: (/* @__PURE__ */ new Date()).toISOString()
      };
      const existingSummaries = await this.getSavedSummaries();
      const updatedSummaries = [savedSummary, ...existingSummaries];
      const limitedSummaries = updatedSummaries.slice(0, 1e3);
      await chrome.storage.local.set({ [this.STORAGE_KEYS.SAVED_SUMMARIES]: limitedSummaries });
      return savedSummary;
    } catch (error) {
      console.error("Failed to save summary:", error);
      throw new Error("Failed to save summary to storage");
    }
  }
  /**
   * Get all saved summaries
   */
  static async getSavedSummaries() {
    try {
      const result = await chrome.storage.local.get([this.STORAGE_KEYS.SAVED_SUMMARIES]);
      return result[this.STORAGE_KEYS.SAVED_SUMMARIES] || [];
    } catch (error) {
      console.error("Failed to retrieve saved summaries:", error);
      return [];
    }
  }
  /**
   * Delete a saved summary by ID
   */
  static async deleteSummary(summaryId) {
    try {
      const existingSummaries = await this.getSavedSummaries();
      const updatedSummaries = existingSummaries.filter((s) => s.id !== summaryId);
      await chrome.storage.local.set({ [this.STORAGE_KEYS.SAVED_SUMMARIES]: updatedSummaries });
    } catch (error) {
      console.error("Failed to delete summary:", error);
      throw new Error("Failed to delete summary from storage");
    }
  }
  /**
   * Clear all saved summaries
   */
  static async clearSavedSummaries() {
    try {
      await chrome.storage.local.remove([this.STORAGE_KEYS.SAVED_SUMMARIES]);
    } catch (error) {
      console.error("Failed to clear saved summaries:", error);
      throw new Error("Failed to clear saved summaries from storage");
    }
  }
  /**
   * Get all stored data
   */
  static async getAllData() {
    try {
      const result = await chrome.storage.local.get(Object.values(this.STORAGE_KEYS));
      return {
        apiKey: result[this.STORAGE_KEYS.API_KEY] || void 0,
        userStats: result[this.STORAGE_KEYS.USER_STATS] || void 0,
        lastUsageCheck: result[this.STORAGE_KEYS.LAST_USAGE_CHECK] || void 0,
        savedSummaries: result[this.STORAGE_KEYS.SAVED_SUMMARIES] || void 0,
        themePreference: result[this.STORAGE_KEYS.THEME] || void 0
      };
    } catch (error) {
      console.error("Failed to retrieve all data:", error);
      return {};
    }
  }
  /**
   * Check if storage quota is available
   */
  static async checkStorageQuota() {
    try {
      const bytesInUse = await chrome.storage.local.getBytesInUse();
      return {
        used: bytesInUse,
        total: chrome.storage.local.QUOTA_BYTES || 10485760
        // 10MB default for chrome.storage.local
      };
    } catch (error) {
      console.error("Failed to check storage quota:", error);
      return { used: 0, total: 0 };
    }
  }
  /**
   * Save theme preference
   */
  static async saveThemePreference(theme) {
    try {
      await chrome.storage.local.set({ [this.STORAGE_KEYS.THEME]: theme });
    } catch (error) {
      console.error("Failed to save theme preference:", error);
    }
  }
  /**
   * Retrieve theme preference (falls back to system preference, then dark)
   */
  static async getThemePreference() {
    try {
      const result = await chrome.storage.local.get([this.STORAGE_KEYS.THEME]);
      const stored = result[this.STORAGE_KEYS.THEME];
      if (stored === "light" || stored === "dark") return stored;
      if (typeof window !== "undefined" && window.matchMedia) {
        return window.matchMedia("(prefers-color-scheme: light)").matches ? "light" : "dark";
      }
      return "dark";
    } catch (error) {
      console.error("Failed to retrieve theme preference:", error);
      return "dark";
    }
  }
  /**
   * Save last selected prompt id
   */
  static async saveLastSelectedPrompt(promptId) {
    try {
      await chrome.storage.local.set({ [this.STORAGE_KEYS.LAST_PROMPT]: promptId });
    } catch (error) {
      console.error("Failed to save last selected prompt:", error);
    }
  }
  /**
   * Retrieve last selected prompt id
   */
  static async getLastSelectedPrompt() {
    try {
      const result = await chrome.storage.local.get([this.STORAGE_KEYS.LAST_PROMPT]);
      return result[this.STORAGE_KEYS.LAST_PROMPT] || null;
    } catch (error) {
      console.error("Failed to retrieve last selected prompt:", error);
      return null;
    }
  }
  /**
   * Cache prompts with TTL (1 hour)
   */
  static async cachePrompts(prompts, ttlMinutes = 60) {
    try {
      const cacheData = {
        prompts,
        cachedAt: Date.now(),
        ttl: ttlMinutes * 60 * 1e3
        // Convert to milliseconds
      };
      await chrome.storage.local.set({ "get_tldr_prompts_cache": cacheData });
    } catch (error) {
      console.error("Failed to cache prompts:", error);
    }
  }
  /**
   * Get cached prompts if still valid
   */
  static async getCachedPrompts() {
    try {
      const result = await chrome.storage.local.get(["get_tldr_prompts_cache"]);
      const cache = result["get_tldr_prompts_cache"];
      if (!cache || !cache.prompts || !cache.cachedAt) {
        return null;
      }
      const now = Date.now();
      const age = now - cache.cachedAt;
      if (age > cache.ttl) {
        return null;
      }
      return cache.prompts;
    } catch (error) {
      console.error("Failed to retrieve cached prompts:", error);
      return null;
    }
  }
  static async saveUiPreferences(prefs) {
    try {
      const current = await this.getUiPreferences();
      await chrome.storage.local.set({
        [this.STORAGE_KEYS.UI_PREFS]: { ...current, ...prefs }
      });
    } catch (error) {
      console.error("Failed to save UI preferences:", error);
    }
  }
  static async getUiPreferences() {
    try {
      const result = await chrome.storage.local.get([this.STORAGE_KEYS.UI_PREFS]);
      return result[this.STORAGE_KEYS.UI_PREFS] || {};
    } catch (error) {
      console.error("Failed to retrieve UI preferences:", error);
      return {};
    }
  }
  /**
   * Clear prompts cache
   */
  static async clearPromptsCache() {
    try {
      await chrome.storage.local.remove(["get_tldr_prompts_cache"]);
    } catch (error) {
      console.error("Failed to clear prompts cache:", error);
    }
  }
}
class ApiService {
  static BASE_URL = "https://www.get-tldr.com/api/v1";
  static ENDPOINTS = {
    SUMMARIZE: "/summarize",
    USAGE: "/users/usage",
    PROMPTS: "/prompts",
    PROFILE: "/users/profile"
  };
  /**
   * Validate API key by attempting to access profile endpoint
   */
  static async validateApiKey(apiKey) {
    try {
      const response = await fetch(`${this.BASE_URL}${this.ENDPOINTS.PROFILE}`, {
        method: "GET",
        headers: {
          "Content-Type": "application/json",
          "X-API-Key": apiKey
        }
      });
      return response.ok;
    } catch (error) {
      console.error("API key validation failed:", error);
      return false;
    }
  }
  /**
   * Get available prompts (with caching)
   */
  static async getPrompts(apiKey, useCache = true) {
    if (useCache) {
      const cached = await StorageService.getCachedPrompts();
      if (cached && Array.isArray(cached)) {
        return cached;
      }
    }
    try {
      const response = await fetch(`${this.BASE_URL}${this.ENDPOINTS.PROMPTS}`, {
        method: "GET",
        headers: {
          "X-API-Key": apiKey,
          "Content-Type": "application/json"
        }
      });
      if (response.ok) {
        const data = await response.json();
        if (data.prompts && Array.isArray(data.prompts)) {
          const apiPrompts = data.prompts.map((prompt) => ({
            id: prompt.id,
            name: prompt.title || prompt.name,
            description: prompt.description || "",
            prompt: prompt.content || prompt.prompt
          }));
          const allPrompts = [...this.getDefaultPrompts(), ...apiPrompts];
          await StorageService.cachePrompts(allPrompts, 60);
          return allPrompts;
        }
        const defaultPrompts2 = this.getDefaultPrompts();
        await StorageService.cachePrompts(defaultPrompts2, 60);
        return defaultPrompts2;
      }
      const defaultPrompts = this.getDefaultPrompts();
      await StorageService.cachePrompts(defaultPrompts, 60);
      return defaultPrompts;
    } catch (error) {
      console.error("Failed to fetch prompts:", error);
      const defaultPrompts = this.getDefaultPrompts();
      await StorageService.cachePrompts(defaultPrompts, 60);
      return defaultPrompts;
    }
  }
  /**
   * Get default prompts as fallback
   */
  static getDefaultPrompts() {
    return [
      {
        id: "default",
        name: "Default Summary",
        description: "General purpose summary",
        prompt: "Provide a concise summary of the main points in this content."
      },
      {
        id: "bullet-points",
        name: "Bullet Points",
        description: "Key points in bullet format",
        prompt: "Summarize this content as bullet points highlighting the key information."
      },
      {
        id: "executive",
        name: "Executive Summary",
        description: "Business-focused summary",
        prompt: "Create an executive summary focusing on business implications and key decisions."
      },
      {
        id: "technical",
        name: "Technical Summary",
        description: "Technical details and implementation",
        prompt: "Summarize the technical aspects, implementation details, and key technical points."
      },
      {
        id: "action-items",
        name: "Action Items",
        description: "Actionable tasks and next steps",
        prompt: "Extract actionable items, tasks, and next steps from this content."
      }
    ];
  }
  /**
   * Summarize content
   */
  static async summarizeContent(apiKey, request) {
    try {
      const inputUrl = ApiService.canonicalizeUrl(request.url);
      const response = await fetch(`${this.BASE_URL}${this.ENDPOINTS.SUMMARIZE}`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
          "X-API-Key": apiKey
        },
        body: JSON.stringify({
          // Per API docs: input should be the URL (we send only the open page URL)
          input: inputUrl,
          system_prompt: request.prompt,
          ...request.skipCache !== void 0 ? { skip_cache: request.skipCache } : {}
        })
      });
      if (!response.ok) {
        const errorData = await response.json().catch(() => ({}));
        throw new Error(errorData.message || `API request failed with status ${response.status}`);
      }
      const data = await response.json();
      const tokensUsed = typeof data.total_tokens === "number" && data.total_tokens || (typeof data.input_tokens === "number" && typeof data.output_tokens === "number" ? data.input_tokens + data.output_tokens : 0);
      const processingTime = data.processing_info && typeof data.processing_info.processing_time === "number" ? data.processing_info.processing_time : 0;
      const wordCount = typeof data.summary === "string" ? data.summary.trim().split(/\s+/).length : 0;
      return {
        summary: data.summary,
        tokensUsed,
        processingTime,
        wordCount
      };
    } catch (error) {
      console.error("Summarization failed:", error);
      throw new Error(error instanceof Error ? error.message : "Failed to summarize content");
    }
  }
  /**
   * Canonicalize URLs for better API handling (e.g., normalize YouTube URLs to watch form)
   */
  static canonicalizeUrl(rawUrl) {
    try {
      const url = new URL(rawUrl);
      const host = url.hostname.toLowerCase();
      if (host === "m.youtube.com") {
        url.hostname = "www.youtube.com";
      }
      if (host === "youtu.be") {
        const videoId = url.pathname.replace(/^\//, "") || "";
        if (videoId) {
          const watch = new URL("https://www.youtube.com/watch");
          watch.searchParams.set("v", videoId);
          const t = url.searchParams.get("t") || url.searchParams.get("start");
          if (t) watch.searchParams.set("t", t);
          return watch.toString();
        }
      }
      if (host.endsWith("youtube.com") && url.pathname.startsWith("/shorts/")) {
        const videoId = url.pathname.split("/")[2] || "";
        if (videoId) {
          const watch = new URL("https://www.youtube.com/watch");
          watch.searchParams.set("v", videoId);
          return watch.toString();
        }
      }
      if (host.endsWith("youtube.com") && url.pathname.startsWith("/embed/")) {
        const videoId = url.pathname.split("/")[2] || "";
        if (videoId) {
          const watch = new URL("https://www.youtube.com/watch");
          watch.searchParams.set("v", videoId);
          return watch.toString();
        }
      }
      return url.toString();
    } catch {
      return rawUrl;
    }
  }
  /**
   * Get usage statistics
   */
  static async getUsageData(apiKey) {
    try {
      const response = await fetch(`${this.BASE_URL}${this.ENDPOINTS.USAGE}`, {
        method: "GET",
        headers: {
          "X-API-Key": apiKey,
          "Content-Type": "application/json"
        }
      });
      if (!response.ok) {
        throw new Error(`Usage request failed with status ${response.status}`);
      }
      const data = await response.json();
      const now = /* @__PURE__ */ new Date();
      const resetDate = new Date(now.getFullYear(), now.getMonth() + 1, 1);
      return {
        currentUsage: data.monthly_used || 0,
        monthlyLimit: data.monthly_limit || 0,
        planType: "API",
        // Default since not provided in API response
        resetDate: resetDate.toISOString()
      };
    } catch (error) {
      console.error("Failed to fetch usage data:", error);
      throw new Error("Failed to retrieve usage information");
    }
  }
  /**
   * Check if current page is accessible for content extraction
   */
  static async isPageAccessible() {
    try {
      const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
      if (!tab.url) return false;
      const restrictedProtocols = ["chrome://", "chrome-extension://", "moz-extension://", "edge://"];
      return !restrictedProtocols.some((protocol) => tab.url.startsWith(protocol));
    } catch (error) {
      console.error("Failed to check page accessibility:", error);
      return false;
    }
  }
}
function L() {
  return { async: false, breaks: false, extensions: null, gfm: true, hooks: null, pedantic: false, renderer: null, silent: false, tokenizer: null, walkTokens: null };
}
var T = L();
function G(u3) {
  T = u3;
}
var I = { exec: () => null };
function d(u3, e = "") {
  let t = typeof u3 == "string" ? u3 : u3.source, n = { replace: (r, i) => {
    let s = typeof i == "string" ? i : i.source;
    return s = s.replace(m.caret, "$1"), t = t.replace(r, s), n;
  }, getRegex: () => new RegExp(t, e) };
  return n;
}
var m = { codeRemoveIndent: /^(?: {1,4}| {0,3}\t)/gm, outputLinkReplace: /\\([\[\]])/g, indentCodeCompensation: /^(\s+)(?:```)/, beginningSpace: /^\s+/, endingHash: /#$/, startingSpaceChar: /^ /, endingSpaceChar: / $/, nonSpaceChar: /[^ ]/, newLineCharGlobal: /\n/g, tabCharGlobal: /\t/g, multipleSpaceGlobal: /\s+/g, blankLine: /^[ \t]*$/, doubleBlankLine: /\n[ \t]*\n[ \t]*$/, blockquoteStart: /^ {0,3}>/, blockquoteSetextReplace: /\n {0,3}((?:=+|-+) *)(?=\n|$)/g, blockquoteSetextReplace2: /^ {0,3}>[ \t]?/gm, listReplaceTabs: /^\t+/, listReplaceNesting: /^ {1,4}(?=( {4})*[^ ])/g, listIsTask: /^\[[ xX]\] /, listReplaceTask: /^\[[ xX]\] +/, anyLine: /\n.*\n/, hrefBrackets: /^<(.*)>$/, tableDelimiter: /[:|]/, tableAlignChars: /^\||\| *$/g, tableRowBlankLine: /\n[ \t]*$/, tableAlignRight: /^ *-+: *$/, tableAlignCenter: /^ *:-+: *$/, tableAlignLeft: /^ *:-+ *$/, startATag: /^<a /i, endATag: /^<\/a>/i, startPreScriptTag: /^<(pre|code|kbd|script)(\s|>)/i, endPreScriptTag: /^<\/(pre|code|kbd|script)(\s|>)/i, startAngleBracket: /^</, endAngleBracket: />$/, pedanticHrefTitle: /^([^'"]*[^\s])\s+(['"])(.*)\2/, unicodeAlphaNumeric: /[\p{L}\p{N}]/u, escapeTest: /[&<>"']/, escapeReplace: /[&<>"']/g, escapeTestNoEncode: /[<>"']|&(?!(#\d{1,7}|#[Xx][a-fA-F0-9]{1,6}|\w+);)/, escapeReplaceNoEncode: /[<>"']|&(?!(#\d{1,7}|#[Xx][a-fA-F0-9]{1,6}|\w+);)/g, unescapeTest: /&(#(?:\d+)|(?:#x[0-9A-Fa-f]+)|(?:\w+));?/ig, caret: /(^|[^\[])\^/g, percentDecode: /%25/g, findPipe: /\|/g, splitPipe: / \|/, slashPipe: /\\\|/g, carriageReturn: /\r\n|\r/g, spaceLine: /^ +$/gm, notSpaceStart: /^\S*/, endingNewline: /\n$/, listItemRegex: (u3) => new RegExp(`^( {0,3}${u3})((?:[	 ][^\\n]*)?(?:\\n|$))`), nextBulletRegex: (u3) => new RegExp(`^ {0,${Math.min(3, u3 - 1)}}(?:[*+-]|\\d{1,9}[.)])((?:[ 	][^\\n]*)?(?:\\n|$))`), hrRegex: (u3) => new RegExp(`^ {0,${Math.min(3, u3 - 1)}}((?:- *){3,}|(?:_ *){3,}|(?:\\* *){3,})(?:\\n+|$)`), fencesBeginRegex: (u3) => new RegExp(`^ {0,${Math.min(3, u3 - 1)}}(?:\`\`\`|~~~)`), headingBeginRegex: (u3) => new RegExp(`^ {0,${Math.min(3, u3 - 1)}}#`), htmlBeginRegex: (u3) => new RegExp(`^ {0,${Math.min(3, u3 - 1)}}<(?:[a-z].*>|!--)`, "i") }, be = /^(?:[ \t]*(?:\n|$))+/, Re = /^((?: {4}| {0,3}\t)[^\n]+(?:\n(?:[ \t]*(?:\n|$))*)?)+/, Te = /^ {0,3}(`{3,}(?=[^`\n]*(?:\n|$))|~{3,})([^\n]*)(?:\n|$)(?:|([\s\S]*?)(?:\n|$))(?: {0,3}\1[~`]* *(?=\n|$)|$)/, E = /^ {0,3}((?:-[\t ]*){3,}|(?:_[ \t]*){3,}|(?:\*[ \t]*){3,})(?:\n+|$)/, Oe = /^ {0,3}(#{1,6})(?=\s|$)(.*)(?:\n+|$)/, F = /(?:[*+-]|\d{1,9}[.)])/, ie = /^(?!bull |blockCode|fences|blockquote|heading|html|table)((?:.|\n(?!\s*?\n|bull |blockCode|fences|blockquote|heading|html|table))+?)\n {0,3}(=+|-+) *(?:\n+|$)/, oe = d(ie).replace(/bull/g, F).replace(/blockCode/g, /(?: {4}| {0,3}\t)/).replace(/fences/g, / {0,3}(?:`{3,}|~{3,})/).replace(/blockquote/g, / {0,3}>/).replace(/heading/g, / {0,3}#{1,6}/).replace(/html/g, / {0,3}<[^\n>]+>\n/).replace(/\|table/g, "").getRegex(), we = d(ie).replace(/bull/g, F).replace(/blockCode/g, /(?: {4}| {0,3}\t)/).replace(/fences/g, / {0,3}(?:`{3,}|~{3,})/).replace(/blockquote/g, / {0,3}>/).replace(/heading/g, / {0,3}#{1,6}/).replace(/html/g, / {0,3}<[^\n>]+>\n/).replace(/table/g, / {0,3}\|?(?:[:\- ]*\|)+[\:\- ]*\n/).getRegex(), j = /^([^\n]+(?:\n(?!hr|heading|lheading|blockquote|fences|list|html|table| +\n)[^\n]+)*)/, ye = /^[^\n]+/, Q = /(?!\s*\])(?:\\[\s\S]|[^\[\]\\])+/, Pe = d(/^ {0,3}\[(label)\]: *(?:\n[ \t]*)?([^<\s][^\s]*|<.*?>)(?:(?: +(?:\n[ \t]*)?| *\n[ \t]*)(title))? *(?:\n+|$)/).replace("label", Q).replace("title", /(?:"(?:\\"?|[^"\\])*"|'[^'\n]*(?:\n[^'\n]+)*\n?'|\([^()]*\))/).getRegex(), Se = d(/^( {0,3}bull)([ \t][^\n]+?)?(?:\n|$)/).replace(/bull/g, F).getRegex(), v = "address|article|aside|base|basefont|blockquote|body|caption|center|col|colgroup|dd|details|dialog|dir|div|dl|dt|fieldset|figcaption|figure|footer|form|frame|frameset|h[1-6]|head|header|hr|html|iframe|legend|li|link|main|menu|menuitem|meta|nav|noframes|ol|optgroup|option|p|param|search|section|summary|table|tbody|td|tfoot|th|thead|title|tr|track|ul", U = /<!--(?:-?>|[\s\S]*?(?:-->|$))/, $e = d("^ {0,3}(?:<(script|pre|style|textarea)[\\s>][\\s\\S]*?(?:</\\1>[^\\n]*\\n+|$)|comment[^\\n]*(\\n+|$)|<\\?[\\s\\S]*?(?:\\?>\\n*|$)|<![A-Z][\\s\\S]*?(?:>\\n*|$)|<!\\[CDATA\\[[\\s\\S]*?(?:\\]\\]>\\n*|$)|</?(tag)(?: +|\\n|/?>)[\\s\\S]*?(?:(?:\\n[ 	]*)+\\n|$)|<(?!script|pre|style|textarea)([a-z][\\w-]*)(?:attribute)*? */?>(?=[ \\t]*(?:\\n|$))[\\s\\S]*?(?:(?:\\n[ 	]*)+\\n|$)|</(?!script|pre|style|textarea)[a-z][\\w-]*\\s*>(?=[ \\t]*(?:\\n|$))[\\s\\S]*?(?:(?:\\n[ 	]*)+\\n|$))", "i").replace("comment", U).replace("tag", v).replace("attribute", / +[a-zA-Z:_][\w.:-]*(?: *= *"[^"\n]*"| *= *'[^'\n]*'| *= *[^\s"'=<>`]+)?/).getRegex(), ae = d(j).replace("hr", E).replace("heading", " {0,3}#{1,6}(?:\\s|$)").replace("|lheading", "").replace("|table", "").replace("blockquote", " {0,3}>").replace("fences", " {0,3}(?:`{3,}(?=[^`\\n]*\\n)|~{3,})[^\\n]*\\n").replace("list", " {0,3}(?:[*+-]|1[.)]) ").replace("html", "</?(?:tag)(?: +|\\n|/?>)|<(?:script|pre|style|textarea|!--)").replace("tag", v).getRegex(), _e = d(/^( {0,3}> ?(paragraph|[^\n]*)(?:\n|$))+/).replace("paragraph", ae).getRegex(), K = { blockquote: _e, code: Re, def: Pe, fences: Te, heading: Oe, hr: E, html: $e, lheading: oe, list: Se, newline: be, paragraph: ae, table: I, text: ye }, re = d("^ *([^\\n ].*)\\n {0,3}((?:\\| *)?:?-+:? *(?:\\| *:?-+:? *)*(?:\\| *)?)(?:\\n((?:(?! *\\n|hr|heading|blockquote|code|fences|list|html).*(?:\\n|$))*)\\n*|$)").replace("hr", E).replace("heading", " {0,3}#{1,6}(?:\\s|$)").replace("blockquote", " {0,3}>").replace("code", "(?: {4}| {0,3}	)[^\\n]").replace("fences", " {0,3}(?:`{3,}(?=[^`\\n]*\\n)|~{3,})[^\\n]*\\n").replace("list", " {0,3}(?:[*+-]|1[.)]) ").replace("html", "</?(?:tag)(?: +|\\n|/?>)|<(?:script|pre|style|textarea|!--)").replace("tag", v).getRegex(), Le = { ...K, lheading: we, table: re, paragraph: d(j).replace("hr", E).replace("heading", " {0,3}#{1,6}(?:\\s|$)").replace("|lheading", "").replace("table", re).replace("blockquote", " {0,3}>").replace("fences", " {0,3}(?:`{3,}(?=[^`\\n]*\\n)|~{3,})[^\\n]*\\n").replace("list", " {0,3}(?:[*+-]|1[.)]) ").replace("html", "</?(?:tag)(?: +|\\n|/?>)|<(?:script|pre|style|textarea|!--)").replace("tag", v).getRegex() }, Me = { ...K, html: d(`^ *(?:comment *(?:\\n|\\s*$)|<(tag)[\\s\\S]+?</\\1> *(?:\\n{2,}|\\s*$)|<tag(?:"[^"]*"|'[^']*'|\\s[^'"/>\\s]*)*?/?> *(?:\\n{2,}|\\s*$))`).replace("comment", U).replace(/tag/g, "(?!(?:a|em|strong|small|s|cite|q|dfn|abbr|data|time|code|var|samp|kbd|sub|sup|i|b|u|mark|ruby|rt|rp|bdi|bdo|span|br|wbr|ins|del|img)\\b)\\w+(?!:|[^\\w\\s@]*@)\\b").getRegex(), def: /^ *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +(["(][^\n]+[")]))? *(?:\n+|$)/, heading: /^(#{1,6})(.*)(?:\n+|$)/, fences: I, lheading: /^(.+?)\n {0,3}(=+|-+) *(?:\n+|$)/, paragraph: d(j).replace("hr", E).replace("heading", ` *#{1,6} *[^
]`).replace("lheading", oe).replace("|table", "").replace("blockquote", " {0,3}>").replace("|fences", "").replace("|list", "").replace("|html", "").replace("|tag", "").getRegex() }, ze = /^\\([!"#$%&'()*+,\-./:;<=>?@\[\]\\^_`{|}~])/, Ae = /^(`+)([^`]|[^`][\s\S]*?[^`])\1(?!`)/, le = /^( {2,}|\\)\n(?!\s*$)/, Ie = /^(`+|[^`])(?:(?= {2,}\n)|[\s\S]*?(?:(?=[\\<!\[`*_]|\b_|$)|[^ ](?= {2,}\n)))/, D = /[\p{P}\p{S}]/u, W = /[\s\p{P}\p{S}]/u, ue = /[^\s\p{P}\p{S}]/u, Ee = d(/^((?![*_])punctSpace)/, "u").replace(/punctSpace/g, W).getRegex(), pe = /(?!~)[\p{P}\p{S}]/u, Ce = /(?!~)[\s\p{P}\p{S}]/u, Be = /(?:[^\s\p{P}\p{S}]|~)/u, qe = /\[(?:[^\[\]`]|`[^`]*?`)*?\]\((?:\\[\s\S]|[^\\\(\)]|\((?:\\[\s\S]|[^\\\(\)])*\))*\)|`[^`]*?`|<(?! )[^<>]*?>/g, ce = /^(?:\*+(?:((?!\*)punct)|[^\s*]))|^_+(?:((?!_)punct)|([^\s_]))/, ve = d(ce, "u").replace(/punct/g, D).getRegex(), De = d(ce, "u").replace(/punct/g, pe).getRegex(), he = "^[^_*]*?__[^_*]*?\\*[^_*]*?(?=__)|[^*]+(?=[^*])|(?!\\*)punct(\\*+)(?=[\\s]|$)|notPunctSpace(\\*+)(?!\\*)(?=punctSpace|$)|(?!\\*)punctSpace(\\*+)(?=notPunctSpace)|[\\s](\\*+)(?!\\*)(?=punct)|(?!\\*)punct(\\*+)(?!\\*)(?=punct)|notPunctSpace(\\*+)(?=notPunctSpace)", He = d(he, "gu").replace(/notPunctSpace/g, ue).replace(/punctSpace/g, W).replace(/punct/g, D).getRegex(), Ze = d(he, "gu").replace(/notPunctSpace/g, Be).replace(/punctSpace/g, Ce).replace(/punct/g, pe).getRegex(), Ge = d("^[^_*]*?\\*\\*[^_*]*?_[^_*]*?(?=\\*\\*)|[^_]+(?=[^_])|(?!_)punct(_+)(?=[\\s]|$)|notPunctSpace(_+)(?!_)(?=punctSpace|$)|(?!_)punctSpace(_+)(?=notPunctSpace)|[\\s](_+)(?!_)(?=punct)|(?!_)punct(_+)(?!_)(?=punct)", "gu").replace(/notPunctSpace/g, ue).replace(/punctSpace/g, W).replace(/punct/g, D).getRegex(), Ne = d(/\\(punct)/, "gu").replace(/punct/g, D).getRegex(), Fe = d(/^<(scheme:[^\s\x00-\x1f<>]*|email)>/).replace("scheme", /[a-zA-Z][a-zA-Z0-9+.-]{1,31}/).replace("email", /[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+(@)[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)+(?![-_])/).getRegex(), je = d(U).replace("(?:-->|$)", "-->").getRegex(), Qe = d("^comment|^</[a-zA-Z][\\w:-]*\\s*>|^<[a-zA-Z][\\w-]*(?:attribute)*?\\s*/?>|^<\\?[\\s\\S]*?\\?>|^<![a-zA-Z]+\\s[\\s\\S]*?>|^<!\\[CDATA\\[[\\s\\S]*?\\]\\]>").replace("comment", je).replace("attribute", /\s+[a-zA-Z:_][\w.:-]*(?:\s*=\s*"[^"]*"|\s*=\s*'[^']*'|\s*=\s*[^\s"'=<>`]+)?/).getRegex(), q = /(?:\[(?:\\[\s\S]|[^\[\]\\])*\]|\\[\s\S]|`+[^`]*?`+(?!`)|[^\[\]\\`])*?/, Ue = d(/^!?\[(label)\]\(\s*(href)(?:(?:[ \t]*(?:\n[ \t]*)?)(title))?\s*\)/).replace("label", q).replace("href", /<(?:\\.|[^\n<>\\])+>|[^ \t\n\x00-\x1f]*/).replace("title", /"(?:\\"?|[^"\\])*"|'(?:\\'?|[^'\\])*'|\((?:\\\)?|[^)\\])*\)/).getRegex(), de = d(/^!?\[(label)\]\[(ref)\]/).replace("label", q).replace("ref", Q).getRegex(), ke = d(/^!?\[(ref)\](?:\[\])?/).replace("ref", Q).getRegex(), Ke = d("reflink|nolink(?!\\()", "g").replace("reflink", de).replace("nolink", ke).getRegex(), se = /[hH][tT][tT][pP][sS]?|[fF][tT][pP]/, X = { _backpedal: I, anyPunctuation: Ne, autolink: Fe, blockSkip: qe, br: le, code: Ae, del: I, emStrongLDelim: ve, emStrongRDelimAst: He, emStrongRDelimUnd: Ge, escape: ze, link: Ue, nolink: ke, punctuation: Ee, reflink: de, reflinkSearch: Ke, tag: Qe, text: Ie, url: I }, We = { ...X, link: d(/^!?\[(label)\]\((.*?)\)/).replace("label", q).getRegex(), reflink: d(/^!?\[(label)\]\s*\[([^\]]*)\]/).replace("label", q).getRegex() }, N = { ...X, emStrongRDelimAst: Ze, emStrongLDelim: De, url: d(/^((?:protocol):\/\/|www\.)(?:[a-zA-Z0-9\-]+\.?)+[^\s<]*|^email/).replace("protocol", se).replace("email", /[A-Za-z0-9._+-]+(@)[a-zA-Z0-9-_]+(?:\.[a-zA-Z0-9-_]*[a-zA-Z0-9])+(?![-_])/).getRegex(), _backpedal: /(?:[^?!.,:;*_'"~()&]+|\([^)]*\)|&(?![a-zA-Z0-9]+;$)|[?!.,:;*_'"~)]+(?!$))+/, del: /^(~~?)(?=[^\s~])((?:\\[\s\S]|[^\\])*?(?:\\[\s\S]|[^\s~\\]))\1(?=[^~]|$)/, text: d(/^([`~]+|[^`~])(?:(?= {2,}\n)|(?=[a-zA-Z0-9.!#$%&'*+\/=?_`{\|}~-]+@)|[\s\S]*?(?:(?=[\\<!\[`*~_]|\b_|protocol:\/\/|www\.|$)|[^ ](?= {2,}\n)|[^a-zA-Z0-9.!#$%&'*+\/=?_`{\|}~-](?=[a-zA-Z0-9.!#$%&'*+\/=?_`{\|}~-]+@)))/).replace("protocol", se).getRegex() }, Xe = { ...N, br: d(le).replace("{2,}", "*").getRegex(), text: d(N.text).replace("\\b_", "\\b_| {2,}\\n").replace(/\{2,\}/g, "*").getRegex() }, C = { normal: K, gfm: Le, pedantic: Me }, M = { normal: X, gfm: N, breaks: Xe, pedantic: We };
var Je = { "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" }, ge = (u3) => Je[u3];
function w(u3, e) {
  if (e) {
    if (m.escapeTest.test(u3)) return u3.replace(m.escapeReplace, ge);
  } else if (m.escapeTestNoEncode.test(u3)) return u3.replace(m.escapeReplaceNoEncode, ge);
  return u3;
}
function J(u3) {
  try {
    u3 = encodeURI(u3).replace(m.percentDecode, "%");
  } catch {
    return null;
  }
  return u3;
}
function V(u3, e) {
  let t = u3.replace(m.findPipe, (i, s, o) => {
    let a = false, l = s;
    for (; --l >= 0 && o[l] === "\\"; ) a = !a;
    return a ? "|" : " |";
  }), n = t.split(m.splitPipe), r = 0;
  if (n[0].trim() || n.shift(), n.length > 0 && !n.at(-1)?.trim() && n.pop(), e) if (n.length > e) n.splice(e);
  else for (; n.length < e; ) n.push("");
  for (; r < n.length; r++) n[r] = n[r].trim().replace(m.slashPipe, "|");
  return n;
}
function z(u3, e, t) {
  let n = u3.length;
  if (n === 0) return "";
  let r = 0;
  for (; r < n; ) {
    let i = u3.charAt(n - r - 1);
    if (i === e && true) r++;
    else break;
  }
  return u3.slice(0, n - r);
}
function fe(u3, e) {
  if (u3.indexOf(e[1]) === -1) return -1;
  let t = 0;
  for (let n = 0; n < u3.length; n++) if (u3[n] === "\\") n++;
  else if (u3[n] === e[0]) t++;
  else if (u3[n] === e[1] && (t--, t < 0)) return n;
  return t > 0 ? -2 : -1;
}
function me(u3, e, t, n, r) {
  let i = e.href, s = e.title || null, o = u3[1].replace(r.other.outputLinkReplace, "$1");
  n.state.inLink = true;
  let a = { type: u3[0].charAt(0) === "!" ? "image" : "link", raw: t, href: i, title: s, text: o, tokens: n.inlineTokens(o) };
  return n.state.inLink = false, a;
}
function Ve(u3, e, t) {
  let n = u3.match(t.other.indentCodeCompensation);
  if (n === null) return e;
  let r = n[1];
  return e.split(`
`).map((i) => {
    let s = i.match(t.other.beginningSpace);
    if (s === null) return i;
    let [o] = s;
    return o.length >= r.length ? i.slice(r.length) : i;
  }).join(`
`);
}
var y = class {
  options;
  rules;
  lexer;
  constructor(e) {
    this.options = e || T;
  }
  space(e) {
    let t = this.rules.block.newline.exec(e);
    if (t && t[0].length > 0) return { type: "space", raw: t[0] };
  }
  code(e) {
    let t = this.rules.block.code.exec(e);
    if (t) {
      let n = t[0].replace(this.rules.other.codeRemoveIndent, "");
      return { type: "code", raw: t[0], codeBlockStyle: "indented", text: this.options.pedantic ? n : z(n, `
`) };
    }
  }
  fences(e) {
    let t = this.rules.block.fences.exec(e);
    if (t) {
      let n = t[0], r = Ve(n, t[3] || "", this.rules);
      return { type: "code", raw: n, lang: t[2] ? t[2].trim().replace(this.rules.inline.anyPunctuation, "$1") : t[2], text: r };
    }
  }
  heading(e) {
    let t = this.rules.block.heading.exec(e);
    if (t) {
      let n = t[2].trim();
      if (this.rules.other.endingHash.test(n)) {
        let r = z(n, "#");
        (this.options.pedantic || !r || this.rules.other.endingSpaceChar.test(r)) && (n = r.trim());
      }
      return { type: "heading", raw: t[0], depth: t[1].length, text: n, tokens: this.lexer.inline(n) };
    }
  }
  hr(e) {
    let t = this.rules.block.hr.exec(e);
    if (t) return { type: "hr", raw: z(t[0], `
`) };
  }
  blockquote(e) {
    let t = this.rules.block.blockquote.exec(e);
    if (t) {
      let n = z(t[0], `
`).split(`
`), r = "", i = "", s = [];
      for (; n.length > 0; ) {
        let o = false, a = [], l;
        for (l = 0; l < n.length; l++) if (this.rules.other.blockquoteStart.test(n[l])) a.push(n[l]), o = true;
        else if (!o) a.push(n[l]);
        else break;
        n = n.slice(l);
        let c = a.join(`
`), p = c.replace(this.rules.other.blockquoteSetextReplace, `
    $1`).replace(this.rules.other.blockquoteSetextReplace2, "");
        r = r ? `${r}
${c}` : c, i = i ? `${i}
${p}` : p;
        let g = this.lexer.state.top;
        if (this.lexer.state.top = true, this.lexer.blockTokens(p, s, true), this.lexer.state.top = g, n.length === 0) break;
        let h = s.at(-1);
        if (h?.type === "code") break;
        if (h?.type === "blockquote") {
          let R = h, f = R.raw + `
` + n.join(`
`), O = this.blockquote(f);
          s[s.length - 1] = O, r = r.substring(0, r.length - R.raw.length) + O.raw, i = i.substring(0, i.length - R.text.length) + O.text;
          break;
        } else if (h?.type === "list") {
          let R = h, f = R.raw + `
` + n.join(`
`), O = this.list(f);
          s[s.length - 1] = O, r = r.substring(0, r.length - h.raw.length) + O.raw, i = i.substring(0, i.length - R.raw.length) + O.raw, n = f.substring(s.at(-1).raw.length).split(`
`);
          continue;
        }
      }
      return { type: "blockquote", raw: r, tokens: s, text: i };
    }
  }
  list(e) {
    let t = this.rules.block.list.exec(e);
    if (t) {
      let n = t[1].trim(), r = n.length > 1, i = { type: "list", raw: "", ordered: r, start: r ? +n.slice(0, -1) : "", loose: false, items: [] };
      n = r ? `\\d{1,9}\\${n.slice(-1)}` : `\\${n}`, this.options.pedantic && (n = r ? n : "[*+-]");
      let s = this.rules.other.listItemRegex(n), o = false;
      for (; e; ) {
        let l = false, c = "", p = "";
        if (!(t = s.exec(e)) || this.rules.block.hr.test(e)) break;
        c = t[0], e = e.substring(c.length);
        let g = t[2].split(`
`, 1)[0].replace(this.rules.other.listReplaceTabs, (H) => " ".repeat(3 * H.length)), h = e.split(`
`, 1)[0], R = !g.trim(), f = 0;
        if (this.options.pedantic ? (f = 2, p = g.trimStart()) : R ? f = t[1].length + 1 : (f = t[2].search(this.rules.other.nonSpaceChar), f = f > 4 ? 1 : f, p = g.slice(f), f += t[1].length), R && this.rules.other.blankLine.test(h) && (c += h + `
`, e = e.substring(h.length + 1), l = true), !l) {
          let H = this.rules.other.nextBulletRegex(f), ee = this.rules.other.hrRegex(f), te = this.rules.other.fencesBeginRegex(f), ne = this.rules.other.headingBeginRegex(f), xe = this.rules.other.htmlBeginRegex(f);
          for (; e; ) {
            let Z = e.split(`
`, 1)[0], A;
            if (h = Z, this.options.pedantic ? (h = h.replace(this.rules.other.listReplaceNesting, "  "), A = h) : A = h.replace(this.rules.other.tabCharGlobal, "    "), te.test(h) || ne.test(h) || xe.test(h) || H.test(h) || ee.test(h)) break;
            if (A.search(this.rules.other.nonSpaceChar) >= f || !h.trim()) p += `
` + A.slice(f);
            else {
              if (R || g.replace(this.rules.other.tabCharGlobal, "    ").search(this.rules.other.nonSpaceChar) >= 4 || te.test(g) || ne.test(g) || ee.test(g)) break;
              p += `
` + h;
            }
            !R && !h.trim() && (R = true), c += Z + `
`, e = e.substring(Z.length + 1), g = A.slice(f);
          }
        }
        i.loose || (o ? i.loose = true : this.rules.other.doubleBlankLine.test(c) && (o = true));
        let O = null, Y;
        this.options.gfm && (O = this.rules.other.listIsTask.exec(p), O && (Y = O[0] !== "[ ] ", p = p.replace(this.rules.other.listReplaceTask, ""))), i.items.push({ type: "list_item", raw: c, task: !!O, checked: Y, loose: false, text: p, tokens: [] }), i.raw += c;
      }
      let a = i.items.at(-1);
      if (a) a.raw = a.raw.trimEnd(), a.text = a.text.trimEnd();
      else return;
      i.raw = i.raw.trimEnd();
      for (let l = 0; l < i.items.length; l++) if (this.lexer.state.top = false, i.items[l].tokens = this.lexer.blockTokens(i.items[l].text, []), !i.loose) {
        let c = i.items[l].tokens.filter((g) => g.type === "space"), p = c.length > 0 && c.some((g) => this.rules.other.anyLine.test(g.raw));
        i.loose = p;
      }
      if (i.loose) for (let l = 0; l < i.items.length; l++) i.items[l].loose = true;
      return i;
    }
  }
  html(e) {
    let t = this.rules.block.html.exec(e);
    if (t) return { type: "html", block: true, raw: t[0], pre: t[1] === "pre" || t[1] === "script" || t[1] === "style", text: t[0] };
  }
  def(e) {
    let t = this.rules.block.def.exec(e);
    if (t) {
      let n = t[1].toLowerCase().replace(this.rules.other.multipleSpaceGlobal, " "), r = t[2] ? t[2].replace(this.rules.other.hrefBrackets, "$1").replace(this.rules.inline.anyPunctuation, "$1") : "", i = t[3] ? t[3].substring(1, t[3].length - 1).replace(this.rules.inline.anyPunctuation, "$1") : t[3];
      return { type: "def", tag: n, raw: t[0], href: r, title: i };
    }
  }
  table(e) {
    let t = this.rules.block.table.exec(e);
    if (!t || !this.rules.other.tableDelimiter.test(t[2])) return;
    let n = V(t[1]), r = t[2].replace(this.rules.other.tableAlignChars, "").split("|"), i = t[3]?.trim() ? t[3].replace(this.rules.other.tableRowBlankLine, "").split(`
`) : [], s = { type: "table", raw: t[0], header: [], align: [], rows: [] };
    if (n.length === r.length) {
      for (let o of r) this.rules.other.tableAlignRight.test(o) ? s.align.push("right") : this.rules.other.tableAlignCenter.test(o) ? s.align.push("center") : this.rules.other.tableAlignLeft.test(o) ? s.align.push("left") : s.align.push(null);
      for (let o = 0; o < n.length; o++) s.header.push({ text: n[o], tokens: this.lexer.inline(n[o]), header: true, align: s.align[o] });
      for (let o of i) s.rows.push(V(o, s.header.length).map((a, l) => ({ text: a, tokens: this.lexer.inline(a), header: false, align: s.align[l] })));
      return s;
    }
  }
  lheading(e) {
    let t = this.rules.block.lheading.exec(e);
    if (t) return { type: "heading", raw: t[0], depth: t[2].charAt(0) === "=" ? 1 : 2, text: t[1], tokens: this.lexer.inline(t[1]) };
  }
  paragraph(e) {
    let t = this.rules.block.paragraph.exec(e);
    if (t) {
      let n = t[1].charAt(t[1].length - 1) === `
` ? t[1].slice(0, -1) : t[1];
      return { type: "paragraph", raw: t[0], text: n, tokens: this.lexer.inline(n) };
    }
  }
  text(e) {
    let t = this.rules.block.text.exec(e);
    if (t) return { type: "text", raw: t[0], text: t[0], tokens: this.lexer.inline(t[0]) };
  }
  escape(e) {
    let t = this.rules.inline.escape.exec(e);
    if (t) return { type: "escape", raw: t[0], text: t[1] };
  }
  tag(e) {
    let t = this.rules.inline.tag.exec(e);
    if (t) return !this.lexer.state.inLink && this.rules.other.startATag.test(t[0]) ? this.lexer.state.inLink = true : this.lexer.state.inLink && this.rules.other.endATag.test(t[0]) && (this.lexer.state.inLink = false), !this.lexer.state.inRawBlock && this.rules.other.startPreScriptTag.test(t[0]) ? this.lexer.state.inRawBlock = true : this.lexer.state.inRawBlock && this.rules.other.endPreScriptTag.test(t[0]) && (this.lexer.state.inRawBlock = false), { type: "html", raw: t[0], inLink: this.lexer.state.inLink, inRawBlock: this.lexer.state.inRawBlock, block: false, text: t[0] };
  }
  link(e) {
    let t = this.rules.inline.link.exec(e);
    if (t) {
      let n = t[2].trim();
      if (!this.options.pedantic && this.rules.other.startAngleBracket.test(n)) {
        if (!this.rules.other.endAngleBracket.test(n)) return;
        let s = z(n.slice(0, -1), "\\");
        if ((n.length - s.length) % 2 === 0) return;
      } else {
        let s = fe(t[2], "()");
        if (s === -2) return;
        if (s > -1) {
          let a = (t[0].indexOf("!") === 0 ? 5 : 4) + t[1].length + s;
          t[2] = t[2].substring(0, s), t[0] = t[0].substring(0, a).trim(), t[3] = "";
        }
      }
      let r = t[2], i = "";
      if (this.options.pedantic) {
        let s = this.rules.other.pedanticHrefTitle.exec(r);
        s && (r = s[1], i = s[3]);
      } else i = t[3] ? t[3].slice(1, -1) : "";
      return r = r.trim(), this.rules.other.startAngleBracket.test(r) && (this.options.pedantic && !this.rules.other.endAngleBracket.test(n) ? r = r.slice(1) : r = r.slice(1, -1)), me(t, { href: r && r.replace(this.rules.inline.anyPunctuation, "$1"), title: i && i.replace(this.rules.inline.anyPunctuation, "$1") }, t[0], this.lexer, this.rules);
    }
  }
  reflink(e, t) {
    let n;
    if ((n = this.rules.inline.reflink.exec(e)) || (n = this.rules.inline.nolink.exec(e))) {
      let r = (n[2] || n[1]).replace(this.rules.other.multipleSpaceGlobal, " "), i = t[r.toLowerCase()];
      if (!i) {
        let s = n[0].charAt(0);
        return { type: "text", raw: s, text: s };
      }
      return me(n, i, n[0], this.lexer, this.rules);
    }
  }
  emStrong(e, t, n = "") {
    let r = this.rules.inline.emStrongLDelim.exec(e);
    if (!r || r[3] && n.match(this.rules.other.unicodeAlphaNumeric)) return;
    if (!(r[1] || r[2] || "") || !n || this.rules.inline.punctuation.exec(n)) {
      let s = [...r[0]].length - 1, o, a, l = s, c = 0, p = r[0][0] === "*" ? this.rules.inline.emStrongRDelimAst : this.rules.inline.emStrongRDelimUnd;
      for (p.lastIndex = 0, t = t.slice(-1 * e.length + s); (r = p.exec(t)) != null; ) {
        if (o = r[1] || r[2] || r[3] || r[4] || r[5] || r[6], !o) continue;
        if (a = [...o].length, r[3] || r[4]) {
          l += a;
          continue;
        } else if ((r[5] || r[6]) && s % 3 && !((s + a) % 3)) {
          c += a;
          continue;
        }
        if (l -= a, l > 0) continue;
        a = Math.min(a, a + l + c);
        let g = [...r[0]][0].length, h = e.slice(0, s + r.index + g + a);
        if (Math.min(s, a) % 2) {
          let f = h.slice(1, -1);
          return { type: "em", raw: h, text: f, tokens: this.lexer.inlineTokens(f) };
        }
        let R = h.slice(2, -2);
        return { type: "strong", raw: h, text: R, tokens: this.lexer.inlineTokens(R) };
      }
    }
  }
  codespan(e) {
    let t = this.rules.inline.code.exec(e);
    if (t) {
      let n = t[2].replace(this.rules.other.newLineCharGlobal, " "), r = this.rules.other.nonSpaceChar.test(n), i = this.rules.other.startingSpaceChar.test(n) && this.rules.other.endingSpaceChar.test(n);
      return r && i && (n = n.substring(1, n.length - 1)), { type: "codespan", raw: t[0], text: n };
    }
  }
  br(e) {
    let t = this.rules.inline.br.exec(e);
    if (t) return { type: "br", raw: t[0] };
  }
  del(e) {
    let t = this.rules.inline.del.exec(e);
    if (t) return { type: "del", raw: t[0], text: t[2], tokens: this.lexer.inlineTokens(t[2]) };
  }
  autolink(e) {
    let t = this.rules.inline.autolink.exec(e);
    if (t) {
      let n, r;
      return t[2] === "@" ? (n = t[1], r = "mailto:" + n) : (n = t[1], r = n), { type: "link", raw: t[0], text: n, href: r, tokens: [{ type: "text", raw: n, text: n }] };
    }
  }
  url(e) {
    let t;
    if (t = this.rules.inline.url.exec(e)) {
      let n, r;
      if (t[2] === "@") n = t[0], r = "mailto:" + n;
      else {
        let i;
        do
          i = t[0], t[0] = this.rules.inline._backpedal.exec(t[0])?.[0] ?? "";
        while (i !== t[0]);
        n = t[0], t[1] === "www." ? r = "http://" + t[0] : r = t[0];
      }
      return { type: "link", raw: t[0], text: n, href: r, tokens: [{ type: "text", raw: n, text: n }] };
    }
  }
  inlineText(e) {
    let t = this.rules.inline.text.exec(e);
    if (t) {
      let n = this.lexer.state.inRawBlock;
      return { type: "text", raw: t[0], text: t[0], escaped: n };
    }
  }
};
var x = class u {
  tokens;
  options;
  state;
  tokenizer;
  inlineQueue;
  constructor(e) {
    this.tokens = [], this.tokens.links = /* @__PURE__ */ Object.create(null), this.options = e || T, this.options.tokenizer = this.options.tokenizer || new y(), this.tokenizer = this.options.tokenizer, this.tokenizer.options = this.options, this.tokenizer.lexer = this, this.inlineQueue = [], this.state = { inLink: false, inRawBlock: false, top: true };
    let t = { other: m, block: C.normal, inline: M.normal };
    this.options.pedantic ? (t.block = C.pedantic, t.inline = M.pedantic) : this.options.gfm && (t.block = C.gfm, this.options.breaks ? t.inline = M.breaks : t.inline = M.gfm), this.tokenizer.rules = t;
  }
  static get rules() {
    return { block: C, inline: M };
  }
  static lex(e, t) {
    return new u(t).lex(e);
  }
  static lexInline(e, t) {
    return new u(t).inlineTokens(e);
  }
  lex(e) {
    e = e.replace(m.carriageReturn, `
`), this.blockTokens(e, this.tokens);
    for (let t = 0; t < this.inlineQueue.length; t++) {
      let n = this.inlineQueue[t];
      this.inlineTokens(n.src, n.tokens);
    }
    return this.inlineQueue = [], this.tokens;
  }
  blockTokens(e, t = [], n = false) {
    for (this.options.pedantic && (e = e.replace(m.tabCharGlobal, "    ").replace(m.spaceLine, "")); e; ) {
      let r;
      if (this.options.extensions?.block?.some((s) => (r = s.call({ lexer: this }, e, t)) ? (e = e.substring(r.raw.length), t.push(r), true) : false)) continue;
      if (r = this.tokenizer.space(e)) {
        e = e.substring(r.raw.length);
        let s = t.at(-1);
        r.raw.length === 1 && s !== void 0 ? s.raw += `
` : t.push(r);
        continue;
      }
      if (r = this.tokenizer.code(e)) {
        e = e.substring(r.raw.length);
        let s = t.at(-1);
        s?.type === "paragraph" || s?.type === "text" ? (s.raw += (s.raw.endsWith(`
`) ? "" : `
`) + r.raw, s.text += `
` + r.text, this.inlineQueue.at(-1).src = s.text) : t.push(r);
        continue;
      }
      if (r = this.tokenizer.fences(e)) {
        e = e.substring(r.raw.length), t.push(r);
        continue;
      }
      if (r = this.tokenizer.heading(e)) {
        e = e.substring(r.raw.length), t.push(r);
        continue;
      }
      if (r = this.tokenizer.hr(e)) {
        e = e.substring(r.raw.length), t.push(r);
        continue;
      }
      if (r = this.tokenizer.blockquote(e)) {
        e = e.substring(r.raw.length), t.push(r);
        continue;
      }
      if (r = this.tokenizer.list(e)) {
        e = e.substring(r.raw.length), t.push(r);
        continue;
      }
      if (r = this.tokenizer.html(e)) {
        e = e.substring(r.raw.length), t.push(r);
        continue;
      }
      if (r = this.tokenizer.def(e)) {
        e = e.substring(r.raw.length);
        let s = t.at(-1);
        s?.type === "paragraph" || s?.type === "text" ? (s.raw += (s.raw.endsWith(`
`) ? "" : `
`) + r.raw, s.text += `
` + r.raw, this.inlineQueue.at(-1).src = s.text) : this.tokens.links[r.tag] || (this.tokens.links[r.tag] = { href: r.href, title: r.title }, t.push(r));
        continue;
      }
      if (r = this.tokenizer.table(e)) {
        e = e.substring(r.raw.length), t.push(r);
        continue;
      }
      if (r = this.tokenizer.lheading(e)) {
        e = e.substring(r.raw.length), t.push(r);
        continue;
      }
      let i = e;
      if (this.options.extensions?.startBlock) {
        let s = 1 / 0, o = e.slice(1), a;
        this.options.extensions.startBlock.forEach((l) => {
          a = l.call({ lexer: this }, o), typeof a == "number" && a >= 0 && (s = Math.min(s, a));
        }), s < 1 / 0 && s >= 0 && (i = e.substring(0, s + 1));
      }
      if (this.state.top && (r = this.tokenizer.paragraph(i))) {
        let s = t.at(-1);
        n && s?.type === "paragraph" ? (s.raw += (s.raw.endsWith(`
`) ? "" : `
`) + r.raw, s.text += `
` + r.text, this.inlineQueue.pop(), this.inlineQueue.at(-1).src = s.text) : t.push(r), n = i.length !== e.length, e = e.substring(r.raw.length);
        continue;
      }
      if (r = this.tokenizer.text(e)) {
        e = e.substring(r.raw.length);
        let s = t.at(-1);
        s?.type === "text" ? (s.raw += (s.raw.endsWith(`
`) ? "" : `
`) + r.raw, s.text += `
` + r.text, this.inlineQueue.pop(), this.inlineQueue.at(-1).src = s.text) : t.push(r);
        continue;
      }
      if (e) {
        let s = "Infinite loop on byte: " + e.charCodeAt(0);
        if (this.options.silent) {
          console.error(s);
          break;
        } else throw new Error(s);
      }
    }
    return this.state.top = true, t;
  }
  inline(e, t = []) {
    return this.inlineQueue.push({ src: e, tokens: t }), t;
  }
  inlineTokens(e, t = []) {
    let n = e, r = null;
    if (this.tokens.links) {
      let o = Object.keys(this.tokens.links);
      if (o.length > 0) for (; (r = this.tokenizer.rules.inline.reflinkSearch.exec(n)) != null; ) o.includes(r[0].slice(r[0].lastIndexOf("[") + 1, -1)) && (n = n.slice(0, r.index) + "[" + "a".repeat(r[0].length - 2) + "]" + n.slice(this.tokenizer.rules.inline.reflinkSearch.lastIndex));
    }
    for (; (r = this.tokenizer.rules.inline.anyPunctuation.exec(n)) != null; ) n = n.slice(0, r.index) + "++" + n.slice(this.tokenizer.rules.inline.anyPunctuation.lastIndex);
    for (; (r = this.tokenizer.rules.inline.blockSkip.exec(n)) != null; ) n = n.slice(0, r.index) + "[" + "a".repeat(r[0].length - 2) + "]" + n.slice(this.tokenizer.rules.inline.blockSkip.lastIndex);
    n = this.options.hooks?.emStrongMask?.call({ lexer: this }, n) ?? n;
    let i = false, s = "";
    for (; e; ) {
      i || (s = ""), i = false;
      let o;
      if (this.options.extensions?.inline?.some((l) => (o = l.call({ lexer: this }, e, t)) ? (e = e.substring(o.raw.length), t.push(o), true) : false)) continue;
      if (o = this.tokenizer.escape(e)) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      if (o = this.tokenizer.tag(e)) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      if (o = this.tokenizer.link(e)) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      if (o = this.tokenizer.reflink(e, this.tokens.links)) {
        e = e.substring(o.raw.length);
        let l = t.at(-1);
        o.type === "text" && l?.type === "text" ? (l.raw += o.raw, l.text += o.text) : t.push(o);
        continue;
      }
      if (o = this.tokenizer.emStrong(e, n, s)) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      if (o = this.tokenizer.codespan(e)) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      if (o = this.tokenizer.br(e)) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      if (o = this.tokenizer.del(e)) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      if (o = this.tokenizer.autolink(e)) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      if (!this.state.inLink && (o = this.tokenizer.url(e))) {
        e = e.substring(o.raw.length), t.push(o);
        continue;
      }
      let a = e;
      if (this.options.extensions?.startInline) {
        let l = 1 / 0, c = e.slice(1), p;
        this.options.extensions.startInline.forEach((g) => {
          p = g.call({ lexer: this }, c), typeof p == "number" && p >= 0 && (l = Math.min(l, p));
        }), l < 1 / 0 && l >= 0 && (a = e.substring(0, l + 1));
      }
      if (o = this.tokenizer.inlineText(a)) {
        e = e.substring(o.raw.length), o.raw.slice(-1) !== "_" && (s = o.raw.slice(-1)), i = true;
        let l = t.at(-1);
        l?.type === "text" ? (l.raw += o.raw, l.text += o.text) : t.push(o);
        continue;
      }
      if (e) {
        let l = "Infinite loop on byte: " + e.charCodeAt(0);
        if (this.options.silent) {
          console.error(l);
          break;
        } else throw new Error(l);
      }
    }
    return t;
  }
};
var P = class {
  options;
  parser;
  constructor(e) {
    this.options = e || T;
  }
  space(e) {
    return "";
  }
  code({ text: e, lang: t, escaped: n }) {
    let r = (t || "").match(m.notSpaceStart)?.[0], i = e.replace(m.endingNewline, "") + `
`;
    return r ? '<pre><code class="language-' + w(r) + '">' + (n ? i : w(i, true)) + `</code></pre>
` : "<pre><code>" + (n ? i : w(i, true)) + `</code></pre>
`;
  }
  blockquote({ tokens: e }) {
    return `<blockquote>
${this.parser.parse(e)}</blockquote>
`;
  }
  html({ text: e }) {
    return e;
  }
  def(e) {
    return "";
  }
  heading({ tokens: e, depth: t }) {
    return `<h${t}>${this.parser.parseInline(e)}</h${t}>
`;
  }
  hr(e) {
    return `<hr>
`;
  }
  list(e) {
    let t = e.ordered, n = e.start, r = "";
    for (let o = 0; o < e.items.length; o++) {
      let a = e.items[o];
      r += this.listitem(a);
    }
    let i = t ? "ol" : "ul", s = t && n !== 1 ? ' start="' + n + '"' : "";
    return "<" + i + s + `>
` + r + "</" + i + `>
`;
  }
  listitem(e) {
    let t = "";
    if (e.task) {
      let n = this.checkbox({ checked: !!e.checked });
      e.loose ? e.tokens[0]?.type === "paragraph" ? (e.tokens[0].text = n + " " + e.tokens[0].text, e.tokens[0].tokens && e.tokens[0].tokens.length > 0 && e.tokens[0].tokens[0].type === "text" && (e.tokens[0].tokens[0].text = n + " " + w(e.tokens[0].tokens[0].text), e.tokens[0].tokens[0].escaped = true)) : e.tokens.unshift({ type: "text", raw: n + " ", text: n + " ", escaped: true }) : t += n + " ";
    }
    return t += this.parser.parse(e.tokens, !!e.loose), `<li>${t}</li>
`;
  }
  checkbox({ checked: e }) {
    return "<input " + (e ? 'checked="" ' : "") + 'disabled="" type="checkbox">';
  }
  paragraph({ tokens: e }) {
    return `<p>${this.parser.parseInline(e)}</p>
`;
  }
  table(e) {
    let t = "", n = "";
    for (let i = 0; i < e.header.length; i++) n += this.tablecell(e.header[i]);
    t += this.tablerow({ text: n });
    let r = "";
    for (let i = 0; i < e.rows.length; i++) {
      let s = e.rows[i];
      n = "";
      for (let o = 0; o < s.length; o++) n += this.tablecell(s[o]);
      r += this.tablerow({ text: n });
    }
    return r && (r = `<tbody>${r}</tbody>`), `<table>
<thead>
` + t + `</thead>
` + r + `</table>
`;
  }
  tablerow({ text: e }) {
    return `<tr>
${e}</tr>
`;
  }
  tablecell(e) {
    let t = this.parser.parseInline(e.tokens), n = e.header ? "th" : "td";
    return (e.align ? `<${n} align="${e.align}">` : `<${n}>`) + t + `</${n}>
`;
  }
  strong({ tokens: e }) {
    return `<strong>${this.parser.parseInline(e)}</strong>`;
  }
  em({ tokens: e }) {
    return `<em>${this.parser.parseInline(e)}</em>`;
  }
  codespan({ text: e }) {
    return `<code>${w(e, true)}</code>`;
  }
  br(e) {
    return "<br>";
  }
  del({ tokens: e }) {
    return `<del>${this.parser.parseInline(e)}</del>`;
  }
  link({ href: e, title: t, tokens: n }) {
    let r = this.parser.parseInline(n), i = J(e);
    if (i === null) return r;
    e = i;
    let s = '<a href="' + e + '"';
    return t && (s += ' title="' + w(t) + '"'), s += ">" + r + "</a>", s;
  }
  image({ href: e, title: t, text: n, tokens: r }) {
    r && (n = this.parser.parseInline(r, this.parser.textRenderer));
    let i = J(e);
    if (i === null) return w(n);
    e = i;
    let s = `<img src="${e}" alt="${n}"`;
    return t && (s += ` title="${w(t)}"`), s += ">", s;
  }
  text(e) {
    return "tokens" in e && e.tokens ? this.parser.parseInline(e.tokens) : "escaped" in e && e.escaped ? e.text : w(e.text);
  }
};
var $ = class {
  strong({ text: e }) {
    return e;
  }
  em({ text: e }) {
    return e;
  }
  codespan({ text: e }) {
    return e;
  }
  del({ text: e }) {
    return e;
  }
  html({ text: e }) {
    return e;
  }
  text({ text: e }) {
    return e;
  }
  link({ text: e }) {
    return "" + e;
  }
  image({ text: e }) {
    return "" + e;
  }
  br() {
    return "";
  }
};
var b = class u2 {
  options;
  renderer;
  textRenderer;
  constructor(e) {
    this.options = e || T, this.options.renderer = this.options.renderer || new P(), this.renderer = this.options.renderer, this.renderer.options = this.options, this.renderer.parser = this, this.textRenderer = new $();
  }
  static parse(e, t) {
    return new u2(t).parse(e);
  }
  static parseInline(e, t) {
    return new u2(t).parseInline(e);
  }
  parse(e, t = true) {
    let n = "";
    for (let r = 0; r < e.length; r++) {
      let i = e[r];
      if (this.options.extensions?.renderers?.[i.type]) {
        let o = i, a = this.options.extensions.renderers[o.type].call({ parser: this }, o);
        if (a !== false || !["space", "hr", "heading", "code", "table", "blockquote", "list", "html", "def", "paragraph", "text"].includes(o.type)) {
          n += a || "";
          continue;
        }
      }
      let s = i;
      switch (s.type) {
        case "space": {
          n += this.renderer.space(s);
          continue;
        }
        case "hr": {
          n += this.renderer.hr(s);
          continue;
        }
        case "heading": {
          n += this.renderer.heading(s);
          continue;
        }
        case "code": {
          n += this.renderer.code(s);
          continue;
        }
        case "table": {
          n += this.renderer.table(s);
          continue;
        }
        case "blockquote": {
          n += this.renderer.blockquote(s);
          continue;
        }
        case "list": {
          n += this.renderer.list(s);
          continue;
        }
        case "html": {
          n += this.renderer.html(s);
          continue;
        }
        case "def": {
          n += this.renderer.def(s);
          continue;
        }
        case "paragraph": {
          n += this.renderer.paragraph(s);
          continue;
        }
        case "text": {
          let o = s, a = this.renderer.text(o);
          for (; r + 1 < e.length && e[r + 1].type === "text"; ) o = e[++r], a += `
` + this.renderer.text(o);
          t ? n += this.renderer.paragraph({ type: "paragraph", raw: a, text: a, tokens: [{ type: "text", raw: a, text: a, escaped: true }] }) : n += a;
          continue;
        }
        default: {
          let o = 'Token with "' + s.type + '" type was not found.';
          if (this.options.silent) return console.error(o), "";
          throw new Error(o);
        }
      }
    }
    return n;
  }
  parseInline(e, t = this.renderer) {
    let n = "";
    for (let r = 0; r < e.length; r++) {
      let i = e[r];
      if (this.options.extensions?.renderers?.[i.type]) {
        let o = this.options.extensions.renderers[i.type].call({ parser: this }, i);
        if (o !== false || !["escape", "html", "link", "image", "strong", "em", "codespan", "br", "del", "text"].includes(i.type)) {
          n += o || "";
          continue;
        }
      }
      let s = i;
      switch (s.type) {
        case "escape": {
          n += t.text(s);
          break;
        }
        case "html": {
          n += t.html(s);
          break;
        }
        case "link": {
          n += t.link(s);
          break;
        }
        case "image": {
          n += t.image(s);
          break;
        }
        case "strong": {
          n += t.strong(s);
          break;
        }
        case "em": {
          n += t.em(s);
          break;
        }
        case "codespan": {
          n += t.codespan(s);
          break;
        }
        case "br": {
          n += t.br(s);
          break;
        }
        case "del": {
          n += t.del(s);
          break;
        }
        case "text": {
          n += t.text(s);
          break;
        }
        default: {
          let o = 'Token with "' + s.type + '" type was not found.';
          if (this.options.silent) return console.error(o), "";
          throw new Error(o);
        }
      }
    }
    return n;
  }
};
var S = class {
  options;
  block;
  constructor(e) {
    this.options = e || T;
  }
  static passThroughHooks = /* @__PURE__ */ new Set(["preprocess", "postprocess", "processAllTokens", "emStrongMask"]);
  static passThroughHooksRespectAsync = /* @__PURE__ */ new Set(["preprocess", "postprocess", "processAllTokens"]);
  preprocess(e) {
    return e;
  }
  postprocess(e) {
    return e;
  }
  processAllTokens(e) {
    return e;
  }
  emStrongMask(e) {
    return e;
  }
  provideLexer() {
    return this.block ? x.lex : x.lexInline;
  }
  provideParser() {
    return this.block ? b.parse : b.parseInline;
  }
};
var B = class {
  defaults = L();
  options = this.setOptions;
  parse = this.parseMarkdown(true);
  parseInline = this.parseMarkdown(false);
  Parser = b;
  Renderer = P;
  TextRenderer = $;
  Lexer = x;
  Tokenizer = y;
  Hooks = S;
  constructor(...e) {
    this.use(...e);
  }
  walkTokens(e, t) {
    let n = [];
    for (let r of e) switch (n = n.concat(t.call(this, r)), r.type) {
      case "table": {
        let i = r;
        for (let s of i.header) n = n.concat(this.walkTokens(s.tokens, t));
        for (let s of i.rows) for (let o of s) n = n.concat(this.walkTokens(o.tokens, t));
        break;
      }
      case "list": {
        let i = r;
        n = n.concat(this.walkTokens(i.items, t));
        break;
      }
      default: {
        let i = r;
        this.defaults.extensions?.childTokens?.[i.type] ? this.defaults.extensions.childTokens[i.type].forEach((s) => {
          let o = i[s].flat(1 / 0);
          n = n.concat(this.walkTokens(o, t));
        }) : i.tokens && (n = n.concat(this.walkTokens(i.tokens, t)));
      }
    }
    return n;
  }
  use(...e) {
    let t = this.defaults.extensions || { renderers: {}, childTokens: {} };
    return e.forEach((n) => {
      let r = { ...n };
      if (r.async = this.defaults.async || r.async || false, n.extensions && (n.extensions.forEach((i) => {
        if (!i.name) throw new Error("extension name required");
        if ("renderer" in i) {
          let s = t.renderers[i.name];
          s ? t.renderers[i.name] = function(...o) {
            let a = i.renderer.apply(this, o);
            return a === false && (a = s.apply(this, o)), a;
          } : t.renderers[i.name] = i.renderer;
        }
        if ("tokenizer" in i) {
          if (!i.level || i.level !== "block" && i.level !== "inline") throw new Error("extension level must be 'block' or 'inline'");
          let s = t[i.level];
          s ? s.unshift(i.tokenizer) : t[i.level] = [i.tokenizer], i.start && (i.level === "block" ? t.startBlock ? t.startBlock.push(i.start) : t.startBlock = [i.start] : i.level === "inline" && (t.startInline ? t.startInline.push(i.start) : t.startInline = [i.start]));
        }
        "childTokens" in i && i.childTokens && (t.childTokens[i.name] = i.childTokens);
      }), r.extensions = t), n.renderer) {
        let i = this.defaults.renderer || new P(this.defaults);
        for (let s in n.renderer) {
          if (!(s in i)) throw new Error(`renderer '${s}' does not exist`);
          if (["options", "parser"].includes(s)) continue;
          let o = s, a = n.renderer[o], l = i[o];
          i[o] = (...c) => {
            let p = a.apply(i, c);
            return p === false && (p = l.apply(i, c)), p || "";
          };
        }
        r.renderer = i;
      }
      if (n.tokenizer) {
        let i = this.defaults.tokenizer || new y(this.defaults);
        for (let s in n.tokenizer) {
          if (!(s in i)) throw new Error(`tokenizer '${s}' does not exist`);
          if (["options", "rules", "lexer"].includes(s)) continue;
          let o = s, a = n.tokenizer[o], l = i[o];
          i[o] = (...c) => {
            let p = a.apply(i, c);
            return p === false && (p = l.apply(i, c)), p;
          };
        }
        r.tokenizer = i;
      }
      if (n.hooks) {
        let i = this.defaults.hooks || new S();
        for (let s in n.hooks) {
          if (!(s in i)) throw new Error(`hook '${s}' does not exist`);
          if (["options", "block"].includes(s)) continue;
          let o = s, a = n.hooks[o], l = i[o];
          S.passThroughHooks.has(s) ? i[o] = (c) => {
            if (this.defaults.async && S.passThroughHooksRespectAsync.has(s)) return (async () => {
              let g = await a.call(i, c);
              return l.call(i, g);
            })();
            let p = a.call(i, c);
            return l.call(i, p);
          } : i[o] = (...c) => {
            if (this.defaults.async) return (async () => {
              let g = await a.apply(i, c);
              return g === false && (g = await l.apply(i, c)), g;
            })();
            let p = a.apply(i, c);
            return p === false && (p = l.apply(i, c)), p;
          };
        }
        r.hooks = i;
      }
      if (n.walkTokens) {
        let i = this.defaults.walkTokens, s = n.walkTokens;
        r.walkTokens = function(o) {
          let a = [];
          return a.push(s.call(this, o)), i && (a = a.concat(i.call(this, o))), a;
        };
      }
      this.defaults = { ...this.defaults, ...r };
    }), this;
  }
  setOptions(e) {
    return this.defaults = { ...this.defaults, ...e }, this;
  }
  lexer(e, t) {
    return x.lex(e, t ?? this.defaults);
  }
  parser(e, t) {
    return b.parse(e, t ?? this.defaults);
  }
  parseMarkdown(e) {
    return (n, r) => {
      let i = { ...r }, s = { ...this.defaults, ...i }, o = this.onError(!!s.silent, !!s.async);
      if (this.defaults.async === true && i.async === false) return o(new Error("marked(): The async option was set to true by an extension. Remove async: false from the parse options object to return a Promise."));
      if (typeof n > "u" || n === null) return o(new Error("marked(): input parameter is undefined or null"));
      if (typeof n != "string") return o(new Error("marked(): input parameter is of type " + Object.prototype.toString.call(n) + ", string expected"));
      if (s.hooks && (s.hooks.options = s, s.hooks.block = e), s.async) return (async () => {
        let a = s.hooks ? await s.hooks.preprocess(n) : n, c = await (s.hooks ? await s.hooks.provideLexer() : e ? x.lex : x.lexInline)(a, s), p = s.hooks ? await s.hooks.processAllTokens(c) : c;
        s.walkTokens && await Promise.all(this.walkTokens(p, s.walkTokens));
        let h = await (s.hooks ? await s.hooks.provideParser() : e ? b.parse : b.parseInline)(p, s);
        return s.hooks ? await s.hooks.postprocess(h) : h;
      })().catch(o);
      try {
        s.hooks && (n = s.hooks.preprocess(n));
        let l = (s.hooks ? s.hooks.provideLexer() : e ? x.lex : x.lexInline)(n, s);
        s.hooks && (l = s.hooks.processAllTokens(l)), s.walkTokens && this.walkTokens(l, s.walkTokens);
        let p = (s.hooks ? s.hooks.provideParser() : e ? b.parse : b.parseInline)(l, s);
        return s.hooks && (p = s.hooks.postprocess(p)), p;
      } catch (a) {
        return o(a);
      }
    };
  }
  onError(e, t) {
    return (n) => {
      if (n.message += `
Please report this to https://github.com/markedjs/marked.`, e) {
        let r = "<p>An error occurred:</p><pre>" + w(n.message + "", true) + "</pre>";
        return t ? Promise.resolve(r) : r;
      }
      if (t) return Promise.reject(n);
      throw n;
    };
  }
};
var _ = new B();
function k(u3, e) {
  return _.parse(u3, e);
}
k.options = k.setOptions = function(u3) {
  return _.setOptions(u3), k.defaults = _.defaults, G(k.defaults), k;
};
k.getDefaults = L;
k.defaults = T;
k.use = function(...u3) {
  return _.use(...u3), k.defaults = _.defaults, G(k.defaults), k;
};
k.walkTokens = function(u3, e) {
  return _.walkTokens(u3, e);
};
k.parseInline = _.parseInline;
k.Parser = b;
k.parser = b.parse;
k.Renderer = P;
k.TextRenderer = $;
k.Lexer = x;
k.lexer = x.lex;
k.Tokenizer = y;
k.Hooks = S;
k.parse = k;
k.options;
k.setOptions;
k.use;
k.walkTokens;
k.parseInline;
b.parse;
x.lex;
/*! @license DOMPurify 3.4.5 | (c) Cure53 and other contributors | Released under the Apache license 2.0 and Mozilla Public License 2.0 | github.com/cure53/DOMPurify/blob/3.4.5/LICENSE */
function _arrayLikeToArray(r, a) {
  (null == a || a > r.length) && (a = r.length);
  for (var e = 0, n = Array(a); e < a; e++) n[e] = r[e];
  return n;
}
function _arrayWithHoles(r) {
  if (Array.isArray(r)) return r;
}
function _iterableToArrayLimit(r, l) {
  var t = null == r ? null : "undefined" != typeof Symbol && r[Symbol.iterator] || r["@@iterator"];
  if (null != t) {
    var e, n, i, u3, a = [], f = true, o = false;
    try {
      if (i = (t = t.call(r)).next, 0 === l) ;
      else for (; !(f = (e = i.call(t)).done) && (a.push(e.value), a.length !== l); f = true) ;
    } catch (r2) {
      o = true, n = r2;
    } finally {
      try {
        if (!f && null != t.return && (u3 = t.return(), Object(u3) !== u3)) return;
      } finally {
        if (o) throw n;
      }
    }
    return a;
  }
}
function _nonIterableRest() {
  throw new TypeError("Invalid attempt to destructure non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.");
}
function _slicedToArray(r, e) {
  return _arrayWithHoles(r) || _iterableToArrayLimit(r, e) || _unsupportedIterableToArray(r, e) || _nonIterableRest();
}
function _unsupportedIterableToArray(r, a) {
  if (r) {
    if ("string" == typeof r) return _arrayLikeToArray(r, a);
    var t = {}.toString.call(r).slice(8, -1);
    return "Object" === t && r.constructor && (t = r.constructor.name), "Map" === t || "Set" === t ? Array.from(r) : "Arguments" === t || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(t) ? _arrayLikeToArray(r, a) : void 0;
  }
}
const entries = Object.entries, setPrototypeOf = Object.setPrototypeOf, isFrozen = Object.isFrozen, getPrototypeOf = Object.getPrototypeOf, getOwnPropertyDescriptor = Object.getOwnPropertyDescriptor;
let freeze = Object.freeze, seal = Object.seal, create = Object.create;
let _ref = typeof Reflect !== "undefined" && Reflect, apply = _ref.apply, construct = _ref.construct;
if (!freeze) {
  freeze = function freeze2(x2) {
    return x2;
  };
}
if (!seal) {
  seal = function seal2(x2) {
    return x2;
  };
}
if (!apply) {
  apply = function apply2(func, thisArg) {
    for (var _len = arguments.length, args = new Array(_len > 2 ? _len - 2 : 0), _key = 2; _key < _len; _key++) {
      args[_key - 2] = arguments[_key];
    }
    return func.apply(thisArg, args);
  };
}
if (!construct) {
  construct = function construct2(Func) {
    for (var _len2 = arguments.length, args = new Array(_len2 > 1 ? _len2 - 1 : 0), _key2 = 1; _key2 < _len2; _key2++) {
      args[_key2 - 1] = arguments[_key2];
    }
    return new Func(...args);
  };
}
const arrayForEach = unapply(Array.prototype.forEach);
const arrayLastIndexOf = unapply(Array.prototype.lastIndexOf);
const arrayPop = unapply(Array.prototype.pop);
const arrayPush = unapply(Array.prototype.push);
const arraySplice = unapply(Array.prototype.splice);
const arrayIsArray = Array.isArray;
const stringToLowerCase = unapply(String.prototype.toLowerCase);
const stringToString = unapply(String.prototype.toString);
const stringMatch = unapply(String.prototype.match);
const stringReplace = unapply(String.prototype.replace);
const stringIndexOf = unapply(String.prototype.indexOf);
const stringTrim = unapply(String.prototype.trim);
const numberToString = unapply(Number.prototype.toString);
const booleanToString = unapply(Boolean.prototype.toString);
const bigintToString = typeof BigInt === "undefined" ? null : unapply(BigInt.prototype.toString);
const symbolToString = typeof Symbol === "undefined" ? null : unapply(Symbol.prototype.toString);
const objectHasOwnProperty = unapply(Object.prototype.hasOwnProperty);
const objectToString = unapply(Object.prototype.toString);
const regExpTest = unapply(RegExp.prototype.test);
const typeErrorCreate = unconstruct(TypeError);
function unapply(func) {
  return function(thisArg) {
    if (thisArg instanceof RegExp) {
      thisArg.lastIndex = 0;
    }
    for (var _len3 = arguments.length, args = new Array(_len3 > 1 ? _len3 - 1 : 0), _key3 = 1; _key3 < _len3; _key3++) {
      args[_key3 - 1] = arguments[_key3];
    }
    return apply(func, thisArg, args);
  };
}
function unconstruct(Func) {
  return function() {
    for (var _len4 = arguments.length, args = new Array(_len4), _key4 = 0; _key4 < _len4; _key4++) {
      args[_key4] = arguments[_key4];
    }
    return construct(Func, args);
  };
}
function addToSet(set, array) {
  let transformCaseFunc = arguments.length > 2 && arguments[2] !== void 0 ? arguments[2] : stringToLowerCase;
  if (setPrototypeOf) {
    setPrototypeOf(set, null);
  }
  if (!arrayIsArray(array)) {
    return set;
  }
  let l = array.length;
  while (l--) {
    let element = array[l];
    if (typeof element === "string") {
      const lcElement = transformCaseFunc(element);
      if (lcElement !== element) {
        if (!isFrozen(array)) {
          array[l] = lcElement;
        }
        element = lcElement;
      }
    }
    set[element] = true;
  }
  return set;
}
function cleanArray(array) {
  for (let index = 0; index < array.length; index++) {
    const isPropertyExist = objectHasOwnProperty(array, index);
    if (!isPropertyExist) {
      array[index] = null;
    }
  }
  return array;
}
function clone(object) {
  const newObject = create(null);
  for (const _ref2 of entries(object)) {
    var _ref3 = _slicedToArray(_ref2, 2);
    const property = _ref3[0];
    const value = _ref3[1];
    const isPropertyExist = objectHasOwnProperty(object, property);
    if (isPropertyExist) {
      if (arrayIsArray(value)) {
        newObject[property] = cleanArray(value);
      } else if (value && typeof value === "object" && value.constructor === Object) {
        newObject[property] = clone(value);
      } else {
        newObject[property] = value;
      }
    }
  }
  return newObject;
}
function stringifyValue(value) {
  switch (typeof value) {
    case "string": {
      return value;
    }
    case "number": {
      return numberToString(value);
    }
    case "boolean": {
      return booleanToString(value);
    }
    case "bigint": {
      return bigintToString ? bigintToString(value) : "0";
    }
    case "symbol": {
      return symbolToString ? symbolToString(value) : "Symbol()";
    }
    case "undefined": {
      return objectToString(value);
    }
    case "function":
    case "object": {
      if (value === null) {
        return objectToString(value);
      }
      const valueAsRecord = value;
      const valueToString = lookupGetter(valueAsRecord, "toString");
      if (typeof valueToString === "function") {
        const stringified = valueToString(valueAsRecord);
        return typeof stringified === "string" ? stringified : objectToString(stringified);
      }
      return objectToString(value);
    }
    default: {
      return objectToString(value);
    }
  }
}
function lookupGetter(object, prop) {
  while (object !== null) {
    const desc = getOwnPropertyDescriptor(object, prop);
    if (desc) {
      if (desc.get) {
        return unapply(desc.get);
      }
      if (typeof desc.value === "function") {
        return unapply(desc.value);
      }
    }
    object = getPrototypeOf(object);
  }
  function fallbackValue() {
    return null;
  }
  return fallbackValue;
}
function isRegex(value) {
  try {
    regExpTest(value, "");
    return true;
  } catch (_unused) {
    return false;
  }
}
const html$1 = freeze(["a", "abbr", "acronym", "address", "area", "article", "aside", "audio", "b", "bdi", "bdo", "big", "blink", "blockquote", "body", "br", "button", "canvas", "caption", "center", "cite", "code", "col", "colgroup", "content", "data", "datalist", "dd", "decorator", "del", "details", "dfn", "dialog", "dir", "div", "dl", "dt", "element", "em", "fieldset", "figcaption", "figure", "font", "footer", "form", "h1", "h2", "h3", "h4", "h5", "h6", "head", "header", "hgroup", "hr", "html", "i", "img", "input", "ins", "kbd", "label", "legend", "li", "main", "map", "mark", "marquee", "menu", "menuitem", "meter", "nav", "nobr", "ol", "optgroup", "option", "output", "p", "picture", "pre", "progress", "q", "rp", "rt", "ruby", "s", "samp", "search", "section", "select", "shadow", "slot", "small", "source", "spacer", "span", "strike", "strong", "style", "sub", "summary", "sup", "table", "tbody", "td", "template", "textarea", "tfoot", "th", "thead", "time", "tr", "track", "tt", "u", "ul", "var", "video", "wbr"]);
const svg$1 = freeze(["svg", "a", "altglyph", "altglyphdef", "altglyphitem", "animatecolor", "animatemotion", "animatetransform", "circle", "clippath", "defs", "desc", "ellipse", "enterkeyhint", "exportparts", "filter", "font", "g", "glyph", "glyphref", "hkern", "image", "inputmode", "line", "lineargradient", "marker", "mask", "metadata", "mpath", "part", "path", "pattern", "polygon", "polyline", "radialgradient", "rect", "stop", "style", "switch", "symbol", "text", "textpath", "title", "tref", "tspan", "view", "vkern"]);
const svgFilters = freeze(["feBlend", "feColorMatrix", "feComponentTransfer", "feComposite", "feConvolveMatrix", "feDiffuseLighting", "feDisplacementMap", "feDistantLight", "feDropShadow", "feFlood", "feFuncA", "feFuncB", "feFuncG", "feFuncR", "feGaussianBlur", "feImage", "feMerge", "feMergeNode", "feMorphology", "feOffset", "fePointLight", "feSpecularLighting", "feSpotLight", "feTile", "feTurbulence"]);
const svgDisallowed = freeze(["animate", "color-profile", "cursor", "discard", "font-face", "font-face-format", "font-face-name", "font-face-src", "font-face-uri", "foreignobject", "hatch", "hatchpath", "mesh", "meshgradient", "meshpatch", "meshrow", "missing-glyph", "script", "set", "solidcolor", "unknown", "use"]);
const mathMl$1 = freeze(["math", "menclose", "merror", "mfenced", "mfrac", "mglyph", "mi", "mlabeledtr", "mmultiscripts", "mn", "mo", "mover", "mpadded", "mphantom", "mroot", "mrow", "ms", "mspace", "msqrt", "mstyle", "msub", "msup", "msubsup", "mtable", "mtd", "mtext", "mtr", "munder", "munderover", "mprescripts"]);
const mathMlDisallowed = freeze(["maction", "maligngroup", "malignmark", "mlongdiv", "mscarries", "mscarry", "msgroup", "mstack", "msline", "msrow", "semantics", "annotation", "annotation-xml", "mprescripts", "none"]);
const text = freeze(["#text"]);
const html = freeze(["accept", "action", "align", "alt", "autocapitalize", "autocomplete", "autopictureinpicture", "autoplay", "background", "bgcolor", "border", "capture", "cellpadding", "cellspacing", "checked", "cite", "class", "clear", "color", "cols", "colspan", "command", "commandfor", "controls", "controlslist", "coords", "crossorigin", "datetime", "decoding", "default", "dir", "disabled", "disablepictureinpicture", "disableremoteplayback", "download", "draggable", "enctype", "enterkeyhint", "exportparts", "face", "for", "headers", "height", "hidden", "high", "href", "hreflang", "id", "inert", "inputmode", "integrity", "ismap", "kind", "label", "lang", "list", "loading", "loop", "low", "max", "maxlength", "media", "method", "min", "minlength", "multiple", "muted", "name", "nonce", "noshade", "novalidate", "nowrap", "open", "optimum", "part", "pattern", "placeholder", "playsinline", "popover", "popovertarget", "popovertargetaction", "poster", "preload", "pubdate", "radiogroup", "readonly", "rel", "required", "rev", "reversed", "role", "rows", "rowspan", "spellcheck", "scope", "selected", "shape", "size", "sizes", "slot", "span", "srclang", "start", "src", "srcset", "step", "style", "summary", "tabindex", "title", "translate", "type", "usemap", "valign", "value", "width", "wrap", "xmlns"]);
const svg = freeze(["accent-height", "accumulate", "additive", "alignment-baseline", "amplitude", "ascent", "attributename", "attributetype", "azimuth", "basefrequency", "baseline-shift", "begin", "bias", "by", "class", "clip", "clippathunits", "clip-path", "clip-rule", "color", "color-interpolation", "color-interpolation-filters", "color-profile", "color-rendering", "cx", "cy", "d", "dx", "dy", "diffuseconstant", "direction", "display", "divisor", "dur", "edgemode", "elevation", "end", "exponent", "fill", "fill-opacity", "fill-rule", "filter", "filterunits", "flood-color", "flood-opacity", "font-family", "font-size", "font-size-adjust", "font-stretch", "font-style", "font-variant", "font-weight", "fx", "fy", "g1", "g2", "glyph-name", "glyphref", "gradientunits", "gradienttransform", "height", "href", "id", "image-rendering", "in", "in2", "intercept", "k", "k1", "k2", "k3", "k4", "kerning", "keypoints", "keysplines", "keytimes", "lang", "lengthadjust", "letter-spacing", "kernelmatrix", "kernelunitlength", "lighting-color", "local", "marker-end", "marker-mid", "marker-start", "markerheight", "markerunits", "markerwidth", "maskcontentunits", "maskunits", "max", "mask", "mask-type", "media", "method", "mode", "min", "name", "numoctaves", "offset", "operator", "opacity", "order", "orient", "orientation", "origin", "overflow", "paint-order", "path", "pathlength", "patterncontentunits", "patterntransform", "patternunits", "points", "preservealpha", "preserveaspectratio", "primitiveunits", "r", "rx", "ry", "radius", "refx", "refy", "repeatcount", "repeatdur", "restart", "result", "rotate", "scale", "seed", "shape-rendering", "slope", "specularconstant", "specularexponent", "spreadmethod", "startoffset", "stddeviation", "stitchtiles", "stop-color", "stop-opacity", "stroke-dasharray", "stroke-dashoffset", "stroke-linecap", "stroke-linejoin", "stroke-miterlimit", "stroke-opacity", "stroke", "stroke-width", "style", "surfacescale", "systemlanguage", "tabindex", "tablevalues", "targetx", "targety", "transform", "transform-origin", "text-anchor", "text-decoration", "text-rendering", "textlength", "type", "u1", "u2", "unicode", "values", "viewbox", "visibility", "version", "vert-adv-y", "vert-origin-x", "vert-origin-y", "width", "word-spacing", "wrap", "writing-mode", "xchannelselector", "ychannelselector", "x", "x1", "x2", "xmlns", "y", "y1", "y2", "z", "zoomandpan"]);
const mathMl = freeze(["accent", "accentunder", "align", "bevelled", "close", "columnalign", "columnlines", "columnspacing", "columnspan", "denomalign", "depth", "dir", "display", "displaystyle", "encoding", "fence", "frame", "height", "href", "id", "largeop", "length", "linethickness", "lquote", "lspace", "mathbackground", "mathcolor", "mathsize", "mathvariant", "maxsize", "minsize", "movablelimits", "notation", "numalign", "open", "rowalign", "rowlines", "rowspacing", "rowspan", "rspace", "rquote", "scriptlevel", "scriptminsize", "scriptsizemultiplier", "selection", "separator", "separators", "stretchy", "subscriptshift", "supscriptshift", "symmetric", "voffset", "width", "xmlns"]);
const xml = freeze(["xlink:href", "xml:id", "xlink:title", "xml:space", "xmlns:xlink"]);
const MUSTACHE_EXPR = seal(/{{[\w\W]*|^[\w\W]*}}/g);
const ERB_EXPR = seal(/<%[\w\W]*|^[\w\W]*%>/g);
const TMPLIT_EXPR = seal(/\${[\w\W]*/g);
const DATA_ATTR = seal(/^data-[\-\w.\u00B7-\uFFFF]+$/);
const ARIA_ATTR = seal(/^aria-[\-\w]+$/);
const IS_ALLOWED_URI = seal(
  /^(?:(?:(?:f|ht)tps?|mailto|tel|callto|sms|cid|xmpp|matrix):|[^a-z]|[a-z+.\-]+(?:[^a-z+.\-:]|$))/i
  // eslint-disable-line no-useless-escape
);
const IS_SCRIPT_OR_DATA = seal(/^(?:\w+script|data):/i);
const ATTR_WHITESPACE = seal(
  /[\u0000-\u0020\u00A0\u1680\u180E\u2000-\u2029\u205F\u3000]/g
  // eslint-disable-line no-control-regex
);
const DOCTYPE_NAME = seal(/^html$/i);
const CUSTOM_ELEMENT = seal(/^[a-z][.\w]*(-[.\w]+)+$/i);
const NODE_TYPE = {
  element: 1,
  text: 3,
  // Deprecated
  progressingInstruction: 7,
  comment: 8,
  document: 9
};
const getGlobal = function getGlobal2() {
  return typeof window === "undefined" ? null : window;
};
const _createTrustedTypesPolicy = function _createTrustedTypesPolicy2(trustedTypes, purifyHostElement) {
  if (typeof trustedTypes !== "object" || typeof trustedTypes.createPolicy !== "function") {
    return null;
  }
  let suffix = null;
  const ATTR_NAME = "data-tt-policy-suffix";
  if (purifyHostElement && purifyHostElement.hasAttribute(ATTR_NAME)) {
    suffix = purifyHostElement.getAttribute(ATTR_NAME);
  }
  const policyName = "dompurify" + (suffix ? "#" + suffix : "");
  try {
    return trustedTypes.createPolicy(policyName, {
      createHTML(html2) {
        return html2;
      },
      createScriptURL(scriptUrl) {
        return scriptUrl;
      }
    });
  } catch (_2) {
    console.warn("TrustedTypes policy " + policyName + " could not be created.");
    return null;
  }
};
const _createHooksMap = function _createHooksMap2() {
  return {
    afterSanitizeAttributes: [],
    afterSanitizeElements: [],
    afterSanitizeShadowDOM: [],
    beforeSanitizeAttributes: [],
    beforeSanitizeElements: [],
    beforeSanitizeShadowDOM: [],
    uponSanitizeAttribute: [],
    uponSanitizeElement: [],
    uponSanitizeShadowNode: []
  };
};
function createDOMPurify() {
  let window2 = arguments.length > 0 && arguments[0] !== void 0 ? arguments[0] : getGlobal();
  const DOMPurify = (root) => createDOMPurify(root);
  DOMPurify.version = "3.4.5";
  DOMPurify.removed = [];
  if (!window2 || !window2.document || window2.document.nodeType !== NODE_TYPE.document || !window2.Element) {
    DOMPurify.isSupported = false;
    return DOMPurify;
  }
  let document2 = window2.document;
  const originalDocument = document2;
  const currentScript = originalDocument.currentScript;
  const DocumentFragment = window2.DocumentFragment, HTMLTemplateElement = window2.HTMLTemplateElement, Node = window2.Node, Element = window2.Element, NodeFilter = window2.NodeFilter, _window$NamedNodeMap = window2.NamedNodeMap, NamedNodeMap = _window$NamedNodeMap === void 0 ? window2.NamedNodeMap || window2.MozNamedAttrMap : _window$NamedNodeMap, HTMLFormElement = window2.HTMLFormElement, DOMParser = window2.DOMParser, trustedTypes = window2.trustedTypes;
  const ElementPrototype = Element.prototype;
  const cloneNode = lookupGetter(ElementPrototype, "cloneNode");
  const remove = lookupGetter(ElementPrototype, "remove");
  const getNextSibling = lookupGetter(ElementPrototype, "nextSibling");
  const getChildNodes = lookupGetter(ElementPrototype, "childNodes");
  const getParentNode = lookupGetter(ElementPrototype, "parentNode");
  const getNodeType = Node && Node.prototype ? lookupGetter(Node.prototype, "nodeType") : null;
  if (typeof HTMLTemplateElement === "function") {
    const template = document2.createElement("template");
    if (template.content && template.content.ownerDocument) {
      document2 = template.content.ownerDocument;
    }
  }
  let trustedTypesPolicy;
  let emptyHTML = "";
  const _document = document2, implementation = _document.implementation, createNodeIterator = _document.createNodeIterator, createDocumentFragment = _document.createDocumentFragment, getElementsByTagName = _document.getElementsByTagName;
  const importNode = originalDocument.importNode;
  let hooks = _createHooksMap();
  DOMPurify.isSupported = typeof entries === "function" && typeof getParentNode === "function" && implementation && implementation.createHTMLDocument !== void 0;
  const MUSTACHE_EXPR$1 = MUSTACHE_EXPR, ERB_EXPR$1 = ERB_EXPR, TMPLIT_EXPR$1 = TMPLIT_EXPR, DATA_ATTR$1 = DATA_ATTR, ARIA_ATTR$1 = ARIA_ATTR, IS_SCRIPT_OR_DATA$1 = IS_SCRIPT_OR_DATA, ATTR_WHITESPACE$1 = ATTR_WHITESPACE, CUSTOM_ELEMENT$1 = CUSTOM_ELEMENT;
  let IS_ALLOWED_URI$1 = IS_ALLOWED_URI;
  let ALLOWED_TAGS = null;
  const DEFAULT_ALLOWED_TAGS = addToSet({}, [...html$1, ...svg$1, ...svgFilters, ...mathMl$1, ...text]);
  let ALLOWED_ATTR = null;
  const DEFAULT_ALLOWED_ATTR = addToSet({}, [...html, ...svg, ...mathMl, ...xml]);
  let CUSTOM_ELEMENT_HANDLING = Object.seal(create(null, {
    tagNameCheck: {
      writable: true,
      configurable: false,
      enumerable: true,
      value: null
    },
    attributeNameCheck: {
      writable: true,
      configurable: false,
      enumerable: true,
      value: null
    },
    allowCustomizedBuiltInElements: {
      writable: true,
      configurable: false,
      enumerable: true,
      value: false
    }
  }));
  let FORBID_TAGS = null;
  let FORBID_ATTR = null;
  const EXTRA_ELEMENT_HANDLING = Object.seal(create(null, {
    tagCheck: {
      writable: true,
      configurable: false,
      enumerable: true,
      value: null
    },
    attributeCheck: {
      writable: true,
      configurable: false,
      enumerable: true,
      value: null
    }
  }));
  let ALLOW_ARIA_ATTR = true;
  let ALLOW_DATA_ATTR = true;
  let ALLOW_UNKNOWN_PROTOCOLS = false;
  let ALLOW_SELF_CLOSE_IN_ATTR = true;
  let SAFE_FOR_TEMPLATES = false;
  let SAFE_FOR_XML = true;
  let WHOLE_DOCUMENT = false;
  let SET_CONFIG = false;
  let FORCE_BODY = false;
  let RETURN_DOM = false;
  let RETURN_DOM_FRAGMENT = false;
  let RETURN_TRUSTED_TYPE = false;
  let SANITIZE_DOM = true;
  let SANITIZE_NAMED_PROPS = false;
  const SANITIZE_NAMED_PROPS_PREFIX = "user-content-";
  let KEEP_CONTENT = true;
  let IN_PLACE = false;
  let USE_PROFILES = {};
  let FORBID_CONTENTS = null;
  const DEFAULT_FORBID_CONTENTS = addToSet({}, ["annotation-xml", "audio", "colgroup", "desc", "foreignobject", "head", "iframe", "math", "mi", "mn", "mo", "ms", "mtext", "noembed", "noframes", "noscript", "plaintext", "script", "style", "svg", "template", "thead", "title", "video", "xmp"]);
  let DATA_URI_TAGS = null;
  const DEFAULT_DATA_URI_TAGS = addToSet({}, ["audio", "video", "img", "source", "image", "track"]);
  let URI_SAFE_ATTRIBUTES = null;
  const DEFAULT_URI_SAFE_ATTRIBUTES = addToSet({}, ["alt", "class", "for", "id", "label", "name", "pattern", "placeholder", "role", "summary", "title", "value", "style", "xmlns"]);
  const MATHML_NAMESPACE = "http://www.w3.org/1998/Math/MathML";
  const SVG_NAMESPACE = "http://www.w3.org/2000/svg";
  const HTML_NAMESPACE = "http://www.w3.org/1999/xhtml";
  let NAMESPACE = HTML_NAMESPACE;
  let IS_EMPTY_INPUT = false;
  let ALLOWED_NAMESPACES = null;
  const DEFAULT_ALLOWED_NAMESPACES = addToSet({}, [MATHML_NAMESPACE, SVG_NAMESPACE, HTML_NAMESPACE], stringToString);
  let MATHML_TEXT_INTEGRATION_POINTS = addToSet({}, ["mi", "mo", "mn", "ms", "mtext"]);
  let HTML_INTEGRATION_POINTS = addToSet({}, ["annotation-xml"]);
  const COMMON_SVG_AND_HTML_ELEMENTS = addToSet({}, ["title", "style", "font", "a", "script"]);
  let PARSER_MEDIA_TYPE = null;
  const SUPPORTED_PARSER_MEDIA_TYPES = ["application/xhtml+xml", "text/html"];
  const DEFAULT_PARSER_MEDIA_TYPE = "text/html";
  let transformCaseFunc = null;
  let CONFIG = null;
  const formElement = document2.createElement("form");
  const isRegexOrFunction = function isRegexOrFunction2(testValue) {
    return testValue instanceof RegExp || testValue instanceof Function;
  };
  const _parseConfig = function _parseConfig2() {
    let cfg = arguments.length > 0 && arguments[0] !== void 0 ? arguments[0] : {};
    if (CONFIG && CONFIG === cfg) {
      return;
    }
    if (!cfg || typeof cfg !== "object") {
      cfg = {};
    }
    cfg = clone(cfg);
    PARSER_MEDIA_TYPE = // eslint-disable-next-line unicorn/prefer-includes
    SUPPORTED_PARSER_MEDIA_TYPES.indexOf(cfg.PARSER_MEDIA_TYPE) === -1 ? DEFAULT_PARSER_MEDIA_TYPE : cfg.PARSER_MEDIA_TYPE;
    transformCaseFunc = PARSER_MEDIA_TYPE === "application/xhtml+xml" ? stringToString : stringToLowerCase;
    ALLOWED_TAGS = objectHasOwnProperty(cfg, "ALLOWED_TAGS") && arrayIsArray(cfg.ALLOWED_TAGS) ? addToSet({}, cfg.ALLOWED_TAGS, transformCaseFunc) : DEFAULT_ALLOWED_TAGS;
    ALLOWED_ATTR = objectHasOwnProperty(cfg, "ALLOWED_ATTR") && arrayIsArray(cfg.ALLOWED_ATTR) ? addToSet({}, cfg.ALLOWED_ATTR, transformCaseFunc) : DEFAULT_ALLOWED_ATTR;
    ALLOWED_NAMESPACES = objectHasOwnProperty(cfg, "ALLOWED_NAMESPACES") && arrayIsArray(cfg.ALLOWED_NAMESPACES) ? addToSet({}, cfg.ALLOWED_NAMESPACES, stringToString) : DEFAULT_ALLOWED_NAMESPACES;
    URI_SAFE_ATTRIBUTES = objectHasOwnProperty(cfg, "ADD_URI_SAFE_ATTR") && arrayIsArray(cfg.ADD_URI_SAFE_ATTR) ? addToSet(clone(DEFAULT_URI_SAFE_ATTRIBUTES), cfg.ADD_URI_SAFE_ATTR, transformCaseFunc) : DEFAULT_URI_SAFE_ATTRIBUTES;
    DATA_URI_TAGS = objectHasOwnProperty(cfg, "ADD_DATA_URI_TAGS") && arrayIsArray(cfg.ADD_DATA_URI_TAGS) ? addToSet(clone(DEFAULT_DATA_URI_TAGS), cfg.ADD_DATA_URI_TAGS, transformCaseFunc) : DEFAULT_DATA_URI_TAGS;
    FORBID_CONTENTS = objectHasOwnProperty(cfg, "FORBID_CONTENTS") && arrayIsArray(cfg.FORBID_CONTENTS) ? addToSet({}, cfg.FORBID_CONTENTS, transformCaseFunc) : DEFAULT_FORBID_CONTENTS;
    FORBID_TAGS = objectHasOwnProperty(cfg, "FORBID_TAGS") && arrayIsArray(cfg.FORBID_TAGS) ? addToSet({}, cfg.FORBID_TAGS, transformCaseFunc) : clone({});
    FORBID_ATTR = objectHasOwnProperty(cfg, "FORBID_ATTR") && arrayIsArray(cfg.FORBID_ATTR) ? addToSet({}, cfg.FORBID_ATTR, transformCaseFunc) : clone({});
    USE_PROFILES = objectHasOwnProperty(cfg, "USE_PROFILES") ? cfg.USE_PROFILES && typeof cfg.USE_PROFILES === "object" ? clone(cfg.USE_PROFILES) : cfg.USE_PROFILES : false;
    ALLOW_ARIA_ATTR = cfg.ALLOW_ARIA_ATTR !== false;
    ALLOW_DATA_ATTR = cfg.ALLOW_DATA_ATTR !== false;
    ALLOW_UNKNOWN_PROTOCOLS = cfg.ALLOW_UNKNOWN_PROTOCOLS || false;
    ALLOW_SELF_CLOSE_IN_ATTR = cfg.ALLOW_SELF_CLOSE_IN_ATTR !== false;
    SAFE_FOR_TEMPLATES = cfg.SAFE_FOR_TEMPLATES || false;
    SAFE_FOR_XML = cfg.SAFE_FOR_XML !== false;
    WHOLE_DOCUMENT = cfg.WHOLE_DOCUMENT || false;
    RETURN_DOM = cfg.RETURN_DOM || false;
    RETURN_DOM_FRAGMENT = cfg.RETURN_DOM_FRAGMENT || false;
    RETURN_TRUSTED_TYPE = cfg.RETURN_TRUSTED_TYPE || false;
    FORCE_BODY = cfg.FORCE_BODY || false;
    SANITIZE_DOM = cfg.SANITIZE_DOM !== false;
    SANITIZE_NAMED_PROPS = cfg.SANITIZE_NAMED_PROPS || false;
    KEEP_CONTENT = cfg.KEEP_CONTENT !== false;
    IN_PLACE = cfg.IN_PLACE || false;
    IS_ALLOWED_URI$1 = isRegex(cfg.ALLOWED_URI_REGEXP) ? cfg.ALLOWED_URI_REGEXP : IS_ALLOWED_URI;
    NAMESPACE = typeof cfg.NAMESPACE === "string" ? cfg.NAMESPACE : HTML_NAMESPACE;
    MATHML_TEXT_INTEGRATION_POINTS = objectHasOwnProperty(cfg, "MATHML_TEXT_INTEGRATION_POINTS") && cfg.MATHML_TEXT_INTEGRATION_POINTS && typeof cfg.MATHML_TEXT_INTEGRATION_POINTS === "object" ? clone(cfg.MATHML_TEXT_INTEGRATION_POINTS) : addToSet({}, ["mi", "mo", "mn", "ms", "mtext"]);
    HTML_INTEGRATION_POINTS = objectHasOwnProperty(cfg, "HTML_INTEGRATION_POINTS") && cfg.HTML_INTEGRATION_POINTS && typeof cfg.HTML_INTEGRATION_POINTS === "object" ? clone(cfg.HTML_INTEGRATION_POINTS) : addToSet({}, ["annotation-xml"]);
    const customElementHandling = objectHasOwnProperty(cfg, "CUSTOM_ELEMENT_HANDLING") && cfg.CUSTOM_ELEMENT_HANDLING && typeof cfg.CUSTOM_ELEMENT_HANDLING === "object" ? clone(cfg.CUSTOM_ELEMENT_HANDLING) : create(null);
    CUSTOM_ELEMENT_HANDLING = create(null);
    if (objectHasOwnProperty(customElementHandling, "tagNameCheck") && isRegexOrFunction(customElementHandling.tagNameCheck)) {
      CUSTOM_ELEMENT_HANDLING.tagNameCheck = customElementHandling.tagNameCheck;
    }
    if (objectHasOwnProperty(customElementHandling, "attributeNameCheck") && isRegexOrFunction(customElementHandling.attributeNameCheck)) {
      CUSTOM_ELEMENT_HANDLING.attributeNameCheck = customElementHandling.attributeNameCheck;
    }
    if (objectHasOwnProperty(customElementHandling, "allowCustomizedBuiltInElements") && typeof customElementHandling.allowCustomizedBuiltInElements === "boolean") {
      CUSTOM_ELEMENT_HANDLING.allowCustomizedBuiltInElements = customElementHandling.allowCustomizedBuiltInElements;
    }
    if (SAFE_FOR_TEMPLATES) {
      ALLOW_DATA_ATTR = false;
    }
    if (RETURN_DOM_FRAGMENT) {
      RETURN_DOM = true;
    }
    if (USE_PROFILES) {
      ALLOWED_TAGS = addToSet({}, text);
      ALLOWED_ATTR = create(null);
      if (USE_PROFILES.html === true) {
        addToSet(ALLOWED_TAGS, html$1);
        addToSet(ALLOWED_ATTR, html);
      }
      if (USE_PROFILES.svg === true) {
        addToSet(ALLOWED_TAGS, svg$1);
        addToSet(ALLOWED_ATTR, svg);
        addToSet(ALLOWED_ATTR, xml);
      }
      if (USE_PROFILES.svgFilters === true) {
        addToSet(ALLOWED_TAGS, svgFilters);
        addToSet(ALLOWED_ATTR, svg);
        addToSet(ALLOWED_ATTR, xml);
      }
      if (USE_PROFILES.mathMl === true) {
        addToSet(ALLOWED_TAGS, mathMl$1);
        addToSet(ALLOWED_ATTR, mathMl);
        addToSet(ALLOWED_ATTR, xml);
      }
    }
    EXTRA_ELEMENT_HANDLING.tagCheck = null;
    EXTRA_ELEMENT_HANDLING.attributeCheck = null;
    if (objectHasOwnProperty(cfg, "ADD_TAGS")) {
      if (typeof cfg.ADD_TAGS === "function") {
        EXTRA_ELEMENT_HANDLING.tagCheck = cfg.ADD_TAGS;
      } else if (arrayIsArray(cfg.ADD_TAGS)) {
        if (ALLOWED_TAGS === DEFAULT_ALLOWED_TAGS) {
          ALLOWED_TAGS = clone(ALLOWED_TAGS);
        }
        addToSet(ALLOWED_TAGS, cfg.ADD_TAGS, transformCaseFunc);
      }
    }
    if (objectHasOwnProperty(cfg, "ADD_ATTR")) {
      if (typeof cfg.ADD_ATTR === "function") {
        EXTRA_ELEMENT_HANDLING.attributeCheck = cfg.ADD_ATTR;
      } else if (arrayIsArray(cfg.ADD_ATTR)) {
        if (ALLOWED_ATTR === DEFAULT_ALLOWED_ATTR) {
          ALLOWED_ATTR = clone(ALLOWED_ATTR);
        }
        addToSet(ALLOWED_ATTR, cfg.ADD_ATTR, transformCaseFunc);
      }
    }
    if (objectHasOwnProperty(cfg, "ADD_URI_SAFE_ATTR") && arrayIsArray(cfg.ADD_URI_SAFE_ATTR)) {
      addToSet(URI_SAFE_ATTRIBUTES, cfg.ADD_URI_SAFE_ATTR, transformCaseFunc);
    }
    if (objectHasOwnProperty(cfg, "FORBID_CONTENTS") && arrayIsArray(cfg.FORBID_CONTENTS)) {
      if (FORBID_CONTENTS === DEFAULT_FORBID_CONTENTS) {
        FORBID_CONTENTS = clone(FORBID_CONTENTS);
      }
      addToSet(FORBID_CONTENTS, cfg.FORBID_CONTENTS, transformCaseFunc);
    }
    if (objectHasOwnProperty(cfg, "ADD_FORBID_CONTENTS") && arrayIsArray(cfg.ADD_FORBID_CONTENTS)) {
      if (FORBID_CONTENTS === DEFAULT_FORBID_CONTENTS) {
        FORBID_CONTENTS = clone(FORBID_CONTENTS);
      }
      addToSet(FORBID_CONTENTS, cfg.ADD_FORBID_CONTENTS, transformCaseFunc);
    }
    if (KEEP_CONTENT) {
      ALLOWED_TAGS["#text"] = true;
    }
    if (WHOLE_DOCUMENT) {
      addToSet(ALLOWED_TAGS, ["html", "head", "body"]);
    }
    if (ALLOWED_TAGS.table) {
      addToSet(ALLOWED_TAGS, ["tbody"]);
      delete FORBID_TAGS.tbody;
    }
    if (cfg.TRUSTED_TYPES_POLICY) {
      if (typeof cfg.TRUSTED_TYPES_POLICY.createHTML !== "function") {
        throw typeErrorCreate('TRUSTED_TYPES_POLICY configuration option must provide a "createHTML" hook.');
      }
      if (typeof cfg.TRUSTED_TYPES_POLICY.createScriptURL !== "function") {
        throw typeErrorCreate('TRUSTED_TYPES_POLICY configuration option must provide a "createScriptURL" hook.');
      }
      trustedTypesPolicy = cfg.TRUSTED_TYPES_POLICY;
      emptyHTML = trustedTypesPolicy.createHTML("");
    } else {
      if (trustedTypesPolicy === void 0) {
        trustedTypesPolicy = _createTrustedTypesPolicy(trustedTypes, currentScript);
      }
      if (trustedTypesPolicy !== null && typeof emptyHTML === "string") {
        emptyHTML = trustedTypesPolicy.createHTML("");
      }
    }
    if (freeze) {
      freeze(cfg);
    }
    CONFIG = cfg;
  };
  const ALL_SVG_TAGS = addToSet({}, [...svg$1, ...svgFilters, ...svgDisallowed]);
  const ALL_MATHML_TAGS = addToSet({}, [...mathMl$1, ...mathMlDisallowed]);
  const _checkValidNamespace = function _checkValidNamespace2(element) {
    let parent = getParentNode(element);
    if (!parent || !parent.tagName) {
      parent = {
        namespaceURI: NAMESPACE,
        tagName: "template"
      };
    }
    const tagName = stringToLowerCase(element.tagName);
    const parentTagName = stringToLowerCase(parent.tagName);
    if (!ALLOWED_NAMESPACES[element.namespaceURI]) {
      return false;
    }
    if (element.namespaceURI === SVG_NAMESPACE) {
      if (parent.namespaceURI === HTML_NAMESPACE) {
        return tagName === "svg";
      }
      if (parent.namespaceURI === MATHML_NAMESPACE) {
        return tagName === "svg" && (parentTagName === "annotation-xml" || MATHML_TEXT_INTEGRATION_POINTS[parentTagName]);
      }
      return Boolean(ALL_SVG_TAGS[tagName]);
    }
    if (element.namespaceURI === MATHML_NAMESPACE) {
      if (parent.namespaceURI === HTML_NAMESPACE) {
        return tagName === "math";
      }
      if (parent.namespaceURI === SVG_NAMESPACE) {
        return tagName === "math" && HTML_INTEGRATION_POINTS[parentTagName];
      }
      return Boolean(ALL_MATHML_TAGS[tagName]);
    }
    if (element.namespaceURI === HTML_NAMESPACE) {
      if (parent.namespaceURI === SVG_NAMESPACE && !HTML_INTEGRATION_POINTS[parentTagName]) {
        return false;
      }
      if (parent.namespaceURI === MATHML_NAMESPACE && !MATHML_TEXT_INTEGRATION_POINTS[parentTagName]) {
        return false;
      }
      return !ALL_MATHML_TAGS[tagName] && (COMMON_SVG_AND_HTML_ELEMENTS[tagName] || !ALL_SVG_TAGS[tagName]);
    }
    if (PARSER_MEDIA_TYPE === "application/xhtml+xml" && ALLOWED_NAMESPACES[element.namespaceURI]) {
      return true;
    }
    return false;
  };
  const _forceRemove = function _forceRemove2(node) {
    arrayPush(DOMPurify.removed, {
      element: node
    });
    try {
      getParentNode(node).removeChild(node);
    } catch (_2) {
      remove(node);
    }
  };
  const _removeAttribute = function _removeAttribute2(name, element) {
    try {
      arrayPush(DOMPurify.removed, {
        attribute: element.getAttributeNode(name),
        from: element
      });
    } catch (_2) {
      arrayPush(DOMPurify.removed, {
        attribute: null,
        from: element
      });
    }
    element.removeAttribute(name);
    if (name === "is") {
      if (RETURN_DOM || RETURN_DOM_FRAGMENT) {
        try {
          _forceRemove(element);
        } catch (_2) {
        }
      } else {
        try {
          element.setAttribute(name, "");
        } catch (_2) {
        }
      }
    }
  };
  const _initDocument = function _initDocument2(dirty) {
    let doc = null;
    let leadingWhitespace = null;
    if (FORCE_BODY) {
      dirty = "<remove></remove>" + dirty;
    } else {
      const matches = stringMatch(dirty, /^[\r\n\t ]+/);
      leadingWhitespace = matches && matches[0];
    }
    if (PARSER_MEDIA_TYPE === "application/xhtml+xml" && NAMESPACE === HTML_NAMESPACE) {
      dirty = '<html xmlns="http://www.w3.org/1999/xhtml"><head></head><body>' + dirty + "</body></html>";
    }
    const dirtyPayload = trustedTypesPolicy ? trustedTypesPolicy.createHTML(dirty) : dirty;
    if (NAMESPACE === HTML_NAMESPACE) {
      try {
        doc = new DOMParser().parseFromString(dirtyPayload, PARSER_MEDIA_TYPE);
      } catch (_2) {
      }
    }
    if (!doc || !doc.documentElement) {
      doc = implementation.createDocument(NAMESPACE, "template", null);
      try {
        doc.documentElement.innerHTML = IS_EMPTY_INPUT ? emptyHTML : dirtyPayload;
      } catch (_2) {
      }
    }
    const body = doc.body || doc.documentElement;
    if (dirty && leadingWhitespace) {
      body.insertBefore(document2.createTextNode(leadingWhitespace), body.childNodes[0] || null);
    }
    if (NAMESPACE === HTML_NAMESPACE) {
      return getElementsByTagName.call(doc, WHOLE_DOCUMENT ? "html" : "body")[0];
    }
    return WHOLE_DOCUMENT ? doc.documentElement : body;
  };
  const _createNodeIterator = function _createNodeIterator2(root) {
    return createNodeIterator.call(
      root.ownerDocument || root,
      root,
      // eslint-disable-next-line no-bitwise
      NodeFilter.SHOW_ELEMENT | NodeFilter.SHOW_COMMENT | NodeFilter.SHOW_TEXT | NodeFilter.SHOW_PROCESSING_INSTRUCTION | NodeFilter.SHOW_CDATA_SECTION,
      null
    );
  };
  const _scrubTemplateExpressions = function _scrubTemplateExpressions2(node) {
    node.normalize();
    const walker = createNodeIterator.call(
      node.ownerDocument || node,
      node,
      // eslint-disable-next-line no-bitwise
      NodeFilter.SHOW_TEXT | NodeFilter.SHOW_COMMENT | NodeFilter.SHOW_CDATA_SECTION | NodeFilter.SHOW_PROCESSING_INSTRUCTION,
      null
    );
    let currentNode = walker.nextNode();
    while (currentNode) {
      let data = currentNode.data;
      arrayForEach([MUSTACHE_EXPR$1, ERB_EXPR$1, TMPLIT_EXPR$1], (expr) => {
        data = stringReplace(data, expr, " ");
      });
      currentNode.data = data;
      currentNode = walker.nextNode();
    }
  };
  const _isClobbered = function _isClobbered2(element) {
    return element instanceof HTMLFormElement && (typeof element.nodeName !== "string" || typeof element.textContent !== "string" || typeof element.removeChild !== "function" || !(element.attributes instanceof NamedNodeMap) || typeof element.removeAttribute !== "function" || typeof element.setAttribute !== "function" || typeof element.namespaceURI !== "string" || typeof element.insertBefore !== "function" || typeof element.hasChildNodes !== "function");
  };
  const _isNode = function _isNode2(value) {
    if (!getNodeType || typeof value !== "object" || value === null) {
      return false;
    }
    try {
      return typeof getNodeType(value) === "number";
    } catch (_2) {
      return false;
    }
  };
  function _executeHooks(hooks2, currentNode, data) {
    arrayForEach(hooks2, (hook) => {
      hook.call(DOMPurify, currentNode, data, CONFIG);
    });
  }
  const _sanitizeElements = function _sanitizeElements2(currentNode) {
    let content = null;
    _executeHooks(hooks.beforeSanitizeElements, currentNode, null);
    if (_isClobbered(currentNode)) {
      _forceRemove(currentNode);
      return true;
    }
    const tagName = transformCaseFunc(currentNode.nodeName);
    _executeHooks(hooks.uponSanitizeElement, currentNode, {
      tagName,
      allowedTags: ALLOWED_TAGS
    });
    if (SAFE_FOR_XML && currentNode.hasChildNodes() && !_isNode(currentNode.firstElementChild) && regExpTest(/<[/\w!]/g, currentNode.innerHTML) && regExpTest(/<[/\w!]/g, currentNode.textContent)) {
      _forceRemove(currentNode);
      return true;
    }
    if (SAFE_FOR_XML && currentNode.namespaceURI === HTML_NAMESPACE && tagName === "style" && _isNode(currentNode.firstElementChild)) {
      _forceRemove(currentNode);
      return true;
    }
    if (currentNode.nodeType === NODE_TYPE.progressingInstruction) {
      _forceRemove(currentNode);
      return true;
    }
    if (SAFE_FOR_XML && currentNode.nodeType === NODE_TYPE.comment && regExpTest(/<[/\w]/g, currentNode.data)) {
      _forceRemove(currentNode);
      return true;
    }
    if (FORBID_TAGS[tagName] || !(EXTRA_ELEMENT_HANDLING.tagCheck instanceof Function && EXTRA_ELEMENT_HANDLING.tagCheck(tagName)) && !ALLOWED_TAGS[tagName]) {
      if (!FORBID_TAGS[tagName] && _isBasicCustomElement(tagName)) {
        if (CUSTOM_ELEMENT_HANDLING.tagNameCheck instanceof RegExp && regExpTest(CUSTOM_ELEMENT_HANDLING.tagNameCheck, tagName)) {
          return false;
        }
        if (CUSTOM_ELEMENT_HANDLING.tagNameCheck instanceof Function && CUSTOM_ELEMENT_HANDLING.tagNameCheck(tagName)) {
          return false;
        }
      }
      if (KEEP_CONTENT && !FORBID_CONTENTS[tagName]) {
        const parentNode = getParentNode(currentNode) || currentNode.parentNode;
        const childNodes = getChildNodes(currentNode) || currentNode.childNodes;
        if (childNodes && parentNode) {
          const childCount = childNodes.length;
          for (let i = childCount - 1; i >= 0; --i) {
            const childClone = cloneNode(childNodes[i], true);
            parentNode.insertBefore(childClone, getNextSibling(currentNode));
          }
        }
      }
      _forceRemove(currentNode);
      return true;
    }
    if (currentNode instanceof Element && !_checkValidNamespace(currentNode)) {
      _forceRemove(currentNode);
      return true;
    }
    if ((tagName === "noscript" || tagName === "noembed" || tagName === "noframes") && regExpTest(/<\/no(script|embed|frames)/i, currentNode.innerHTML)) {
      _forceRemove(currentNode);
      return true;
    }
    if (SAFE_FOR_TEMPLATES && currentNode.nodeType === NODE_TYPE.text) {
      content = currentNode.textContent;
      arrayForEach([MUSTACHE_EXPR$1, ERB_EXPR$1, TMPLIT_EXPR$1], (expr) => {
        content = stringReplace(content, expr, " ");
      });
      if (currentNode.textContent !== content) {
        arrayPush(DOMPurify.removed, {
          element: currentNode.cloneNode()
        });
        currentNode.textContent = content;
      }
    }
    _executeHooks(hooks.afterSanitizeElements, currentNode, null);
    return false;
  };
  const _isValidAttribute = function _isValidAttribute2(lcTag, lcName, value) {
    if (FORBID_ATTR[lcName]) {
      return false;
    }
    if (SANITIZE_DOM && (lcName === "id" || lcName === "name") && (value in document2 || value in formElement)) {
      return false;
    }
    const nameIsPermitted = ALLOWED_ATTR[lcName] || EXTRA_ELEMENT_HANDLING.attributeCheck instanceof Function && EXTRA_ELEMENT_HANDLING.attributeCheck(lcName, lcTag);
    if (ALLOW_DATA_ATTR && !FORBID_ATTR[lcName] && regExpTest(DATA_ATTR$1, lcName)) ;
    else if (ALLOW_ARIA_ATTR && regExpTest(ARIA_ATTR$1, lcName)) ;
    else if (!nameIsPermitted || FORBID_ATTR[lcName]) {
      if (
        // First condition does a very basic check if a) it's basically a valid custom element tagname AND
        // b) if the tagName passes whatever the user has configured for CUSTOM_ELEMENT_HANDLING.tagNameCheck
        // and c) if the attribute name passes whatever the user has configured for CUSTOM_ELEMENT_HANDLING.attributeNameCheck
        _isBasicCustomElement(lcTag) && (CUSTOM_ELEMENT_HANDLING.tagNameCheck instanceof RegExp && regExpTest(CUSTOM_ELEMENT_HANDLING.tagNameCheck, lcTag) || CUSTOM_ELEMENT_HANDLING.tagNameCheck instanceof Function && CUSTOM_ELEMENT_HANDLING.tagNameCheck(lcTag)) && (CUSTOM_ELEMENT_HANDLING.attributeNameCheck instanceof RegExp && regExpTest(CUSTOM_ELEMENT_HANDLING.attributeNameCheck, lcName) || CUSTOM_ELEMENT_HANDLING.attributeNameCheck instanceof Function && CUSTOM_ELEMENT_HANDLING.attributeNameCheck(lcName, lcTag)) || // Alternative, second condition checks if it's an `is`-attribute, AND
        // the value passes whatever the user has configured for CUSTOM_ELEMENT_HANDLING.tagNameCheck
        lcName === "is" && CUSTOM_ELEMENT_HANDLING.allowCustomizedBuiltInElements && (CUSTOM_ELEMENT_HANDLING.tagNameCheck instanceof RegExp && regExpTest(CUSTOM_ELEMENT_HANDLING.tagNameCheck, value) || CUSTOM_ELEMENT_HANDLING.tagNameCheck instanceof Function && CUSTOM_ELEMENT_HANDLING.tagNameCheck(value))
      ) ;
      else {
        return false;
      }
    } else if (URI_SAFE_ATTRIBUTES[lcName]) ;
    else if (regExpTest(IS_ALLOWED_URI$1, stringReplace(value, ATTR_WHITESPACE$1, ""))) ;
    else if ((lcName === "src" || lcName === "xlink:href" || lcName === "href") && lcTag !== "script" && stringIndexOf(value, "data:") === 0 && DATA_URI_TAGS[lcTag]) ;
    else if (ALLOW_UNKNOWN_PROTOCOLS && !regExpTest(IS_SCRIPT_OR_DATA$1, stringReplace(value, ATTR_WHITESPACE$1, ""))) ;
    else if (value) {
      return false;
    } else ;
    return true;
  };
  const RESERVED_CUSTOM_ELEMENT_NAMES = addToSet({}, ["annotation-xml", "color-profile", "font-face", "font-face-format", "font-face-name", "font-face-src", "font-face-uri", "missing-glyph"]);
  const _isBasicCustomElement = function _isBasicCustomElement2(tagName) {
    return !RESERVED_CUSTOM_ELEMENT_NAMES[stringToLowerCase(tagName)] && regExpTest(CUSTOM_ELEMENT$1, tagName);
  };
  const _sanitizeAttributes = function _sanitizeAttributes2(currentNode) {
    _executeHooks(hooks.beforeSanitizeAttributes, currentNode, null);
    const attributes = currentNode.attributes;
    if (!attributes || _isClobbered(currentNode)) {
      return;
    }
    const hookEvent = {
      attrName: "",
      attrValue: "",
      keepAttr: true,
      allowedAttributes: ALLOWED_ATTR,
      forceKeepAttr: void 0
    };
    let l = attributes.length;
    while (l--) {
      const attr = attributes[l];
      const name = attr.name, namespaceURI = attr.namespaceURI, attrValue = attr.value;
      const lcName = transformCaseFunc(name);
      const initValue = attrValue;
      let value = name === "value" ? initValue : stringTrim(initValue);
      hookEvent.attrName = lcName;
      hookEvent.attrValue = value;
      hookEvent.keepAttr = true;
      hookEvent.forceKeepAttr = void 0;
      _executeHooks(hooks.uponSanitizeAttribute, currentNode, hookEvent);
      value = hookEvent.attrValue;
      if (SANITIZE_NAMED_PROPS && (lcName === "id" || lcName === "name") && stringIndexOf(value, SANITIZE_NAMED_PROPS_PREFIX) !== 0) {
        _removeAttribute(name, currentNode);
        value = SANITIZE_NAMED_PROPS_PREFIX + value;
      }
      if (SAFE_FOR_XML && regExpTest(/((--!?|])>)|<\/(style|script|title|xmp|textarea|noscript|iframe|noembed|noframes)/i, value)) {
        _removeAttribute(name, currentNode);
        continue;
      }
      if (lcName === "attributename" && stringMatch(value, "href")) {
        _removeAttribute(name, currentNode);
        continue;
      }
      if (hookEvent.forceKeepAttr) {
        continue;
      }
      if (!hookEvent.keepAttr) {
        _removeAttribute(name, currentNode);
        continue;
      }
      if (!ALLOW_SELF_CLOSE_IN_ATTR && regExpTest(/\/>/i, value)) {
        _removeAttribute(name, currentNode);
        continue;
      }
      if (SAFE_FOR_TEMPLATES) {
        arrayForEach([MUSTACHE_EXPR$1, ERB_EXPR$1, TMPLIT_EXPR$1], (expr) => {
          value = stringReplace(value, expr, " ");
        });
      }
      const lcTag = transformCaseFunc(currentNode.nodeName);
      if (!_isValidAttribute(lcTag, lcName, value)) {
        _removeAttribute(name, currentNode);
        continue;
      }
      if (trustedTypesPolicy && typeof trustedTypes === "object" && typeof trustedTypes.getAttributeType === "function") {
        if (namespaceURI) ;
        else {
          switch (trustedTypes.getAttributeType(lcTag, lcName)) {
            case "TrustedHTML": {
              value = trustedTypesPolicy.createHTML(value);
              break;
            }
            case "TrustedScriptURL": {
              value = trustedTypesPolicy.createScriptURL(value);
              break;
            }
          }
        }
      }
      if (value !== initValue) {
        try {
          if (namespaceURI) {
            currentNode.setAttributeNS(namespaceURI, name, value);
          } else {
            currentNode.setAttribute(name, value);
          }
          if (_isClobbered(currentNode)) {
            _forceRemove(currentNode);
          } else {
            arrayPop(DOMPurify.removed);
          }
        } catch (_2) {
          _removeAttribute(name, currentNode);
        }
      }
    }
    _executeHooks(hooks.afterSanitizeAttributes, currentNode, null);
  };
  const _sanitizeShadowDOM2 = function _sanitizeShadowDOM(fragment) {
    let shadowNode = null;
    const shadowIterator = _createNodeIterator(fragment);
    _executeHooks(hooks.beforeSanitizeShadowDOM, fragment, null);
    while (shadowNode = shadowIterator.nextNode()) {
      _executeHooks(hooks.uponSanitizeShadowNode, shadowNode, null);
      _sanitizeElements(shadowNode);
      _sanitizeAttributes(shadowNode);
      if (shadowNode.content instanceof DocumentFragment) {
        _sanitizeShadowDOM2(shadowNode.content);
      }
    }
    _executeHooks(hooks.afterSanitizeShadowDOM, fragment, null);
  };
  const _sanitizeAttachedShadowRoots2 = function _sanitizeAttachedShadowRoots(root) {
    if (root.nodeType === NODE_TYPE.element && root.shadowRoot instanceof DocumentFragment) {
      const sr = root.shadowRoot;
      _sanitizeAttachedShadowRoots2(sr);
      _sanitizeShadowDOM2(sr);
    }
    const childNodes = root.childNodes;
    if (!childNodes) {
      return;
    }
    const snapshot = [];
    arrayForEach(childNodes, (child) => {
      arrayPush(snapshot, child);
    });
    for (const child of snapshot) {
      _sanitizeAttachedShadowRoots2(child);
    }
  };
  DOMPurify.sanitize = function(dirty) {
    let cfg = arguments.length > 1 && arguments[1] !== void 0 ? arguments[1] : {};
    let body = null;
    let importedNode = null;
    let currentNode = null;
    let returnNode = null;
    IS_EMPTY_INPUT = !dirty;
    if (IS_EMPTY_INPUT) {
      dirty = "<!-->";
    }
    if (typeof dirty !== "string" && !_isNode(dirty)) {
      dirty = stringifyValue(dirty);
      if (typeof dirty !== "string") {
        throw typeErrorCreate("dirty is not a string, aborting");
      }
    }
    if (!DOMPurify.isSupported) {
      return dirty;
    }
    if (!SET_CONFIG) {
      _parseConfig(cfg);
    }
    DOMPurify.removed = [];
    if (typeof dirty === "string") {
      IN_PLACE = false;
    }
    if (IN_PLACE) {
      const nn = dirty.nodeName;
      if (typeof nn === "string") {
        const tagName = transformCaseFunc(nn);
        if (!ALLOWED_TAGS[tagName] || FORBID_TAGS[tagName]) {
          throw typeErrorCreate("root node is forbidden and cannot be sanitized in-place");
        }
      }
      _sanitizeAttachedShadowRoots2(dirty);
    } else if (_isNode(dirty)) {
      body = _initDocument("<!---->");
      importedNode = body.ownerDocument.importNode(dirty, true);
      if (importedNode.nodeType === NODE_TYPE.element && importedNode.nodeName === "BODY") {
        body = importedNode;
      } else if (importedNode.nodeName === "HTML") {
        body = importedNode;
      } else {
        body.appendChild(importedNode);
      }
      _sanitizeAttachedShadowRoots2(importedNode);
    } else {
      if (!RETURN_DOM && !SAFE_FOR_TEMPLATES && !WHOLE_DOCUMENT && // eslint-disable-next-line unicorn/prefer-includes
      dirty.indexOf("<") === -1) {
        return trustedTypesPolicy && RETURN_TRUSTED_TYPE ? trustedTypesPolicy.createHTML(dirty) : dirty;
      }
      body = _initDocument(dirty);
      if (!body) {
        return RETURN_DOM ? null : RETURN_TRUSTED_TYPE ? emptyHTML : "";
      }
    }
    if (body && FORCE_BODY) {
      _forceRemove(body.firstChild);
    }
    const nodeIterator = _createNodeIterator(IN_PLACE ? dirty : body);
    while (currentNode = nodeIterator.nextNode()) {
      _sanitizeElements(currentNode);
      _sanitizeAttributes(currentNode);
      if (currentNode.content instanceof DocumentFragment) {
        _sanitizeShadowDOM2(currentNode.content);
      }
    }
    if (IN_PLACE) {
      if (SAFE_FOR_TEMPLATES) {
        _scrubTemplateExpressions(dirty);
      }
      return dirty;
    }
    if (RETURN_DOM) {
      if (SAFE_FOR_TEMPLATES) {
        _scrubTemplateExpressions(body);
      }
      if (RETURN_DOM_FRAGMENT) {
        returnNode = createDocumentFragment.call(body.ownerDocument);
        while (body.firstChild) {
          returnNode.appendChild(body.firstChild);
        }
      } else {
        returnNode = body;
      }
      if (ALLOWED_ATTR.shadowroot || ALLOWED_ATTR.shadowrootmode) {
        returnNode = importNode.call(originalDocument, returnNode, true);
      }
      return returnNode;
    }
    let serializedHTML = WHOLE_DOCUMENT ? body.outerHTML : body.innerHTML;
    if (WHOLE_DOCUMENT && ALLOWED_TAGS["!doctype"] && body.ownerDocument && body.ownerDocument.doctype && body.ownerDocument.doctype.name && regExpTest(DOCTYPE_NAME, body.ownerDocument.doctype.name)) {
      serializedHTML = "<!DOCTYPE " + body.ownerDocument.doctype.name + ">\n" + serializedHTML;
    }
    if (SAFE_FOR_TEMPLATES) {
      arrayForEach([MUSTACHE_EXPR$1, ERB_EXPR$1, TMPLIT_EXPR$1], (expr) => {
        serializedHTML = stringReplace(serializedHTML, expr, " ");
      });
    }
    return trustedTypesPolicy && RETURN_TRUSTED_TYPE ? trustedTypesPolicy.createHTML(serializedHTML) : serializedHTML;
  };
  DOMPurify.setConfig = function() {
    let cfg = arguments.length > 0 && arguments[0] !== void 0 ? arguments[0] : {};
    _parseConfig(cfg);
    SET_CONFIG = true;
  };
  DOMPurify.clearConfig = function() {
    CONFIG = null;
    SET_CONFIG = false;
  };
  DOMPurify.isValidAttribute = function(tag, attr, value) {
    if (!CONFIG) {
      _parseConfig({});
    }
    const lcTag = transformCaseFunc(tag);
    const lcName = transformCaseFunc(attr);
    return _isValidAttribute(lcTag, lcName, value);
  };
  DOMPurify.addHook = function(entryPoint, hookFunction) {
    if (typeof hookFunction !== "function") {
      return;
    }
    arrayPush(hooks[entryPoint], hookFunction);
  };
  DOMPurify.removeHook = function(entryPoint, hookFunction) {
    if (hookFunction !== void 0) {
      const index = arrayLastIndexOf(hooks[entryPoint], hookFunction);
      return index === -1 ? void 0 : arraySplice(hooks[entryPoint], index, 1)[0];
    }
    return arrayPop(hooks[entryPoint]);
  };
  DOMPurify.removeHooks = function(entryPoint) {
    hooks[entryPoint] = [];
  };
  DOMPurify.removeAllHooks = function() {
    hooks = _createHooksMap();
  };
  return DOMPurify;
}
var purify = createDOMPurify();
const FAVORITE_PROMPT_SLOTS = 3;
function parsePageContext(url, title) {
  try {
    const u3 = new URL(url);
    return {
      hostname: u3.hostname.replace(/^www\./, ""),
      favicon: `https://www.google.com/s2/favicons?domain=${encodeURIComponent(u3.hostname)}&sz=32`
    };
  } catch {
    return { hostname: title || "Unknown page", favicon: "" };
  }
}
function renderMarkdown$1(raw) {
  const html2 = k(raw);
  return purify.sanitize(html2);
}
const SummarizeSkeleton = () => /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "skeleton-summarize", "aria-busy": "true", "aria-label": "Loading page details", children: [
  /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "skeleton-chip skeleton-animate", children: [
    /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-circle" }),
    /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "skeleton-lines", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "60%", height: 12 } }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "85%", height: 10 } })
    ] })
  ] }),
  /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "skeleton-chip skeleton-animate", style: { gap: 8 }, children: [
    /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "30%", height: 10 } }),
    /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "30%", height: 10 } }),
    /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "30%", height: 10 } })
  ] }),
  /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block skeleton-animate", style: { height: 44, borderRadius: 999 } })
] });
const SummarizeTab = ({ apiKey, onSummarySaved }) => {
  const [state, setState] = reactExports.useState({
    currentUrl: "Loading...",
    currentTitle: "",
    prompts: [],
    selectedPrompt: "default",
    isLoading: true,
    isSummarizing: false,
    summary: null,
    error: "",
    pageAccessible: false,
    domainWarning: void 0,
    autoSaved: false
  });
  const showToast = useToast();
  reactExports.useEffect(() => {
    initializeTab();
    const messageListener = (message) => {
      if (message.type === "CONTEXT_MENU_SUMMARY" && message.data) {
        handleContextMenuSummary(message.data);
      }
    };
    chrome.runtime.onMessage.addListener(messageListener);
    return () => chrome.runtime.onMessage.removeListener(messageListener);
  }, [apiKey]);
  const handleContextMenuSummary = (data) => {
    setState((prev) => ({
      ...prev,
      summary: {
        summary: data.summary,
        tokensUsed: data.tokensUsed,
        wordCount: data.wordCount,
        processingTime: 0
      },
      currentUrl: data.url,
      currentTitle: `[Selected Text] ${data.title}`,
      isSummarizing: false,
      error: "",
      autoSaved: false
    }));
  };
  const initializeTab = async () => {
    setState((prev) => ({ ...prev, isLoading: true, error: "" }));
    try {
      const [pageAccessible, tab, lastPrompt, cachedPrompts] = await Promise.all([
        ApiService.isPageAccessible(),
        chrome.tabs.query({ active: true, currentWindow: true }).then((tabs) => tabs[0]),
        StorageService.getLastSelectedPrompt(),
        StorageService.getCachedPrompts()
      ]);
      const currentUrl = tab?.url || "Unknown";
      const currentTitle = tab?.title || "Unknown";
      let domainWarning;
      try {
        const hostname2 = new URL(currentUrl).hostname.toLowerCase();
        domainWarning = getDomainWarning(hostname2) || void 0;
      } catch {
      }
      if (cachedPrompts && Array.isArray(cachedPrompts) && cachedPrompts.length > 0) {
        const validSelected = lastPrompt && cachedPrompts.some((p) => p.id === lastPrompt) ? lastPrompt : "default";
        setState((prev) => ({
          ...prev,
          currentUrl,
          currentTitle,
          prompts: cachedPrompts,
          selectedPrompt: validSelected,
          pageAccessible,
          domainWarning,
          isLoading: false
        }));
        ApiService.getPrompts(apiKey, false).then((fresh) => setState((prev) => ({ ...prev, prompts: fresh }))).catch((err) => console.warn("Background prompt refresh failed:", err));
      } else {
        const prompts = await ApiService.getPrompts(apiKey, true);
        const validSelected = lastPrompt && prompts.some((p) => p.id === lastPrompt) ? lastPrompt : "default";
        setState((prev) => ({
          ...prev,
          currentUrl,
          currentTitle,
          prompts,
          selectedPrompt: validSelected,
          pageAccessible,
          domainWarning,
          isLoading: false
        }));
      }
    } catch {
      setState((prev) => ({ ...prev, error: "Failed to initialize tab", isLoading: false }));
    }
  };
  const getDomainWarning = (hostname2) => {
    const limited = [
      { patterns: /(^|\.)google\.com$/i, message: "Google pages often restrict direct content extraction; summarization may be limited." },
      { patterns: /(^|\.)facebook\.com$/i, message: "Facebook is highly dynamic; extracted text may be incomplete." },
      { patterns: /(^|\.)instagram\.com$/i, message: "Instagram content is mostly images; textual summary may be minimal." },
      { patterns: /(^|\.)twitter\.com$/i, message: "Twitter timeline is dynamic; only visible loaded tweets may be summarized." },
      { patterns: /(^|\.)x\.com$/i, message: "X (Twitter) timeline is dynamic; only visible loaded posts may be summarized." },
      { patterns: /(^|\.)linkedin\.com$/i, message: "LinkedIn feeds use virtual scrolling; extraction may exclude off‑screen content." },
      { patterns: /(^|\.)web\.whatsapp\.com$/i, message: "WhatsApp Web is a protected app shell; message text may not be accessible." },
      { patterns: /(^|\.)tiktok\.com$/i, message: "TikTok content is video-centric; textual extraction is limited." },
      { patterns: /(^|\.)slack\.com$/i, message: "Slack web app content is dynamic and may not expose full history for extraction." }
    ];
    for (const entry of limited) {
      if (entry.patterns.test(hostname2)) return entry.message;
    }
    return null;
  };
  const handleSummarize = async () => {
    if (!state.pageAccessible) {
      setState((prev) => ({
        ...prev,
        error: "Cannot summarize this type of page. Open a regular https:// article or page and try again."
      }));
      return;
    }
    setState((prev) => ({ ...prev, isSummarizing: true, error: "", summary: null, autoSaved: false }));
    try {
      const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
      const currentUrl = tab?.url || state.currentUrl;
      const currentTitle = tab?.title || state.currentTitle;
      const tabId = tab?.id;
      if (!currentUrl || !/^https?:\/\//i.test(currentUrl)) {
        throw new Error("Unable to access a valid web page URL to summarize");
      }
      const selectedPromptObj2 = state.prompts.find((p) => p.id === state.selectedPrompt);
      const promptText = selectedPromptObj2?.prompt || "Provide a concise summary of the main points in this content.";
      const isYouTube = /(^|\.)youtube\.com\/watch/i.test(currentUrl) || /(^|\.)youtu\.be\//i.test(currentUrl);
      let summary;
      const startTime = Date.now();
      const canonicalUrl = ApiService.canonicalizeUrl(currentUrl);
      if (isYouTube && tabId) {
        const response = await chrome.runtime.sendMessage({
          type: "SUMMARIZE_YOUTUBE_VIDEO",
          data: { url: currentUrl, title: currentTitle, prompt: promptText }
        });
        if (response.error) throw new Error(response.error);
        summary = { summary: response.summary, tokensUsed: response.tokensUsed, wordCount: response.wordCount, processingTime: 0 };
      } else {
        summary = await ApiService.summarizeContent(apiKey, { url: canonicalUrl, prompt: promptText, skipCache: false });
      }
      const processingTime = Date.now() - startTime;
      await StorageService.updateUserStats({
        totalSummaries: 1,
        wordsProcessed: summary.wordCount,
        tokensUsed: summary.tokensUsed
      });
      let autoSaved = false;
      try {
        await StorageService.saveSummary({
          title: currentTitle || "Untitled Page",
          url: currentUrl || "",
          summary: summary.summary,
          prompt: selectedPromptObj2?.prompt || "Default prompt",
          tokensUsed: summary.tokensUsed,
          wordCount: summary.wordCount
        });
        autoSaved = true;
        onSummarySaved?.();
      } catch (saveError) {
        console.warn("Failed to auto-save summary:", saveError);
      }
      setState((prev) => ({
        ...prev,
        currentUrl,
        currentTitle,
        sentUrl: canonicalUrl,
        summary: { ...summary, processingTime },
        isSummarizing: false,
        autoSaved
      }));
    } catch (error) {
      setState((prev) => ({
        ...prev,
        error: error instanceof Error ? error.message : "Failed to summarize content",
        isSummarizing: false
      }));
    }
  };
  const selectPrompt = (promptId) => {
    setState((prev) => ({ ...prev, selectedPrompt: promptId }));
    StorageService.saveLastSelectedPrompt(promptId).catch(
      (err) => console.warn("Could not persist selected prompt", err)
    );
  };
  const handleCopySummary = async (summary) => {
    try {
      await navigator.clipboard.writeText(summary);
      showToast({ message: "Copied to clipboard!", type: "success" });
    } catch {
      const ta = document.createElement("textarea");
      ta.value = summary;
      document.body.appendChild(ta);
      ta.select();
      document.execCommand("copy");
      document.body.removeChild(ta);
      showToast({ message: "Copied to clipboard!", type: "success" });
    }
  };
  const handleShareSummary = async (summary) => {
    const shareData = {
      title: "AI Summary",
      text: `Summary of "${state.currentTitle}":

${summary}`,
      url: state.currentUrl
    };
    try {
      if (navigator.share) {
        await navigator.share(shareData);
      } else {
        await navigator.clipboard.writeText(`${shareData.text}

Source: ${shareData.url}`);
        showToast({ message: "Summary copied for sharing!", type: "success" });
      }
    } catch (e) {
      console.error("Failed to share:", e);
    }
  };
  const handleOpenInSidebar = async () => {
    if (!state.summary) return;
    try {
      const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
      if (!tab.id) return;
      try {
        await chrome.scripting.executeScript({ target: { tabId: tab.id }, files: ["marked.min.js"] });
      } catch {
      }
      try {
        await chrome.scripting.executeScript({ target: { tabId: tab.id }, files: ["content-sidebar.js"] });
      } catch {
      }
      try {
        await chrome.scripting.insertCSS({ target: { tabId: tab.id }, files: ["content-sidebar.css"] });
      } catch {
      }
      await chrome.tabs.sendMessage(tab.id, {
        type: "SHOW_SIDEBAR_SUMMARY",
        data: { summary: state.summary.summary, selectedText: "", tokensUsed: state.summary.tokensUsed, wordCount: state.summary.wordCount, url: state.currentUrl, title: state.currentTitle }
      });
      window.close();
    } catch {
      setState((prev) => ({ ...prev, error: "Failed to open sidebar. Try refreshing the page and summarizing again." }));
    }
  };
  const copyPageUrl = async () => {
    if (!state.currentUrl || state.currentUrl === "Loading...") return;
    try {
      await navigator.clipboard.writeText(state.currentUrl);
      showToast({ message: "Page link copied", type: "success" });
    } catch {
    }
  };
  const openCurrentPage = () => {
    if (state.currentUrl && /^https?:\/\//i.test(state.currentUrl)) {
      chrome.tabs.create({ url: state.currentUrl });
    }
  };
  if (state.isLoading) {
    return /* @__PURE__ */ jsxRuntimeExports.jsx("div", { id: "summarize-tab", className: "tab-pane active", children: /* @__PURE__ */ jsxRuntimeExports.jsx(SummarizeSkeleton, {}) });
  }
  const { hostname, favicon } = parsePageContext(state.currentUrl, state.currentTitle);
  const favoritePrompts = state.prompts.slice(0, FAVORITE_PROMPT_SLOTS);
  const morePrompts = state.prompts.slice(FAVORITE_PROMPT_SLOTS);
  const selectedPromptObj = state.prompts.find((p) => p.id === state.selectedPrompt);
  const containerClass = `tab-pane active ${state.summary ? "summary-top-layout" : ""}`;
  return /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "summarize-tab", className: containerClass, children: [
    state.isSummarizing && !state.summary && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "summary-result", className: "result-section skeleton-wrapper skeleton-animate", "aria-busy": "true", "aria-live": "polite", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "result-header", children: /* @__PURE__ */ jsxRuntimeExports.jsx("h3", { className: "text-muted-heading", children: "Generating Summary…" }) }),
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "summary-text", style: { maxHeight: "none" }, children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "92%" } }),
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "87%" } }),
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "83%" } }),
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "58%" } })
      ] })
    ] }),
    state.summary && !state.isSummarizing && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "summary-result", className: "result-section", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "result-header", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("h3", { children: "Summary" }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "result-actions", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("button", { className: "action-btn sidebar-btn", onClick: handleOpenInSidebar, title: "Open in sidebar", type: "button", children: /* @__PURE__ */ jsxRuntimeExports.jsx(PanelRight, { size: 14, strokeWidth: 2 }) }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("button", { className: "action-btn copy-btn", onClick: () => handleCopySummary(state.summary.summary), title: "Copy to clipboard", type: "button", children: /* @__PURE__ */ jsxRuntimeExports.jsx(ClipboardCopy, { size: 14, strokeWidth: 2 }) }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("button", { className: "action-btn share-btn", onClick: () => handleShareSummary(state.summary.summary), title: "Share summary", type: "button", children: /* @__PURE__ */ jsxRuntimeExports.jsx(Share2, { size: 14, strokeWidth: 2 }) })
        ] })
      ] }),
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "summary-meta-strip", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "summary-meta-item", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx(Hash, { size: 11, strokeWidth: 2.5 }),
          state.summary.wordCount.toLocaleString(),
          " words"
        ] }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "summary-meta-item", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx(Zap, { size: 11, strokeWidth: 2.5 }),
          state.summary.tokensUsed.toLocaleString(),
          " tokens"
        ] }),
        state.summary.processingTime > 0 && /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "summary-meta-item", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx(Clock, { size: 11, strokeWidth: 2.5 }),
          (state.summary.processingTime / 1e3).toFixed(1),
          "s"
        ] }),
        state.autoSaved && /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "summary-meta-item meta-saved", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx(CircleCheck, { size: 11, strokeWidth: 2.5 }),
          "Saved automatically"
        ] })
      ] }),
      /* @__PURE__ */ jsxRuntimeExports.jsx(
        "div",
        {
          id: "summary-content",
          className: "summary-text markdown-content",
          dangerouslySetInnerHTML: { __html: renderMarkdown$1(state.summary.summary) }
        }
      )
    ] }),
    !state.summary && !state.isSummarizing && state.pageAccessible && /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "summarize-empty-hint", role: "note", children: "Choose a prompt below, then summarize this page. You can also right‑click selected text on any page." }),
    /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "current-page", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsx("label", { children: "Current Page" }),
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "current-url", className: "url-display page-context-chip", children: [
        favicon ? /* @__PURE__ */ jsxRuntimeExports.jsx("img", { src: favicon, alt: "", className: "page-favicon", width: 26, height: 26 }) : /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "page-favicon", "aria-hidden": true }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "page-context-text", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "page-hostname", children: hostname }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "page-title-trunc", children: state.currentTitle || "Untitled" })
        ] }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "page-context-actions", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("button", { type: "button", className: "icon-btn-sm", onClick: copyPageUrl, title: "Copy page URL", children: /* @__PURE__ */ jsxRuntimeExports.jsx(Link2, { size: 13 }) }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("button", { type: "button", className: "icon-btn-sm", onClick: openCurrentPage, title: "Open page in new tab", children: /* @__PURE__ */ jsxRuntimeExports.jsx(ExternalLink, { size: 13 }) })
        ] })
      ] }),
      state.sentUrl && state.sentUrl !== state.currentUrl && /* @__PURE__ */ jsxRuntimeExports.jsxs("details", { className: "page-details", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("summary", { children: "API URL details" }),
        "Sent to API: ",
        state.sentUrl
      ] }),
      !state.pageAccessible && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "error-message show", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx(TriangleAlert, { size: 13, style: { display: "inline", marginRight: 6, verticalAlign: "middle" } }),
        "This page cannot be summarized. Navigate to a regular https:// page.",
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "callout-actions", children: /* @__PURE__ */ jsxRuntimeExports.jsxs("button", { type: "button", className: "secondary-btn", onClick: initializeTab, children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx(RotateCcw, { size: 12, style: { display: "inline", marginRight: 4, verticalAlign: "middle" } }),
          "Retry detection"
        ] }) })
      ] }),
      state.pageAccessible && state.domainWarning && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "warning-message show", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx(TriangleAlert, { size: 13, style: { display: "inline", marginRight: 6, verticalAlign: "middle" } }),
        state.domainWarning
      ] })
    ] }),
    /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "prompt-section", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsx("label", { children: "Choose Prompt" }),
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "prompt-picker", children: [
        favoritePrompts.length > 0 && /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "prompt-segments", role: "group", "aria-label": "Favorite prompts", children: favoritePrompts.map((prompt) => /* @__PURE__ */ jsxRuntimeExports.jsx(
          "button",
          {
            type: "button",
            className: `prompt-segment ${state.selectedPrompt === prompt.id ? "active" : ""}`,
            onClick: () => selectPrompt(prompt.id),
            disabled: state.isSummarizing,
            title: prompt.description,
            children: prompt.name
          },
          prompt.id
        )) }),
        morePrompts.length > 0 && /* @__PURE__ */ jsxRuntimeExports.jsxs(
          "select",
          {
            id: "prompt-select",
            className: "prompt-more-select",
            value: morePrompts.some((p) => p.id === state.selectedPrompt) ? state.selectedPrompt : "",
            onChange: (e) => e.target.value && selectPrompt(e.target.value),
            disabled: state.isSummarizing,
            "aria-label": "More prompts",
            children: [
              /* @__PURE__ */ jsxRuntimeExports.jsx("option", { value: "", disabled: true, children: "More prompts…" }),
              morePrompts.map((prompt) => /* @__PURE__ */ jsxRuntimeExports.jsx("option", { value: prompt.id, children: prompt.name }, prompt.id))
            ]
          }
        ),
        selectedPromptObj?.description && /* @__PURE__ */ jsxRuntimeExports.jsx("p", { className: "prompt-description", children: selectedPromptObj.description })
      ] })
    ] }),
    /* @__PURE__ */ jsxRuntimeExports.jsxs(
      "button",
      {
        id: "summarize-btn",
        className: `primary-btn full-width ${state.isSummarizing ? "loading" : ""}`,
        onClick: handleSummarize,
        disabled: state.isSummarizing || !state.pageAccessible,
        type: "button",
        children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: `btn-text ${state.isSummarizing ? "hidden" : ""}`, children: "Summarize This Page" }),
          /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: `btn-loading ${state.isSummarizing ? "" : "hidden"}`, children: [
            /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "loading-dots", children: [
              /* @__PURE__ */ jsxRuntimeExports.jsx("span", {}),
              /* @__PURE__ */ jsxRuntimeExports.jsx("span", {}),
              /* @__PURE__ */ jsxRuntimeExports.jsx("span", {})
            ] }),
            "Summarizing…"
          ] })
        ]
      }
    ),
    !state.pageAccessible && !state.isSummarizing && /* @__PURE__ */ jsxRuntimeExports.jsxs("p", { className: "summarize-disabled-note", role: "note", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsx(Info, { size: 12, strokeWidth: 2 }),
      "Navigate to a regular web page or article to enable summarization."
    ] }),
    state.error && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "summary-error", className: "error-message show", role: "alert", children: [
      state.error,
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "callout-actions", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("button", { type: "button", className: "secondary-btn", onClick: handleSummarize, disabled: state.isSummarizing, children: "Retry" }),
        /* @__PURE__ */ jsxRuntimeExports.jsx(
          "a",
          {
            className: "callout-link secondary-btn",
            href: "https://www.get-tldr.com",
            target: "_blank",
            rel: "noopener noreferrer",
            children: "Help"
          }
        )
      ] })
    ] })
  ] });
};
const UsageTab = ({ apiKey }) => {
  const [state, setState] = reactExports.useState({
    isLoading: true,
    error: "",
    usageData: null,
    localStats: null,
    lastRefresh: "",
    localStatsDate: ""
  });
  reactExports.useEffect(() => {
    loadUsageData();
  }, [apiKey]);
  const loadUsageData = async () => {
    setState((prev) => ({ ...prev, isLoading: true, error: "" }));
    try {
      const [usageData, localStats] = await Promise.all([
        ApiService.getUsageData(apiKey),
        StorageService.getUserStats()
      ]);
      await StorageService.saveLastUsageCheck();
      const localStatsDate = localStats?.lastUpdated ? formatDate(localStats.lastUpdated) : "";
      setState((prev) => ({
        ...prev,
        usageData,
        localStats,
        lastRefresh: (/* @__PURE__ */ new Date()).toLocaleTimeString([], { hour: "2-digit", minute: "2-digit" }),
        localStatsDate,
        isLoading: false
      }));
    } catch (error) {
      setState((prev) => ({
        ...prev,
        error: error instanceof Error ? error.message : "Failed to load usage data",
        isLoading: false
      }));
    }
  };
  const calculateUsagePercentage = () => {
    if (!state.usageData || state.usageData.monthlyLimit <= 0) return 0;
    return Math.min(state.usageData.currentUsage / state.usageData.monthlyLimit * 100, 100);
  };
  const getUsageLevelClass = () => {
    const pct2 = calculateUsagePercentage();
    if (pct2 >= 90) return "usage-high";
    if (pct2 >= 75) return "usage-mid";
    return "usage-low";
  };
  const formatNumber = (num) => num.toLocaleString();
  const formatDate = (dateString) => {
    try {
      return new Date(dateString).toLocaleDateString([], { month: "short", day: "numeric" });
    } catch {
      return "Unknown";
    }
  };
  const getRemainingDays = () => {
    if (!state.usageData?.resetDate) return 0;
    try {
      const diff = Math.ceil((new Date(state.usageData.resetDate).getTime() - Date.now()) / 864e5);
      return Math.max(0, diff);
    } catch {
      return 0;
    }
  };
  const pct = calculateUsagePercentage();
  const hasLimit = state.usageData && state.usageData.monthlyLimit > 0;
  const remaining = hasLimit ? Math.max(0, state.usageData.monthlyLimit - state.usageData.currentUsage) : 0;
  if (state.isLoading) {
    return /* @__PURE__ */ jsxRuntimeExports.jsx("div", { id: "usage-tab", className: "tab-pane active", children: /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "usage-stats", children: /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "skeleton-card skeleton-animate usage-skeleton", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "50%", height: 15, marginBottom: 18 } }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "100%", height: 8, marginBottom: 12 } }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "60%", height: 18, margin: "0 auto 12px" } })
    ] }) }) });
  }
  return /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "usage-tab", className: "tab-pane active", children: [
    /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "usage-stats", children: [
      state.usageData && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "stat-card", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsxs("h3", { children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx(TrendingUp, { size: 16, style: { display: "inline", marginRight: 6, verticalAlign: "middle" } }),
          "Monthly Usage"
        ] }),
        hasLimit && /* @__PURE__ */ jsxRuntimeExports.jsxs(jsxRuntimeExports.Fragment, { children: [
          /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "usage-ring-wrap", children: [
            /* @__PURE__ */ jsxRuntimeExports.jsx(
              "div",
              {
                className: `usage-ring ${getUsageLevelClass()}`,
                style: {
                  ["--usage-pct"]: String(pct),
                  ["--ring-color"]: pct >= 90 ? "var(--usage-high)" : pct >= 75 ? "var(--usage-mid)" : "var(--usage-low)"
                },
                role: "img",
                "aria-label": `${Math.round(pct)} percent of monthly limit used`,
                children: /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "usage-ring-label", children: [
                  Math.round(pct),
                  "%"
                ] })
              }
            ),
            /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "usage-ring-caption", children: [
              /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "usage-remaining", children: [
                formatNumber(remaining),
                " summaries left"
              ] }),
              /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "usage-sub", children: [
                formatNumber(state.usageData.currentUsage),
                " / ",
                formatNumber(state.usageData.monthlyLimit),
                " used · Resets in ",
                getRemainingDays(),
                "d"
              ] })
            ] })
          ] }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "usage-bar", children: /* @__PURE__ */ jsxRuntimeExports.jsx(
            "div",
            {
              id: "usage-progress",
              className: `progress-fill ${getUsageLevelClass()}`,
              style: { width: `${pct}%` }
            }
          ) })
        ] }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "usage-numbers", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { id: "usage-current", children: formatNumber(state.usageData.currentUsage) }),
          hasLimit ? /* @__PURE__ */ jsxRuntimeExports.jsxs(jsxRuntimeExports.Fragment, { children: [
            " / ",
            /* @__PURE__ */ jsxRuntimeExports.jsx("span", { id: "usage-limit", children: formatNumber(state.usageData.monthlyLimit) }),
            " summaries"
          ] }) : /* @__PURE__ */ jsxRuntimeExports.jsx(jsxRuntimeExports.Fragment, { children: " summaries used" })
        ] }),
        hasLimit ? /* @__PURE__ */ jsxRuntimeExports.jsxs("p", { className: "usage-reset-note", children: [
          "Resets ",
          formatDate(state.usageData.resetDate),
          " (",
          getRemainingDays(),
          " days)"
        ] }) : /* @__PURE__ */ jsxRuntimeExports.jsx("p", { className: "usage-reset-note", children: "No monthly limit reported — plan may be unlimited." }),
        state.usageData.planType && /* @__PURE__ */ jsxRuntimeExports.jsxs("p", { className: "usage-plan-type", children: [
          "Plan: ",
          state.usageData.planType
        ] })
      ] }),
      state.localStats && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "stat-card local-stats-card", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("h3", { children: "Your Activity (local)" }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "local-stats-grid", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "stat-item", children: [
            /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "stat-label", children: [
              /* @__PURE__ */ jsxRuntimeExports.jsx(FileText, { size: 11, style: { display: "inline", marginRight: 4, verticalAlign: "middle" } }),
              "Summaries"
            ] }),
            /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "stat-value", children: formatNumber(state.localStats.totalSummaries) })
          ] }),
          /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "stat-item", children: [
            /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "stat-label", children: [
              /* @__PURE__ */ jsxRuntimeExports.jsx(Hash, { size: 11, style: { display: "inline", marginRight: 4, verticalAlign: "middle" } }),
              "Words"
            ] }),
            /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "stat-value", children: formatNumber(state.localStats.wordsProcessed) })
          ] }),
          /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "stat-item", children: [
            /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "stat-label", children: [
              /* @__PURE__ */ jsxRuntimeExports.jsx(Zap, { size: 11, style: { display: "inline", marginRight: 4, verticalAlign: "middle" } }),
              "Tokens"
            ] }),
            /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "stat-value", children: formatNumber(state.localStats.tokensUsed) })
          ] })
        ] })
      ] }),
      hasLimit && pct >= 80 && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "error-message show usage-warning-banner", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx(TriangleAlert, { size: 13, style: { display: "inline", marginRight: 6, verticalAlign: "middle" } }),
        "You're approaching your monthly limit. Consider upgrading your plan."
      ] }),
      /* @__PURE__ */ jsxRuntimeExports.jsxs(
        "button",
        {
          id: "refresh-usage-btn",
          type: "button",
          className: "secondary-btn full-width refresh-usage-btn",
          onClick: loadUsageData,
          disabled: state.isLoading,
          children: [
            /* @__PURE__ */ jsxRuntimeExports.jsx(RefreshCw, { size: 13, strokeWidth: 2 }),
            state.isLoading ? "Refreshing…" : "Refresh Usage Data"
          ]
        }
      ),
      (state.lastRefresh || state.localStatsDate) && /* @__PURE__ */ jsxRuntimeExports.jsxs("p", { className: "usage-sync-line", children: [
        state.lastRefresh && /* @__PURE__ */ jsxRuntimeExports.jsxs(jsxRuntimeExports.Fragment, { children: [
          "Synced at ",
          state.lastRefresh
        ] }),
        state.lastRefresh && state.localStatsDate && /* @__PURE__ */ jsxRuntimeExports.jsx(jsxRuntimeExports.Fragment, { children: " · " }),
        state.localStatsDate && /* @__PURE__ */ jsxRuntimeExports.jsxs(jsxRuntimeExports.Fragment, { children: [
          "Local stats: ",
          state.localStatsDate
        ] })
      ] })
    ] }),
    state.error && /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "error-message show", role: "alert", children: state.error })
  ] });
};
function timeAgo(iso) {
  try {
    const date = new Date(iso);
    const diffMs = Date.now() - date.getTime();
    const sec = Math.floor(diffMs / 1e3);
    if (sec < 60) return "just now";
    const min = Math.floor(sec / 60);
    if (min < 60) return `${min}m ago`;
    const hrs = Math.floor(min / 60);
    if (hrs < 24) return `${hrs}h ago`;
    const days = Math.floor(hrs / 24);
    if (days < 7) return `${days}d ago`;
    return date.toLocaleDateString();
  } catch {
    return "unknown";
  }
}
function renderMarkdown(raw) {
  const html2 = k(raw);
  return purify.sanitize(html2);
}
const EmptySVG = () => /* @__PURE__ */ jsxRuntimeExports.jsxs(
  "svg",
  {
    className: "empty-state-svg",
    width: "96",
    height: "96",
    viewBox: "0 0 96 96",
    fill: "none",
    xmlns: "http://www.w3.org/2000/svg",
    "aria-hidden": "true",
    children: [
      /* @__PURE__ */ jsxRuntimeExports.jsx("rect", { x: "12", y: "18", width: "72", height: "60", rx: "8", fill: "currentColor", fillOpacity: "0.06", stroke: "currentColor", strokeOpacity: "0.25", strokeWidth: "2" }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("rect", { x: "22", y: "32", width: "36", height: "4", rx: "2", fill: "currentColor", fillOpacity: "0.22" }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("rect", { x: "22", y: "42", width: "52", height: "3", rx: "1.5", fill: "currentColor", fillOpacity: "0.14" }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("rect", { x: "22", y: "50", width: "44", height: "3", rx: "1.5", fill: "currentColor", fillOpacity: "0.14" }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("rect", { x: "22", y: "58", width: "32", height: "3", rx: "1.5", fill: "currentColor", fillOpacity: "0.10" }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("circle", { cx: "72", cy: "24", r: "6", fill: "currentColor", fillOpacity: "0.12", stroke: "currentColor", strokeOpacity: "0.3", strokeWidth: "1.5" }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("line", { x1: "72", y1: "20", x2: "72", y2: "28", stroke: "currentColor", strokeOpacity: "0.35", strokeWidth: "1.5", strokeLinecap: "round" }),
      /* @__PURE__ */ jsxRuntimeExports.jsx("line", { x1: "68", y1: "24", x2: "76", y2: "24", stroke: "currentColor", strokeOpacity: "0.35", strokeWidth: "1.5", strokeLinecap: "round" })
    ]
  }
);
const SavedSummariesTab = ({
  onSummariesChange,
  onGoToSummarize
}) => {
  const [summaries, setSummaries] = reactExports.useState([]);
  const [isLoading, setIsLoading] = reactExports.useState(true);
  const [openIds, setOpenIds] = reactExports.useState(/* @__PURE__ */ new Set());
  const [limit, setLimit] = reactExports.useState(6);
  const [deletingId, setDeletingId] = reactExports.useState(null);
  const [pendingDeleteId, setPendingDeleteId] = reactExports.useState(null);
  const [searchQuery, setSearchQuery] = reactExports.useState("");
  const showToast = useToast();
  reactExports.useEffect(() => {
    loadSummaries();
  }, []);
  const loadSummaries = async () => {
    setIsLoading(true);
    try {
      const list = await StorageService.getSavedSummaries();
      setSummaries(list);
      onSummariesChange?.();
    } catch (e) {
      console.error("Error loading summaries", e);
    } finally {
      setIsLoading(false);
    }
  };
  const filtered = reactExports.useMemo(() => {
    const q2 = searchQuery.trim().toLowerCase();
    if (!q2) return summaries;
    return summaries.filter((s) => {
      const title = (s.title || "").toLowerCase();
      const url = (s.url || "").toLowerCase();
      const body = (s.summary || "").toLowerCase();
      return title.includes(q2) || url.includes(q2) || body.includes(q2);
    });
  }, [summaries, searchQuery]);
  const toggleCard = reactExports.useCallback((id) => {
    setPendingDeleteId(null);
    setOpenIds((prev) => {
      const next = new Set(prev);
      if (next.has(id)) next.delete(id);
      else next.add(id);
      return next;
    });
  }, []);
  const copySummary = async (s) => {
    try {
      await navigator.clipboard.writeText(s.summary);
      showToast({ message: "Summary copied!", type: "success" });
    } catch (e) {
      console.error("Copy failed", e);
    }
  };
  const openOriginal = (s) => {
    try {
      chrome.tabs.create({ url: s.url });
    } catch (e) {
      console.error("Open failed", e);
    }
  };
  const deleteSummary = async (s) => {
    if (pendingDeleteId !== s.id) {
      setPendingDeleteId(s.id);
      return;
    }
    setPendingDeleteId(null);
    setDeletingId(s.id);
    try {
      await StorageService.deleteSummary(s.id);
      await loadSummaries();
      showToast({ message: "Summary deleted", type: "success" });
    } catch (e) {
      console.error("Delete failed", e);
      showToast({ message: "Delete failed", type: "error" });
    } finally {
      setDeletingId(null);
    }
  };
  const exportSummaries = () => {
    const blob = new Blob([JSON.stringify(summaries, null, 2)], { type: "application/json" });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = `get-tldr-summaries-${(/* @__PURE__ */ new Date()).toISOString().slice(0, 10)}.json`;
    a.click();
    URL.revokeObjectURL(url);
    showToast({ message: "Export started", type: "success" });
  };
  const openSavedSummariesPage = () => {
    chrome.tabs.create({ url: chrome.runtime.getURL("saved-summaries-modern.html") });
  };
  const visible = filtered.slice(0, limit);
  const showMoreAvailable = filtered.length > limit;
  return /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "saved-summaries-tab", "aria-live": "polite", children: [
    /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "saved-summaries-header", children: /* @__PURE__ */ jsxRuntimeExports.jsxs("h2", { children: [
      /* @__PURE__ */ jsxRuntimeExports.jsx(Library, { size: 18, strokeWidth: 2 }),
      "Saved Summaries",
      !isLoading && /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "saved-summaries-count-badge", children: summaries.length })
    ] }) }),
    /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "summaries-toolbar", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "search-input-wrapper", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx(Search, { size: 13, className: "search-icon-inline", "aria-hidden": true }),
        /* @__PURE__ */ jsxRuntimeExports.jsx(
          "input",
          {
            type: "search",
            className: "search-input",
            placeholder: "Search by title, URL, or content…",
            value: searchQuery,
            onChange: (e) => setSearchQuery(e.target.value),
            "aria-label": "Search saved summaries"
          }
        )
      ] }),
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "toolbar-row", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "summary-count", children: isLoading ? "…" : `${filtered.length} of ${summaries.length}` }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs(
          "button",
          {
            type: "button",
            className: "export-btn",
            onClick: exportSummaries,
            disabled: isLoading || summaries.length === 0,
            title: "Export all as JSON",
            children: [
              /* @__PURE__ */ jsxRuntimeExports.jsx(Download, { size: 12 }),
              " Export"
            ]
          }
        )
      ] })
    ] }),
    /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "saved-summary-list", role: "list", "aria-busy": isLoading, children: [
      isLoading && /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-list", children: [...Array(3)].map((_2, i) => /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "skeleton-card skeleton-animate", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "70%", height: 13, marginBottom: 7 } }),
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "skeleton-block", style: { width: "45%", height: 10 } })
      ] }, i)) }),
      !isLoading && visible.length === 0 && /* @__PURE__ */ jsxRuntimeExports.jsx("div", { role: "status", children: searchQuery ? /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "empty-state-illustrated", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx(EmptySVG, {}),
        /* @__PURE__ */ jsxRuntimeExports.jsx("h3", { children: "No results" }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("p", { children: [
          'No summaries match "',
          searchQuery,
          '". Try a different search term.'
        ] })
      ] }) : /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "empty-state-illustrated", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx(EmptySVG, {}),
        /* @__PURE__ */ jsxRuntimeExports.jsx("h3", { children: "Nothing saved yet" }),
        /* @__PURE__ */ jsxRuntimeExports.jsx("p", { children: "Summarize a page and it'll appear here automatically." }),
        onGoToSummarize && /* @__PURE__ */ jsxRuntimeExports.jsx("button", { type: "button", className: "empty-state-cta", onClick: onGoToSummarize, children: "Summarize a Page" })
      ] }) }),
      !isLoading && visible.map((s) => {
        const isOpen = openIds.has(s.id);
        const title = s.title || (() => {
          try {
            return new URL(s.url).hostname;
          } catch {
            return "Untitled";
          }
        })();
        const previewHtml = renderMarkdown(s.summary.length > 1200 ? s.summary.slice(0, 1200) + "…" : s.summary);
        const deleteLabel = pendingDeleteId === s.id ? "Confirm delete" : "Delete";
        return /* @__PURE__ */ jsxRuntimeExports.jsxs(
          "div",
          {
            className: "collapsible-card summary-card-mini",
            "data-open": isOpen ? "true" : "false",
            role: "listitem",
            children: [
              /* @__PURE__ */ jsxRuntimeExports.jsxs(
                "button",
                {
                  type: "button",
                  className: "collapsible-trigger",
                  onClick: () => toggleCard(s.id),
                  "aria-expanded": isOpen,
                  "aria-controls": `summary-content-${s.id}`,
                  children: [
                    /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "summary-trigger-text", children: [
                      /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "summary-title-text", children: title }),
                      /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "summary-meta", children: [
                        timeAgo(s.createdAt),
                        " · ",
                        s.wordCount || 0,
                        "w"
                      ] })
                    ] }),
                    /* @__PURE__ */ jsxRuntimeExports.jsx(ChevronDown, { size: 14, className: `chevron ${isOpen ? "chevron-open" : ""}`, "aria-hidden": true })
                  ]
                }
              ),
              /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: `summary-content-${s.id}`, className: "summary-content", "aria-hidden": !isOpen, children: [
                /* @__PURE__ */ jsxRuntimeExports.jsx(
                  "div",
                  {
                    className: "summary-body-text markdown-preview markdown-content",
                    dangerouslySetInnerHTML: { __html: previewHtml }
                  }
                ),
                /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "summary-actions-row", children: [
                  /* @__PURE__ */ jsxRuntimeExports.jsxs("button", { type: "button", className: "mini-btn", onClick: () => copySummary(s), title: "Copy summary", children: [
                    /* @__PURE__ */ jsxRuntimeExports.jsx(Copy, { size: 12, strokeWidth: 2.5 }),
                    " Copy"
                  ] }),
                  /* @__PURE__ */ jsxRuntimeExports.jsxs("button", { type: "button", className: "mini-btn", onClick: () => openOriginal(s), title: "Open original page", children: [
                    /* @__PURE__ */ jsxRuntimeExports.jsx(ExternalLink, { size: 12, strokeWidth: 2.5 }),
                    " Open"
                  ] }),
                  /* @__PURE__ */ jsxRuntimeExports.jsxs(
                    "button",
                    {
                      type: "button",
                      className: `mini-btn danger ${pendingDeleteId === s.id ? "confirm-pending" : ""}`,
                      disabled: deletingId === s.id,
                      onClick: () => deleteSummary(s),
                      title: pendingDeleteId === s.id ? "Click again to confirm" : "Delete summary",
                      children: [
                        /* @__PURE__ */ jsxRuntimeExports.jsx(Trash2, { size: 12, strokeWidth: 2.5 }),
                        deletingId === s.id ? "Deleting…" : deleteLabel
                      ]
                    }
                  )
                ] })
              ] })
            ]
          },
          s.id
        );
      })
    ] }),
    showMoreAvailable && /* @__PURE__ */ jsxRuntimeExports.jsx(
      "button",
      {
        type: "button",
        className: "secondary-btn full-width load-more-btn",
        onClick: () => setLimit((l) => l + 6),
        children: "Load more"
      }
    ),
    /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "saved-summaries-actions", children: /* @__PURE__ */ jsxRuntimeExports.jsx(
      "button",
      {
        type: "button",
        className: "open-page-btn primary-btn full-width",
        onClick: openSavedSummariesPage,
        disabled: isLoading,
        children: /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "btn-text", children: "Open Full Saved Summaries Page" })
      }
    ) })
  ] });
};
const ToastContext = reactExports.createContext(() => {
});
const useToast = () => reactExports.useContext(ToastContext);
const ToastNotification = ({ toast, onDismiss }) => /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: `toast-notification ${toast.visible ? "toast-visible" : ""} toast-${toast.type}`, children: [
  /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "toast-icon", children: toast.type === "success" ? /* @__PURE__ */ jsxRuntimeExports.jsx(CircleCheck, { size: 14, strokeWidth: 2.5 }) : /* @__PURE__ */ jsxRuntimeExports.jsx(CircleAlert, { size: 14, strokeWidth: 2.5 }) }),
  /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "toast-message", children: toast.message }),
  toast.visible && /* @__PURE__ */ jsxRuntimeExports.jsx("button", { type: "button", className: "toast-dismiss", onClick: onDismiss, "aria-label": "Dismiss", children: /* @__PURE__ */ jsxRuntimeExports.jsx(X$1, { size: 13 }) }),
  /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "toast-progress" })
] });
const ConfirmLogoutDialog = ({ onCancel, onConfirm }) => /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "confirm-overlay", role: "dialog", "aria-modal": "true", "aria-labelledby": "confirm-title", children: /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "confirm-dialog", children: [
  /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "confirm-dialog-icon", children: /* @__PURE__ */ jsxRuntimeExports.jsx(LogOut, { size: 22, strokeWidth: 2 }) }),
  /* @__PURE__ */ jsxRuntimeExports.jsx("h3", { id: "confirm-title", children: "Log out?" }),
  /* @__PURE__ */ jsxRuntimeExports.jsx("p", { children: "This will remove your API key from the extension. You'll need to enter it again to use Get TLDR." }),
  /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "confirm-dialog-actions", children: [
    /* @__PURE__ */ jsxRuntimeExports.jsx("button", { type: "button", className: "confirm-cancel-btn", onClick: onCancel, children: "Cancel" }),
    /* @__PURE__ */ jsxRuntimeExports.jsx("button", { type: "button", className: "confirm-logout-btn", onClick: onConfirm, children: "Log out" })
  ] })
] }) });
const SettingsPanel = ({ theme, uiPrefs, onToggleTheme, onToggleReadingFont, onToggleCompact, onLogout, onClose }) => {
  const panelRef = reactExports.useRef(null);
  reactExports.useEffect(() => {
    const handler = (e) => {
      if (panelRef.current && !panelRef.current.contains(e.target)) {
        onClose();
      }
    };
    document.addEventListener("mousedown", handler);
    return () => document.removeEventListener("mousedown", handler);
  }, [onClose]);
  reactExports.useEffect(() => {
    const handler = (e) => {
      if (e.key === "Escape") onClose();
    };
    document.addEventListener("keydown", handler);
    return () => document.removeEventListener("keydown", handler);
  }, [onClose]);
  return /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "settings-panel", ref: panelRef, role: "menu", children: [
    /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "settings-panel-header", children: "Preferences" }),
    /* @__PURE__ */ jsxRuntimeExports.jsxs(
      "button",
      {
        type: "button",
        className: "settings-panel-item",
        onClick: onToggleTheme,
        role: "menuitem",
        children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "settings-panel-item-icon", children: theme === "dark" ? /* @__PURE__ */ jsxRuntimeExports.jsx(Sun, { size: 15, strokeWidth: 2 }) : /* @__PURE__ */ jsxRuntimeExports.jsx(Moon, { size: 15, strokeWidth: 2 }) }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "settings-panel-item-label", children: theme === "dark" ? "Light mode" : "Dark mode" }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: `settings-toggle ${theme === "light" ? "on" : ""}`, "aria-hidden": true })
        ]
      }
    ),
    /* @__PURE__ */ jsxRuntimeExports.jsxs(
      "button",
      {
        type: "button",
        className: "settings-panel-item",
        onClick: onToggleReadingFont,
        role: "menuitem",
        children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "settings-panel-item-icon", children: /* @__PURE__ */ jsxRuntimeExports.jsx(Type, { size: 15, strokeWidth: 2 }) }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "settings-panel-item-label", children: "Reading font" }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: `settings-toggle ${uiPrefs.readingFont ? "on" : ""}`, "aria-hidden": true })
        ]
      }
    ),
    /* @__PURE__ */ jsxRuntimeExports.jsxs(
      "button",
      {
        type: "button",
        className: "settings-panel-item",
        onClick: onToggleCompact,
        role: "menuitem",
        children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "settings-panel-item-icon", children: /* @__PURE__ */ jsxRuntimeExports.jsx(LayoutGrid, { size: 15, strokeWidth: 2 }) }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "settings-panel-item-label", children: "Compact layout" }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: `settings-toggle ${uiPrefs.compactDensity ? "on" : ""}`, "aria-hidden": true })
        ]
      }
    ),
    /* @__PURE__ */ jsxRuntimeExports.jsxs(
      "button",
      {
        type: "button",
        className: "settings-panel-item",
        onClick: onLogout,
        role: "menuitem",
        children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "settings-panel-item-icon", children: /* @__PURE__ */ jsxRuntimeExports.jsx(LogOut, { size: 15, strokeWidth: 2 }) }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "settings-panel-item-label", children: "Log out" })
        ]
      }
    )
  ] });
};
const SetupStepIndicator = ({ step }) => {
  const steps = ["Get key", "Enter below", "Done!"];
  return /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "setup-steps", "aria-label": "Setup progress", children: steps.map((label, idx) => {
    const num = idx + 1;
    const isDone = step > num;
    const isActive = step === num;
    return /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "setup-step-wrap", children: [
      /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: `setup-step ${isDone ? "done" : ""} ${isActive ? "active" : ""}`, children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "setup-step-dot", children: isDone ? /* @__PURE__ */ jsxRuntimeExports.jsx(CircleCheck, { size: 12, strokeWidth: 3 }) : num }),
        /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "setup-step-label", children: label })
      ] }),
      idx < steps.length - 1 && /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: `setup-step-connector ${isDone ? "filled" : ""}` })
    ] }, num);
  }) });
};
const App = () => {
  const [state, setState] = reactExports.useState({
    screen: "setup",
    activeTab: "summarize",
    apiKey: "",
    isLoading: false,
    error: "",
    theme: "dark",
    savedCount: 0,
    setupSuccess: false
  });
  const [uiPrefs, setUiPrefs] = reactExports.useState({});
  const [showApiKey, setShowApiKey] = reactExports.useState(false);
  const [apiKeyInput, setApiKeyInput] = reactExports.useState("");
  const [showSettings, setShowSettings] = reactExports.useState(false);
  const [showLogoutDialog, setShowLogoutDialog] = reactExports.useState(false);
  const [toast, setToast] = reactExports.useState({ visible: false, message: "", type: "success" });
  const toastTimerRef = reactExports.useRef(null);
  const showToast = reactExports.useCallback((opts) => {
    if (toastTimerRef.current) clearTimeout(toastTimerRef.current);
    setToast({ visible: true, message: opts.message, type: opts.type ?? "success" });
    toastTimerRef.current = setTimeout(() => {
      setToast((prev) => ({ ...prev, visible: false }));
    }, opts.duration ?? 2800);
  }, []);
  const handleDismissToast = reactExports.useCallback(() => {
    if (toastTimerRef.current) clearTimeout(toastTimerRef.current);
    setToast((prev) => ({ ...prev, visible: false }));
  }, []);
  const handleMouseMove = reactExports.useCallback((e) => {
    const el = e.currentTarget;
    el.style.setProperty("--mouse-x", `${e.clientX}px`);
    el.style.setProperty("--mouse-y", `${e.clientY}px`);
  }, []);
  const refreshSavedCount = reactExports.useCallback(async () => {
    const list = await StorageService.getSavedSummaries();
    setState((prev) => ({ ...prev, savedCount: list.length }));
  }, []);
  reactExports.useEffect(() => {
    Promise.all([
      checkExistingApiKey(),
      initTheme(),
      initUiPrefs(),
      refreshSavedCount()
    ]).catch(console.error);
    const onStorageChange = (changes, area) => {
      if (area === "local" && changes.get_tldr_saved_summaries) refreshSavedCount();
    };
    chrome.storage.onChanged.addListener(onStorageChange);
    return () => chrome.storage.onChanged.removeListener(onStorageChange);
  }, [refreshSavedCount]);
  const initUiPrefs = async () => {
    const prefs = await StorageService.getUiPreferences();
    setUiPrefs(prefs);
    applyUiPrefs(prefs);
  };
  const applyUiPrefs = (prefs) => {
    document.documentElement.setAttribute("data-reading-font", prefs.readingFont ? "true" : "false");
    document.documentElement.setAttribute("data-density", prefs.compactDensity ? "compact" : "normal");
  };
  const initTheme = async () => {
    const pref = await StorageService.getThemePreference();
    setState((prev) => ({ ...prev, theme: pref }));
    applyTheme(pref);
    document.documentElement.setAttribute("data-ui", "pro");
  };
  const applyTheme = (theme) => {
    document.documentElement.setAttribute("data-theme", theme);
    if (!document.documentElement.getAttribute("data-ui")) {
      document.documentElement.setAttribute("data-ui", "pro");
    }
  };
  const toggleTheme = async () => {
    setState((prev) => {
      const next = prev.theme === "dark" ? "light" : "dark";
      applyTheme(next);
      StorageService.saveThemePreference(next);
      return { ...prev, theme: next };
    });
  };
  const toggleReadingFont = async () => {
    const next = !uiPrefs.readingFont;
    const prefs = { ...uiPrefs, readingFont: next };
    setUiPrefs(prefs);
    applyUiPrefs(prefs);
    await StorageService.saveUiPreferences({ readingFont: next });
  };
  const toggleCompactDensity = async () => {
    const next = !uiPrefs.compactDensity;
    const prefs = { ...uiPrefs, compactDensity: next };
    setUiPrefs(prefs);
    applyUiPrefs(prefs);
    await StorageService.saveUiPreferences({ compactDensity: next });
  };
  const checkExistingApiKey = async () => {
    try {
      const existing = await StorageService.getApiKey();
      if (existing) setState((prev) => ({ ...prev, apiKey: existing, screen: "main" }));
    } catch (e) {
      console.error("Error checking API key:", e);
    }
  };
  const validateAndSaveApiKey = async () => {
    if (!apiKeyInput.trim()) {
      setState((prev) => ({ ...prev, error: "Please enter an API key" }));
      return;
    }
    if (!apiKeyInput.startsWith("tl_")) {
      setState((prev) => ({ ...prev, error: 'API key must start with "tl_"' }));
      return;
    }
    setState((prev) => ({ ...prev, isLoading: true, error: "" }));
    try {
      const isValid = await ApiService.validateApiKey(apiKeyInput);
      if (isValid) {
        await StorageService.saveApiKey(apiKeyInput);
        setState((prev) => ({ ...prev, apiKey: apiKeyInput, isLoading: false, setupSuccess: true, error: "" }));
        showToast({ message: "API key saved — welcome!", type: "success" });
        setTimeout(() => {
          setState((prev) => ({ ...prev, screen: "main", setupSuccess: false }));
        }, 900);
      } else {
        setState((prev) => ({ ...prev, error: "Invalid API key. Please check and try again.", isLoading: false }));
      }
    } catch {
      setState((prev) => ({ ...prev, error: "Failed to validate API key. Please try again.", isLoading: false }));
    }
  };
  const handleTabChange = (tab) => setState((prev) => ({ ...prev, activeTab: tab }));
  const requestLogout = () => {
    setShowSettings(false);
    setShowLogoutDialog(true);
  };
  const cancelLogout = () => setShowLogoutDialog(false);
  const confirmLogout = async () => {
    setShowLogoutDialog(false);
    await StorageService.clearApiKey();
    setState((prev) => ({ ...prev, screen: "setup", apiKey: "", activeTab: "summarize" }));
    setApiKeyInput("");
  };
  const handleKeyPress = (e) => {
    if (e.key === "Enter") validateAndSaveApiKey();
  };
  const pasteApiKeyFromClipboard = async () => {
    try {
      const text2 = await navigator.clipboard.readText();
      if (text2.trim()) setApiKeyInput(text2.trim());
    } catch {
      setState((prev) => ({ ...prev, error: "Could not read clipboard. Paste manually." }));
    }
  };
  const setupStep = !apiKeyInput.trim() ? 1 : state.isLoading ? 2 : state.setupSuccess ? 3 : 2;
  return /* @__PURE__ */ jsxRuntimeExports.jsxs(ToastContext.Provider, { value: showToast, children: [
    /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "root", onMouseMove: handleMouseMove, children: [
      state.screen === "setup" && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "api-setup", className: "screen", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "header", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("img", { src: "icons/icon48.png", alt: "Get TLDR", className: "logo" }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("h1", { children: "Get TLDR" })
        ] }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "setup-content", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("h2", { children: "Welcome!" }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("p", { children: "Enter your API key to get started with AI-powered summarization." }),
          /* @__PURE__ */ jsxRuntimeExports.jsx(SetupStepIndicator, { step: setupStep }),
          state.setupSuccess && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "setup-success-banner", role: "status", children: [
            /* @__PURE__ */ jsxRuntimeExports.jsx(CircleCheck, { size: 14, strokeWidth: 2.5 }),
            "Key validated — opening app…"
          ] }),
          /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "input-group setup-actions-row", children: [
            /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "api-key-field", children: [
              /* @__PURE__ */ jsxRuntimeExports.jsx(
                "input",
                {
                  type: showApiKey ? "text" : "password",
                  id: "api-key-input",
                  placeholder: "Enter your API key (tl_...)",
                  value: apiKeyInput,
                  onChange: (e) => setApiKeyInput(e.target.value),
                  onKeyPress: handleKeyPress,
                  disabled: state.isLoading,
                  autoComplete: "off"
                }
              ),
              /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "api-key-field-actions", children: [
                /* @__PURE__ */ jsxRuntimeExports.jsx(
                  "button",
                  {
                    type: "button",
                    className: "icon-btn-sm",
                    onClick: () => setShowApiKey((v2) => !v2),
                    "aria-label": showApiKey ? "Hide API key" : "Show API key",
                    children: showApiKey ? /* @__PURE__ */ jsxRuntimeExports.jsx(EyeOff, { size: 15 }) : /* @__PURE__ */ jsxRuntimeExports.jsx(Eye, { size: 15 })
                  }
                ),
                /* @__PURE__ */ jsxRuntimeExports.jsx(
                  "button",
                  {
                    type: "button",
                    className: "icon-btn-sm",
                    onClick: pasteApiKeyFromClipboard,
                    "aria-label": "Paste from clipboard",
                    title: "Paste from clipboard",
                    children: /* @__PURE__ */ jsxRuntimeExports.jsx(ClipboardPaste, { size: 15 })
                  }
                )
              ] })
            ] }),
            /* @__PURE__ */ jsxRuntimeExports.jsxs(
              "button",
              {
                id: "validate-key-btn",
                className: `primary-btn full-width ${state.isLoading ? "loading" : ""}`,
                onClick: validateAndSaveApiKey,
                disabled: state.isLoading,
                type: "button",
                children: [
                  /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "btn-text", children: "Validate & Save" }),
                  /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "btn-loading", children: [
                    /* @__PURE__ */ jsxRuntimeExports.jsxs("span", { className: "loading-dots", children: [
                      /* @__PURE__ */ jsxRuntimeExports.jsx("span", {}),
                      /* @__PURE__ */ jsxRuntimeExports.jsx("span", {}),
                      /* @__PURE__ */ jsxRuntimeExports.jsx("span", {})
                    ] }),
                    "Validating…"
                  ] })
                ]
              }
            )
          ] }),
          state.error && /* @__PURE__ */ jsxRuntimeExports.jsx("div", { id: "api-error", className: "error-message show", role: "alert", children: state.error }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "help-text", children: /* @__PURE__ */ jsxRuntimeExports.jsxs("p", { children: [
            "Don't have an API key?",
            " ",
            /* @__PURE__ */ jsxRuntimeExports.jsx("a", { href: "https://www.get-tldr.com", target: "_blank", rel: "noopener noreferrer", children: "Get one here" })
          ] }) })
        ] })
      ] }),
      state.screen === "main" && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "main-app", className: "screen", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "header", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsx("img", { src: "icons/icon48.png", alt: "Get TLDR", className: "logo" }),
          /* @__PURE__ */ jsxRuntimeExports.jsx("h1", { children: "Get TLDR" }),
          /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "settings-btn-wrap header-actions-group", children: [
            /* @__PURE__ */ jsxRuntimeExports.jsx(
              "button",
              {
                id: "settings-btn",
                type: "button",
                className: "icon-btn",
                onClick: () => setShowSettings((v2) => !v2),
                "aria-label": "Settings",
                "aria-expanded": showSettings,
                title: "Settings",
                children: /* @__PURE__ */ jsxRuntimeExports.jsx(Settings, { size: 16, strokeWidth: 2 })
              }
            ),
            showSettings && /* @__PURE__ */ jsxRuntimeExports.jsx(
              SettingsPanel,
              {
                theme: state.theme,
                uiPrefs,
                onToggleTheme: () => {
                  toggleTheme();
                  setShowSettings(false);
                },
                onToggleReadingFont: () => {
                  toggleReadingFont();
                },
                onToggleCompact: () => {
                  toggleCompactDensity();
                },
                onLogout: requestLogout,
                onClose: () => setShowSettings(false)
              }
            )
          ] })
        ] }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "tab-nav", role: "tablist", "aria-label": "Main navigation", children: [
          /* @__PURE__ */ jsxRuntimeExports.jsxs(
            "button",
            {
              role: "tab",
              "aria-selected": state.activeTab === "summarize",
              className: `tab-btn ${state.activeTab === "summarize" ? "active" : ""}`,
              onClick: () => handleTabChange("summarize"),
              children: [
                /* @__PURE__ */ jsxRuntimeExports.jsx(PenLine, { size: 14, strokeWidth: 2 }),
                "Summarize"
              ]
            }
          ),
          /* @__PURE__ */ jsxRuntimeExports.jsxs(
            "button",
            {
              role: "tab",
              "aria-selected": state.activeTab === "saved",
              className: `tab-btn ${state.activeTab === "saved" ? "active" : ""}`,
              onClick: () => handleTabChange("saved"),
              children: [
                /* @__PURE__ */ jsxRuntimeExports.jsx(Bookmark, { size: 14, strokeWidth: 2 }),
                "Saved",
                state.savedCount > 0 && /* @__PURE__ */ jsxRuntimeExports.jsx("span", { className: "tab-badge", "aria-label": `${state.savedCount} saved`, children: state.savedCount > 99 ? "99+" : state.savedCount })
              ]
            }
          ),
          /* @__PURE__ */ jsxRuntimeExports.jsxs(
            "button",
            {
              role: "tab",
              "aria-selected": state.activeTab === "usage",
              className: `tab-btn ${state.activeTab === "usage" ? "active" : ""}`,
              onClick: () => handleTabChange("usage"),
              children: [
                /* @__PURE__ */ jsxRuntimeExports.jsx(ChartNoAxesColumn, { size: 14, strokeWidth: 2 }),
                "Usage"
              ]
            }
          )
        ] }),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { className: "tab-content tab-content-animated", role: "tabpanel", children: [
          state.activeTab === "summarize" && /* @__PURE__ */ jsxRuntimeExports.jsx(
            SummarizeTab,
            {
              apiKey: state.apiKey,
              onSummarySaved: refreshSavedCount
            }
          ),
          state.activeTab === "saved" && /* @__PURE__ */ jsxRuntimeExports.jsx(
            SavedSummariesTab,
            {
              onSummariesChange: refreshSavedCount,
              onGoToSummarize: () => handleTabChange("summarize")
            }
          ),
          state.activeTab === "usage" && /* @__PURE__ */ jsxRuntimeExports.jsx(UsageTab, { apiKey: state.apiKey })
        ] }, state.activeTab),
        /* @__PURE__ */ jsxRuntimeExports.jsxs("footer", { className: "app-footer", children: [
          "© 2026",
          " ",
          /* @__PURE__ */ jsxRuntimeExports.jsx("a", { href: "https://www.get-tldr.com", target: "_blank", rel: "noopener noreferrer", children: "get-tldr.com" })
        ] })
      ] }),
      state.isLoading && /* @__PURE__ */ jsxRuntimeExports.jsxs("div", { id: "loading-overlay", className: "overlay", children: [
        /* @__PURE__ */ jsxRuntimeExports.jsx("div", { className: "spinner" }),
        /* @__PURE__ */ jsxRuntimeExports.jsx("p", { children: "Loading…" })
      ] })
    ] }),
    showLogoutDialog && /* @__PURE__ */ jsxRuntimeExports.jsx(ConfirmLogoutDialog, { onCancel: cancelLogout, onConfirm: confirmLogout }),
    /* @__PURE__ */ jsxRuntimeExports.jsx(ToastNotification, { toast, onDismiss: handleDismissToast })
  ] });
};
const container = document.getElementById("root");
if (container) {
  const root = clientExports.createRoot(container);
  root.render(/* @__PURE__ */ jsxRuntimeExports.jsx(App, {}));
}
//# sourceMappingURL=popup.js.map
