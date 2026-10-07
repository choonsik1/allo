#define ALLOW_EMPTY_HLS_STREAM_READS 1

//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <hls_vector.h>
#include <math.h>
#include <stdint.h>
using namespace std;
void node_0_0(
  int32_t v0[1][1],
  hls::stream< ap_uint<26> >& v1,
  hls::stream< ap_uint<26> >& v2,
  hls::stream< ap_uint<26> >& v3,
  hls::stream< ap_uint<26> >& v4,
  hls::stream< ap_uint<17> >& v5,
  hls::stream< ap_uint<17> >& v6,
  hls::stream< ap_uint<17> >& v7,
  hls::stream< ap_uint<17> >& v8,
  hls::stream< int32_t >& v9,
  hls::stream< int32_t >& v10,
  hls::stream< int32_t >& v11,
  hls::stream< int32_t >& v12,
  hls::stream< int32_t >& v13,
  hls::stream< int32_t >& v14,
  hls::stream< int32_t >& v15,
  hls::stream< int32_t >& v16,
  hls::stream< ap_uint<26> >& v17,
  hls::stream< ap_uint<26> >& v18,
  hls::stream< ap_uint<26> >& v19,
  hls::stream< ap_uint<26> >& v20,
  hls::stream< int32_t >& v21,
  hls::stream< int32_t >& v22,
  hls::stream< int32_t >& v23,
  hls::stream< int32_t >& v24,
  hls::stream< int32_t >& v25,
  hls::stream< int32_t >& v26,
  hls::stream< int32_t >& v27,
  hls::stream< int32_t >& v28,
  hls::stream< ap_uint<17> >& v29,
  hls::stream< ap_uint<17> >& v30,
  hls::stream< ap_uint<17> >& v31,
  hls::stream< ap_uint<17> >& v32
) {	// L4
  int32_t irf[8];	// L41
  #pragma HLS array_partition variable=irf complete dim=1

  for (int v34 = 0; v34 < 8; v34++) {	// L42
    irf[v34] = 0;	// L42
  }
  half drf[8];	// L43
  #pragma HLS array_partition variable=drf complete dim=1

  for (int v36 = 0; v36 < 8; v36++) {	// L44
    drf[v36] = 0.000000;	// L44
  }
  int32_t drf_full[8];	// L45
  #pragma HLS array_partition variable=drf_full complete dim=1

  for (int v38 = 0; v38 < 8; v38++) {	// L46
    drf_full[v38] = 0;	// L46
  }
  int32_t dsmask;	// L47
  dsmask = 0;	// L48
  int32_t crv_vld;	// L49
  crv_vld = 0;	// L50
  half crv_data;	// L51
  crv_data = 0.000000;	// L52
  int32_t crv_addr;	// L53
  crv_addr = 0;	// L54
  int32_t crv_mode;	// L55
  crv_mode = 0;	// L56
  int32_t crv_raw;	// L57
  crv_raw = 0;	// L58
  int32_t csd_vld;	// L59
  csd_vld = 0;	// L60
  ap_uint<26> csd_pkt;	// L61
  csd_pkt = 0;	// L62
  int32_t csd_dir;	// L63
  csd_dir = 0;	// L64
  int32_t row_id;	// L65
  row_id = 0;	// L66
  int32_t col_id;	// L67
  col_id = 0;	// L68
  ap_uint<26> oe_r;	// L69
  oe_r = 0;	// L70
  ap_uint<26> ow_r;	// L71
  ow_r = 0;	// L72
  ap_uint<26> on_r;	// L73
  on_r = 0;	// L74
  ap_uint<26> os_r;	// L75
  os_r = 0;	// L76
  ap_uint<17> txn_r;	// L77
  txn_r = 0;	// L78
  ap_uint<17> txs_r;	// L79
  txs_r = 0;	// L80
  ap_uint<17> txw_r;	// L81
  txw_r = 0;	// L82
  ap_uint<17> txe_r;	// L83
  txe_r = 0;	// L84
  half hold_v[4][2];	// L85
  #pragma HLS array_partition variable=hold_v complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=2

  for (int v59 = 0; v59 < 4; v59++) {	// L86
    for (int v60 = 0; v60 < 2; v60++) {	// L86
      hold_v[v59][v60] = 0.000000;	// L86
    }
  }
  uint8_t hold_cnt[4];	// L87
  #pragma HLS array_partition variable=hold_cnt complete dim=1

  for (int v62 = 0; v62 < 4; v62++) {	// L88
    hold_cnt[v62] = 0;	// L88
  }
  ap_uint<26> rbuf[4][2];	// L89
  #pragma HLS array_partition variable=rbuf complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=2

  for (int v64 = 0; v64 < 4; v64++) {	// L90
    for (int v65 = 0; v65 < 2; v65++) {	// L90
      rbuf[v64][v65] = 0;	// L90
    }
  }
  uint8_t rbcnt[4];	// L91
  #pragma HLS array_partition variable=rbcnt complete dim=1

  for (int v67 = 0; v67 < 4; v67++) {	// L92
    rbcnt[v67] = 0;	// L92
  }
  uint8_t rcred[4];	// L93
  #pragma HLS array_partition variable=rcred complete dim=1

  for (int v69 = 0; v69 < 4; v69++) {	// L94
    rcred[v69] = 0;	// L94
  }
  uint8_t cre_r;	// L95
  cre_r = 2;	// L96
  uint8_t crw_r;	// L97
  crw_r = 2;	// L98
  uint8_t crs_r;	// L99
  crs_r = 2;	// L100
  uint8_t crn_r;	// L101
  crn_r = 2;	// L102
  int32_t scred[4];	// L103
  #pragma HLS array_partition variable=scred complete dim=1

  for (int v75 = 0; v75 < 4; v75++) {	// L104
    scred[v75] = 0;	// L104
  }
  int32_t txp_v[4];	// L105
  #pragma HLS array_partition variable=txp_v complete dim=1

  for (int v77 = 0; v77 < 4; v77++) {	// L106
    txp_v[v77] = 0;	// L106
  }
  half txp_d[4];	// L107
  #pragma HLS array_partition variable=txp_d complete dim=1

  for (int v79 = 0; v79 < 4; v79++) {	// L108
    txp_d[v79] = 0.000000;	// L108
  }
  int32_t txp_r[4];	// L109
  #pragma HLS array_partition variable=txp_r complete dim=1

  for (int v81 = 0; v81 < 4; v81++) {	// L110
    txp_r[v81] = 0;	// L110
  }
  int32_t sc_r[4];	// L111
  #pragma HLS array_partition variable=sc_r complete dim=1

  for (int v83 = 0; v83 < 4; v83++) {	// L112
    sc_r[v83] = 2;	// L112
  }
  int32_t cfg_isz;	// L113
  cfg_isz = 0;	// L114
  int32_t cfg_itsz;	// L115
  cfg_itsz = 0;	// L116
  uint8_t fetch_en;	// L117
  fetch_en = 0;	// L118
  uint8_t instr_cnt;	// L119
  instr_cnt = 0;	// L120
  uint8_t iter_cnt;	// L121
  iter_cnt = 0;	// L122
  uint8_t condition_reg;	// L123
  condition_reg = 0;	// L124
  uint8_t sb_v[5];	// L125
  #pragma HLS array_partition variable=sb_v complete dim=1

  for (int v91 = 0; v91 < 5; v91++) {	// L126
    sb_v[v91] = 0;	// L126
  }
  uint8_t sb_dst[5];	// L127
  #pragma HLS array_partition variable=sb_dst complete dim=1

  for (int v93 = 0; v93 < 5; v93++) {	// L128
    sb_dst[v93] = 0;	// L128
  }
  uint8_t sb_cmp[5];	// L129
  #pragma HLS array_partition variable=sb_cmp complete dim=1

  for (int v95 = 0; v95 < 5; v95++) {	// L130
    sb_cmp[v95] = 0;	// L130
  }
  uint8_t sb_rtr[5];	// L131
  #pragma HLS array_partition variable=sb_rtr complete dim=1

  for (int v97 = 0; v97 < 5; v97++) {	// L132
    sb_rtr[v97] = 0;	// L132
  }
  uint8_t sb_inj[5];	// L133
  #pragma HLS array_partition variable=sb_inj complete dim=1

  for (int v99 = 0; v99 < 5; v99++) {	// L134
    sb_inj[v99] = 0;	// L134
  }
  uint8_t sb_dir[5];	// L135
  #pragma HLS array_partition variable=sb_dir complete dim=1

  for (int v101 = 0; v101 < 5; v101++) {	// L136
    sb_dir[v101] = 0;	// L136
  }
  uint8_t sb_id[5];	// L137
  #pragma HLS array_partition variable=sb_id complete dim=1

  for (int v103 = 0; v103 < 5; v103++) {	// L138
    sb_id[v103] = 0;	// L138
  }
  uint8_t sb_rvld[5];	// L139
  #pragma HLS array_partition variable=sb_rvld complete dim=1

  for (int v105 = 0; v105 < 5; v105++) {	// L140
    sb_rvld[v105] = 0;	// L140
  }
  uint8_t sb_ix[5];	// L141
  #pragma HLS array_partition variable=sb_ix complete dim=1

  for (int v107 = 0; v107 < 5; v107++) {	// L142
    sb_ix[v107] = 0;	// L142
  }
  uint8_t sb_long[5];	// L143
  #pragma HLS array_partition variable=sb_long complete dim=1

  for (int v109 = 0; v109 < 5; v109++) {	// L144
    sb_long[v109] = 0;	// L144
  }
  half resq[8];	// L145
  #pragma HLS array_partition variable=resq complete dim=1
#pragma HLS dependence variable=resq type=inter dependent=false

  for (int v111 = 0; v111 < 8; v111++) {	// L146
    resq[v111] = 0.000000;	// L146
  }
  uint8_t cmpq[8];	// L147
  #pragma HLS array_partition variable=cmpq complete dim=1
#pragma HLS dependence variable=cmpq type=inter dependent=false

  for (int v113 = 0; v113 < 8; v113++) {	// L148
    cmpq[v113] = 0;	// L148
  }
  uint8_t resq_wr;	// L149
  resq_wr = 0;	// L150
  ap_uint<26> zpkt;	// L151
  zpkt = 0;	// L152
  ap_uint<17> zsys;	// L153
  zsys = 0;	// L154
  int32_t zcr;	// L155
  zcr = 0;	// L156
  int32_t v118 = v0[0][0];	// L157
  ap_int<33> v119 = v118;	// L158
  ap_int<33> v120 = v119 - 1;	// L159
  int v121 = v120;	// L160
  for (int v122 = 0; v122 < v121; v122 += 1) {	// L161
    ap_int<26> v123 = zpkt;	// L162
    v1.write(v123);	// L163
    ap_int<26> v124 = zpkt;	// L164
    v2.write(v124);	// L165
    ap_int<26> v125 = zpkt;	// L166
    v3.write(v125);	// L167
    ap_int<26> v126 = zpkt;	// L168
    v4.write(v126);	// L169
    ap_int<17> v127 = zsys;	// L170
    v5.write(v127);	// L171
    ap_int<17> v128 = zsys;	// L172
    v6.write(v128);	// L173
    ap_int<17> v129 = zsys;	// L174
    v7.write(v129);	// L175
    ap_int<17> v130 = zsys;	// L176
    v8.write(v130);	// L177
    int32_t v131 = zcr;	// L178
    v9.write(v131);	// L179
    int32_t v132 = zcr;	// L180
    v10.write(v132);	// L181
    int32_t v133 = zcr;	// L182
    v11.write(v133);	// L183
    int32_t v134 = zcr;	// L184
    v12.write(v134);	// L185
    int32_t v135 = zcr;	// L186
    v13.write(v135);	// L187
    int32_t v136 = zcr;	// L188
    v14.write(v136);	// L189
    int32_t v137 = zcr;	// L190
    v15.write(v137);	// L191
    int32_t v138 = zcr;	// L192
    v16.write(v138);	// L193
  }
  ap_int<26> v139 = oe_r;	// L195
  v1.write(v139);	// L196
  ap_int<26> v140 = ow_r;	// L197
  v2.write(v140);	// L198
  ap_int<26> v141 = os_r;	// L199
  v3.write(v141);	// L200
  ap_int<26> v142 = on_r;	// L201
  v4.write(v142);	// L202
  ap_int<17> v143 = txe_r;	// L203
  v5.write(v143);	// L204
  ap_int<17> v144 = txw_r;	// L205
  v6.write(v144);	// L206
  ap_int<17> v145 = txs_r;	// L207
  v7.write(v145);	// L208
  ap_int<17> v146 = txn_r;	// L209
  v8.write(v146);	// L210
  int8_t v147 = cre_r;	// L211
  v9.write(v147);	// L212
  int8_t v148 = crw_r;	// L213
  v10.write(v148);	// L214
  int8_t v149 = crs_r;	// L215
  v11.write(v149);	// L216
  int8_t v150 = crn_r;	// L217
  v12.write(v150);	// L218
  int32_t v151 = sc_r[0];	// L219
  v15.write(v151);	// L220
  int32_t v152 = sc_r[1];	// L221
  v16.write(v152);	// L222
  int32_t v153 = sc_r[2];	// L223
  v13.write(v153);	// L224
  int32_t v154 = sc_r[3];	// L225
  v14.write(v154);	// L226
  l_S_t_1_t: for (int t = 0; t < 120; t++) {	// L227
  #pragma HLS pipeline II=1
    ap_uint<26> v156 = v17.read();	// L228
    ap_uint<26> p_w;	// L229
    p_w = v156;	// L230
    ap_uint<26> v158 = v18.read();	// L231
    ap_uint<26> p_e;	// L232
    p_e = v158;	// L233
    ap_uint<26> v160 = v19.read();	// L234
    ap_uint<26> p_n;	// L235
    p_n = v160;	// L236
    ap_uint<26> v162 = v20.read();	// L237
    ap_uint<26> p_s;	// L238
    p_s = v162;	// L239
    int32_t v164 = v21.read();	// L240
    uint8_t v165 = rcred[0];	// L241
    ap_int<33> v166 = v165;	// L242
    ap_int<33> v167 = v164;	// L243
    ap_int<33> v168 = v166 + v167;	// L244
    uint8_t v169 = v168;	// L245
    rcred[0] = v169;	// L246
    int32_t v170 = v22.read();	// L247
    uint8_t v171 = rcred[1];	// L248
    ap_int<33> v172 = v171;	// L249
    ap_int<33> v173 = v170;	// L250
    ap_int<33> v174 = v172 + v173;	// L251
    uint8_t v175 = v174;	// L252
    rcred[1] = v175;	// L253
    int32_t v176 = v23.read();	// L254
    uint8_t v177 = rcred[2];	// L255
    ap_int<33> v178 = v177;	// L256
    ap_int<33> v179 = v176;	// L257
    ap_int<33> v180 = v178 + v179;	// L258
    uint8_t v181 = v180;	// L259
    rcred[2] = v181;	// L260
    int32_t v182 = v24.read();	// L261
    uint8_t v183 = rcred[3];	// L262
    ap_int<33> v184 = v183;	// L263
    ap_int<33> v185 = v182;	// L264
    ap_int<33> v186 = v184 + v185;	// L265
    uint8_t v187 = v186;	// L266
    rcred[3] = v187;	// L267
    int32_t v188 = v25.read();	// L268
    int32_t v189 = scred[0];	// L269
    ap_int<33> v190 = v189;	// L270
    ap_int<33> v191 = v188;	// L271
    ap_int<33> v192 = v190 + v191;	// L272
    int32_t v193 = v192;	// L273
    scred[0] = v193;	// L274
    int32_t v194 = v26.read();	// L275
    int32_t v195 = scred[1];	// L276
    ap_int<33> v196 = v195;	// L277
    ap_int<33> v197 = v194;	// L278
    ap_int<33> v198 = v196 + v197;	// L279
    int32_t v199 = v198;	// L280
    scred[1] = v199;	// L281
    int32_t v200 = v27.read();	// L282
    int32_t v201 = scred[2];	// L283
    ap_int<33> v202 = v201;	// L284
    ap_int<33> v203 = v200;	// L285
    ap_int<33> v204 = v202 + v203;	// L286
    int32_t v205 = v204;	// L287
    scred[2] = v205;	// L288
    int32_t v206 = v28.read();	// L289
    int32_t v207 = scred[3];	// L290
    ap_int<33> v208 = v207;	// L291
    ap_int<33> v209 = v206;	// L292
    ap_int<33> v210 = v208 + v209;	// L293
    int32_t v211 = v210;	// L294
    scred[3] = v211;	// L295
    ap_uint<26> fin[4];	// L296
    for (int v213 = 0; v213 < 4; v213++) {	// L297
      fin[v213] = 0;	// L297
    }
    ap_int<26> v214 = p_w;	// L298
    fin[0] = v214;	// L299
    ap_int<26> v215 = p_e;	// L300
    fin[1] = v215;	// L301
    ap_int<26> v216 = p_n;	// L302
    fin[2] = v216;	// L303
    ap_int<26> v217 = p_s;	// L304
    fin[3] = v217;	// L305
    l_S_d_1_d: for (int d = 0; d < 4; d++) {	// L306
      ap_uint<26> v219 = fin[d];	// L307
      bool v220;
      ap_int<26> v220_tmp = v219;
      v220 = v220_tmp[25];	// L308
      int32_t v221 = v220;	// L309
      bool v222 = v221 == 1;	// L310
      uint8_t v223 = rbcnt[d];	// L311
      int32_t v224 = v223;	// L312
      bool v225 = v224 < 2;	// L313
      bool v226 = v222 & v225;	// L314
      if (v226) {	// L315
        ap_uint<26> v227 = fin[d];	// L316
        uint8_t v228 = rbcnt[d];	// L317
        int v229 = v228;	// L318
        rbuf[d][v229] = v227;	// L319
        uint8_t v230 = rbcnt[d];	// L320
        ap_int<33> v231 = v230;	// L321
        ap_int<33> v232 = v231 + 1;	// L322
        uint8_t v233 = v232;	// L323
        rbcnt[d] = v233;	// L324
      }
    }
    ap_uint<26> hd[4];	// L327
    for (int v235 = 0; v235 < 4; v235++) {	// L328
      hd[v235] = 0;	// L328
    }
    int32_t hvld[4];	// L329
    for (int v237 = 0; v237 < 4; v237++) {	// L330
      hvld[v237] = 0;	// L330
    }
    int32_t hit[4];	// L331
    for (int v239 = 0; v239 < 4; v239++) {	// L332
      hit[v239] = 0;	// L332
    }
    int32_t axis[4];	// L333
    for (int v241 = 0; v241 < 4; v241++) {	// L334
      axis[v241] = 0;	// L334
    }
    int32_t v242 = col_id;	// L335
    axis[0] = v242;	// L336
    int32_t v243 = col_id;	// L337
    axis[1] = v243;	// L338
    int32_t v244 = row_id;	// L339
    axis[2] = v244;	// L340
    int32_t v245 = row_id;	// L341
    axis[3] = v245;	// L342
    l_S_d_2_d1: for (int d1 = 0; d1 < 4; d1++) {	// L343
      uint8_t v247 = rbcnt[d1];	// L344
      int32_t v248 = v247;	// L345
      bool v249 = v248 > 0;	// L346
      if (v249) {	// L347
        ap_uint<26> v250 = rbuf[d1][0];	// L348
        hd[d1] = v250;	// L349
        hvld[d1] = 1;	// L350
        ap_uint<26> v251 = hd[d1];	// L351
        ap_int<4> v252;
        ap_int<26> v252_tmp = v251;
        v252 = v252_tmp(24, 21);	// L352
        int32_t v253 = axis[d1];	// L353
        int32_t v254 = v252;	// L354
        bool v255 = v254 == v253;	// L355
        if (v255) {	// L356
          hit[d1] = 1;	// L357
        }
      }
    }
    ap_uint<26> o_crv;	// L361
    o_crv = 0;	// L362
    int32_t crv_in;	// L363
    crv_in = -1;	// L364
    int32_t v258 = hit[3];	// L365
    bool v259 = v258 == 1;	// L366
    if (v259) {	// L367
      ap_uint<26> v260 = hd[3];	// L368
      o_crv = v260;	// L369
      crv_in = 3;	// L370
    } else {
      int32_t v261 = hit[2];	// L372
      bool v262 = v261 == 1;	// L373
      if (v262) {	// L374
        ap_uint<26> v263 = hd[2];	// L375
        o_crv = v263;	// L376
        crv_in = 2;	// L377
      } else {
        int32_t v264 = hit[1];	// L379
        bool v265 = v264 == 1;	// L380
        if (v265) {	// L381
          ap_uint<26> v266 = hd[1];	// L382
          o_crv = v266;	// L383
          crv_in = 1;	// L384
        } else {
          int32_t v267 = hit[0];	// L386
          bool v268 = v267 == 1;	// L387
          if (v268) {	// L388
            ap_uint<26> v269 = hd[0];	// L389
            o_crv = v269;	// L390
            crv_in = 0;	// L391
          }
        }
      }
    }
    ap_uint<26> o_out[4];	// L396
    for (int v271 = 0; v271 < 4; v271++) {	// L397
      o_out[v271] = 0;	// L397
    }
    int32_t pop[4];	// L398
    for (int v273 = 0; v273 < 4; v273++) {	// L399
      pop[v273] = 0;	// L399
    }
    int32_t inj_done;	// L400
    inj_done = 0;	// L401
    int32_t idir;	// L402
    idir = -1;	// L403
    ap_int<26> v276 = csd_pkt;	// L404
    bool v277;
    ap_int<26> v277_tmp = v276;
    v277 = v277_tmp[25];	// L405
    int32_t v278 = v277;	// L406
    bool v279 = v278 == 1;	// L407
    if (v279) {	// L408
      int32_t v280 = csd_dir;	// L409
      ap_int<33> v281 = v280;	// L410
      ap_int<33> v282 = 3 - v281;	// L411
      int32_t v283 = v282;	// L412
      idir = v283;	// L413
    }
    l_S_o_3_o: for (int o = 0; o < 4; o++) {	// L415
      uint8_t v285 = rcred[o];	// L416
      int32_t v286 = v285;	// L417
      bool v287 = v286 > 0;	// L418
      if (v287) {	// L419
        int32_t v288 = idir;	// L420
        ap_int<33> v289 = v288;	// L421
        ap_int<33> v290 = o;	// L422
        bool v291 = v289 == v290;	// L423
        if (v291) {	// L424
          ap_int<26> v292 = csd_pkt;	// L425
          o_out[o] = v292;	// L426
          uint8_t v293 = rcred[o];	// L427
          ap_int<33> v294 = v293;	// L428
          ap_int<33> v295 = v294 - 1;	// L429
          uint8_t v296 = v295;	// L430
          rcred[o] = v296;	// L431
          inj_done = 1;	// L432
        } else {
          int32_t v297 = hvld[o];	// L434
          bool v298 = v297 == 1;	// L435
          int32_t v299 = hit[o];	// L436
          bool v300 = v299 == 0;	// L437
          bool v301 = v298 & v300;	// L438
          if (v301) {	// L439
            ap_uint<26> v302 = hd[o];	// L440
            o_out[o] = v302;	// L441
            uint8_t v303 = rcred[o];	// L442
            ap_int<33> v304 = v303;	// L443
            ap_int<33> v305 = v304 - 1;	// L444
            uint8_t v306 = v305;	// L445
            rcred[o] = v306;	// L446
            pop[o] = 1;	// L447
          }
        }
      }
    }
    int32_t v307 = crv_in;	// L452
    bool v308 = v307 >= 0;	// L453
    if (v308) {	// L454
      int32_t v309 = crv_in;	// L455
      int v310 = v309;	// L456
      pop[v310] = 1;	// L457
    }
    int32_t ret[4];	// L459
    for (int v312 = 0; v312 < 4; v312++) {	// L460
      ret[v312] = 0;	// L460
    }
    l_S_d_4_d2: for (int d2 = 0; d2 < 4; d2++) {	// L461
      int32_t v314 = pop[d2];	// L462
      bool v315 = v314 == 1;	// L463
      if (v315) {	// L464
        l_S_sft_4_sft: for (int sft = 0; sft < 1; sft++) {	// L465
          ap_uint<26> v317 = rbuf[d2][(sft + 1)];	// L466
          rbuf[d2][sft] = v317;	// L467
        }
        uint8_t v318 = rbcnt[d2];	// L469
        ap_int<33> v319 = v318;	// L470
        ap_int<33> v320 = v319 - 1;	// L471
        uint8_t v321 = v320;	// L472
        rbcnt[d2] = v321;	// L473
        ret[d2] = 1;	// L474
      }
    }
    int32_t v322 = ret[0];	// L477
    uint8_t v323 = v322;	// L478
    cre_r = v323;	// L479
    int32_t v324 = ret[1];	// L480
    uint8_t v325 = v324;	// L481
    crw_r = v325;	// L482
    int32_t v326 = ret[2];	// L483
    uint8_t v327 = v326;	// L484
    crs_r = v327;	// L485
    int32_t v328 = ret[3];	// L486
    uint8_t v329 = v328;	// L487
    crn_r = v329;	// L488
    ap_uint<26> v330 = o_out[0];	// L489
    oe_r = v330;	// L490
    ap_uint<26> v331 = o_out[1];	// L491
    ow_r = v331;	// L492
    ap_uint<26> v332 = o_out[2];	// L493
    os_r = v332;	// L494
    ap_uint<26> v333 = o_out[3];	// L495
    on_r = v333;	// L496
    int32_t v334 = inj_done;	// L497
    bool v335 = v334 == 1;	// L498
    if (v335) {	// L499
      csd_pkt = 0;	// L500
    }
    ap_int<26> v336 = o_crv;	// L502
    bool v337;
    ap_int<26> v337_tmp = v336;
    v337 = v337_tmp[25];	// L503
    int32_t v338 = v337;	// L504
    crv_vld = v338;	// L505
    ap_int<26> v339 = o_crv;	// L506
    int16_t v340;
    ap_int<26> v340_tmp = v339;
    v340 = v340_tmp(15, 0);	// L507
    half v341;
    union { uint16_t from; half to;} _converter_v340_to_v341 = {};
    _converter_v340_to_v341.from = v340;
    v341 = _converter_v340_to_v341.to;	// L508
    crv_data = v341;	// L509
    ap_int<26> v342 = o_crv;	// L510
    ap_int<4> v343;
    ap_int<26> v343_tmp = v342;
    v343 = v343_tmp(19, 16);	// L511
    int32_t v344 = v343;	// L512
    crv_addr = v344;	// L513
    ap_int<26> v345 = o_crv;	// L514
    bool v346;
    ap_int<26> v346_tmp = v345;
    v346 = v346_tmp[20];	// L515
    int32_t v347 = v346;	// L516
    crv_mode = v347;	// L517
    ap_int<26> v348 = o_crv;	// L518
    int16_t v349;
    ap_int<26> v349_tmp = v348;
    v349 = v349_tmp(15, 0);	// L519
    int32_t v350 = v349;	// L520
    crv_raw = v350;	// L521
    ap_uint<17> v351 = v29.read();	// L522
    ap_uint<17> rx_w;	// L523
    rx_w = v351;	// L524
    ap_uint<17> v353 = v30.read();	// L525
    ap_uint<17> rx_e;	// L526
    rx_e = v353;	// L527
    ap_uint<17> v355 = v31.read();	// L528
    ap_uint<17> rx_n;	// L529
    rx_n = v355;	// L530
    ap_uint<17> v357 = v32.read();	// L531
    ap_uint<17> rx_s;	// L532
    rx_s = v357;	// L533
    half rxv[4];	// L534
    for (int v360 = 0; v360 < 4; v360++) {	// L535
      rxv[v360] = 0.000000;	// L535
    }
    int32_t rxvld[4];	// L536
    for (int v362 = 0; v362 < 4; v362++) {	// L537
      rxvld[v362] = 0;	// L537
    }
    ap_int<17> v363 = rx_n;	// L538
    int16_t v364;
    ap_int<17> v364_tmp = v363;
    v364 = v364_tmp(16, 1);	// L539
    half v365;
    union { uint16_t from; half to;} _converter_v364_to_v365 = {};
    _converter_v364_to_v365.from = v364;
    v365 = _converter_v364_to_v365.to;	// L540
    rxv[0] = v365;	// L541
    ap_int<17> v366 = rx_n;	// L542
    bool v367;
    ap_int<17> v367_tmp = v366;
    v367 = v367_tmp[0];	// L543
    int32_t v368 = v367;	// L544
    rxvld[0] = v368;	// L545
    ap_int<17> v369 = rx_s;	// L546
    int16_t v370;
    ap_int<17> v370_tmp = v369;
    v370 = v370_tmp(16, 1);	// L547
    half v371;
    union { uint16_t from; half to;} _converter_v370_to_v371 = {};
    _converter_v370_to_v371.from = v370;
    v371 = _converter_v370_to_v371.to;	// L548
    rxv[1] = v371;	// L549
    ap_int<17> v372 = rx_s;	// L550
    bool v373;
    ap_int<17> v373_tmp = v372;
    v373 = v373_tmp[0];	// L551
    int32_t v374 = v373;	// L552
    rxvld[1] = v374;	// L553
    ap_int<17> v375 = rx_w;	// L554
    int16_t v376;
    ap_int<17> v376_tmp = v375;
    v376 = v376_tmp(16, 1);	// L555
    half v377;
    union { uint16_t from; half to;} _converter_v376_to_v377 = {};
    _converter_v376_to_v377.from = v376;
    v377 = _converter_v376_to_v377.to;	// L556
    rxv[2] = v377;	// L557
    ap_int<17> v378 = rx_w;	// L558
    bool v379;
    ap_int<17> v379_tmp = v378;
    v379 = v379_tmp[0];	// L559
    int32_t v380 = v379;	// L560
    rxvld[2] = v380;	// L561
    ap_int<17> v381 = rx_e;	// L562
    int16_t v382;
    ap_int<17> v382_tmp = v381;
    v382 = v382_tmp(16, 1);	// L563
    half v383;
    union { uint16_t from; half to;} _converter_v382_to_v383 = {};
    _converter_v382_to_v383.from = v382;
    v383 = _converter_v382_to_v383.to;	// L564
    rxv[3] = v383;	// L565
    ap_int<17> v384 = rx_e;	// L566
    bool v385;
    ap_int<17> v385_tmp = v384;
    v385 = v385_tmp[0];	// L567
    int32_t v386 = v385;	// L568
    rxvld[3] = v386;	// L569
    l_S_d_6_d3: for (int d3 = 0; d3 < 4; d3++) {	// L570
      int32_t v388 = rxvld[d3];	// L571
      bool v389 = v388 == 1;	// L572
      uint8_t v390 = hold_cnt[d3];	// L573
      int32_t v391 = v390;	// L574
      bool v392 = v391 < 2;	// L575
      bool v393 = v389 & v392;	// L576
      if (v393) {	// L577
        half v394 = rxv[d3];	// L578
        uint8_t v395 = hold_cnt[d3];	// L579
        int v396 = v395;	// L580
        hold_v[d3][v396] = v394;	// L581
        uint8_t v397 = hold_cnt[d3];	// L582
        ap_int<33> v398 = v397;	// L583
        ap_int<33> v399 = v398 + 1;	// L584
        uint8_t v400 = v399;	// L585
        hold_cnt[d3] = v400;	// L586
      }
    }
    int32_t retire_ok;	// L589
    retire_ok = 1;	// L590
    uint8_t v402 = sb_v[0];	// L591
    int32_t v403 = v402;	// L592
    bool v404 = v403 == 1;	// L593
    uint8_t v405 = sb_rtr[0];	// L594
    int32_t v406 = v405;	// L595
    bool v407 = v406 == 0;	// L596
    uint8_t v408 = sb_dst[0];	// L597
    int32_t v409 = v408;	// L598
    bool v410 = v409 >= 12;	// L599
    bool v411 = v404 & v407;	// L600
    bool v412 = v411 & v410;	// L601
    if (v412) {	// L602
      uint8_t v413 = sb_rvld[0];	// L603
      int32_t v414 = v413;	// L604
      bool v415 = v414 == 1;	// L605
      uint8_t v416 = sb_dst[0];	// L606
      int32_t v417 = v416;	// L607
      int32_t v418 = v417 & 3;	// L608
      int v419 = v418;	// L609
      int32_t v420 = txp_v[v419];	// L610
      bool v421 = v420 == 1;	// L611
      bool v422 = v415 & v421;	// L612
      if (v422) {	// L613
        retire_ok = 0;	// L614
      }
    }
    uint8_t v423 = sb_v[0];	// L617
    int32_t v424 = v423;	// L618
    bool v425 = v424 == 1;	// L619
    int32_t v426 = retire_ok;	// L620
    bool v427 = v426 == 1;	// L621
    bool v428 = v425 & v427;	// L622
    if (v428) {	// L623
      uint8_t v429 = sb_ix[0];	// L624
      int v430 = v429;	// L625
      half v431 = resq[v430];	// L626
      half wb;
#pragma HLS dependence variable=wb type=inter dependent=false	// L627
      wb = v431;	// L628
      uint8_t v433 = sb_cmp[0];	// L629
      int32_t v434 = v433;	// L630
      bool v435 = v434 == 1;	// L631
      if (v435) {	// L632
        uint8_t v436 = sb_ix[0];	// L633
        int v437 = v436;	// L634
        uint8_t v438 = cmpq[v437];	// L635
        condition_reg = v438;	// L636
      }
      uint8_t v439 = sb_rtr[0];	// L638
      int32_t v440 = v439;	// L639
      bool v441 = v440 == 1;	// L640
      if (v441) {	// L641
        uint8_t v442 = sb_inj[0];	// L642
        int32_t v443 = v442;	// L643
        bool v444 = v443 == 1;	// L644
        ap_int<26> v445 = csd_pkt;	// L645
        bool v446;
        ap_int<26> v446_tmp = v445;
        v446 = v446_tmp[25];	// L646
        int32_t v447 = v446;	// L647
        bool v448 = v447 == 0;	// L648
        bool v449 = v444 & v448;	// L649
        if (v449) {	// L650
          half v450 = wb;	// L651
          uint16_t v451;
          union { half from; uint16_t to;} _converter_v450_to_v451 = {};
          _converter_v450_to_v451.from = v450;
          v451 = _converter_v450_to_v451.to;	// L652
          ap_int<26> v452 = csd_pkt;	// L653
          ap_int<26> v453;
          ap_int<26> v453_tmp = v452;
          v453_tmp(15, 0) = v451;
          v453 = v453_tmp;	// L654
          csd_pkt = v453;	// L655
          uint8_t v454 = sb_dst[0];	// L656
          ap_uint<4> v455 = v454;	// L657
          ap_int<26> v456 = csd_pkt;	// L658
          ap_int<26> v457;
          ap_int<26> v457_tmp = v456;
          v457_tmp(19, 16) = v455;
          v457 = v457_tmp;	// L659
          csd_pkt = v457;	// L660
          uint8_t v458 = sb_id[0];	// L661
          ap_uint<4> v459 = v458;	// L662
          ap_int<26> v460 = csd_pkt;	// L663
          ap_int<26> v461;
          ap_int<26> v461_tmp = v460;
          v461_tmp(24, 21) = v459;
          v461 = v461_tmp;	// L664
          csd_pkt = v461;	// L665
          uint8_t v462 = sb_rvld[0];	// L666
          bool v463 = v462;	// L667
          ap_int<26> v464 = csd_pkt;	// L668
          ap_int<26> v465;
          ap_int<26> v465_tmp = v464;
          v465_tmp[25] = v463;          v465 = v465_tmp;	// L669
          csd_pkt = v465;	// L670
          uint8_t v466 = sb_dir[0];	// L671
          int32_t v467 = v466;	// L672
          csd_dir = v467;	// L673
        }
      } else {
        uint8_t v468 = sb_dst[0];	// L676
        int32_t v469 = v468;	// L677
        bool v470 = v469 >= 12;	// L678
        if (v470) {	// L679
          uint8_t v471 = sb_rvld[0];	// L680
          int32_t v472 = v471;	// L681
          bool v473 = v472 == 1;	// L682
          if (v473) {	// L683
            uint8_t v474 = sb_dst[0];	// L684
            int32_t v475 = v474;	// L685
            int32_t v476 = v475 & 3;	// L686
            int v477 = v476;	// L687
            txp_v[v477] = 1;	// L688
            half v478 = wb;	// L689
            uint8_t v479 = sb_dst[0];	// L690
            int32_t v480 = v479;	// L691
            int32_t v481 = v480 & 3;	// L692
            int v482 = v481;	// L693
            txp_d[v482] = v478;	// L694
            uint8_t v483 = sb_dst[0];	// L695
            int32_t v484 = v483;	// L696
            int32_t v485 = v484 & 3;	// L697
            int v486 = v485;	// L698
            txp_r[v486] = 1;	// L699
          }
        } else {
          uint8_t v487 = sb_rvld[0];	// L702
          int32_t v488 = v487;	// L703
          bool v489 = v488 == 1;	// L704
          if (v489) {	// L705
            uint8_t v490 = sb_dst[0];	// L706
            int32_t v491 = v490;	// L707
            bool v492 = v491 < 8;	// L708
            int32_t v493 = dsmask;	// L709
            int32_t v494 = v493 >> v491;	// L710
            int32_t v495 = v494 & 1;	// L711
            bool v496 = v495 == 1;	// L712
            bool v497 = v492 & v496;	// L713
            if (v497) {	// L714
              uint8_t v498 = sb_dst[0];	// L715
              int v499 = v498;	// L716
              int32_t v500 = drf_full[v499];	// L717
              bool v501 = v500 == 0;	// L718
              if (v501) {	// L719
                half v502 = wb;	// L720
                uint8_t v503 = sb_dst[0];	// L721
                int v504 = v503;	// L722
                drf[v504] = v502;	// L723
                uint8_t v505 = sb_dst[0];	// L724
                int v506 = v505;	// L725
                drf_full[v506] = 1;	// L726
              }
            } else {
              half v507 = wb;	// L729
              uint8_t v508 = sb_dst[0];	// L730
              int32_t v509 = v508;	// L731
              int32_t v510 = v509 & 7;	// L732
              int v511 = v510;	// L733
              drf[v511] = v507;	// L734
            }
          }
        }
      }
    }
    int32_t pc;	// L740
    pc = -1;	// L741
    int8_t v513 = fetch_en;	// L742
    int32_t v514 = v513;	// L743
    bool v515 = v514 == 1;	// L744
    if (v515) {	// L745
      int8_t v516 = instr_cnt;	// L746
      int32_t v517 = v516;	// L747
      pc = v517;	// L748
    }
    int32_t instr;	// L750
    instr = 0;	// L751
    int32_t v519 = pc;	// L752
    bool v520 = v519 >= 0;	// L753
    if (v520) {	// L754
      int32_t v521 = pc;	// L755
      int v522 = v521;	// L756
      int32_t v523 = irf[v522];	// L757
      instr = v523;	// L758
    }
    int32_t v524 = instr;	// L760
    int32_t v525 = v524 & 15;	// L761
    int32_t op;	// L762
    op = v525;	// L763
    int32_t v527 = instr;	// L764
    int32_t v528 = v527 >> 4;	// L765
    int32_t v529 = v528 & 15;	// L766
    int32_t dst;	// L767
    dst = v529;	// L768
    int32_t v531 = instr;	// L769
    int32_t v532 = v531 >> 8;	// L770
    int32_t v533 = v532 & 15;	// L771
    int32_t s1;	// L772
    s1 = v533;	// L773
    int32_t v535 = instr;	// L774
    int32_t v536 = v535 >> 12;	// L775
    int32_t v537 = v536 & 15;	// L776
    int32_t s2;	// L777
    s2 = v537;	// L778
    half a;	// L779
    a = 0.000000;	// L780
    half b;	// L781
    b = 0.000000;	// L782
    int32_t v541 = s1;	// L783
    bool v542 = v541 >= 12;	// L784
    if (v542) {	// L785
      int32_t v543 = s1;	// L786
      int32_t v544 = v543 & 3;	// L787
      int v545 = v544;	// L788
      half v546 = hold_v[v545][0];	// L789
      a = v546;	// L790
    } else {
      int32_t v547 = s1;	// L792
      int v548 = v547;	// L793
      half v549 = drf[v548];	// L794
      a = v549;	// L795
    }
    int32_t v550 = s2;	// L797
    bool v551 = v550 >= 12;	// L798
    if (v551) {	// L799
      int32_t v552 = s2;	// L800
      int32_t v553 = v552 & 3;	// L801
      int v554 = v553;	// L802
      half v555 = hold_v[v554][0];	// L803
      b = v555;	// L804
    } else {
      int32_t v556 = s2;	// L806
      int v557 = v556;	// L807
      half v558 = drf[v557];	// L808
      b = v558;	// L809
    }
    int32_t a_vld;	// L811
    a_vld = 1;	// L812
    int32_t b_vld;	// L813
    b_vld = 1;	// L814
    int32_t v561 = s1;	// L815
    bool v562 = v561 >= 12;	// L816
    if (v562) {	// L817
      a_vld = 0;	// L818
      int32_t v563 = s1;	// L819
      int32_t v564 = v563 & 3;	// L820
      int v565 = v564;	// L821
      uint8_t v566 = hold_cnt[v565];	// L822
      int32_t v567 = v566;	// L823
      bool v568 = v567 > 0;	// L824
      if (v568) {	// L825
        a_vld = 1;	// L826
      }
    }
    int32_t v569 = s2;	// L829
    bool v570 = v569 >= 12;	// L830
    if (v570) {	// L831
      b_vld = 0;	// L832
      int32_t v571 = s2;	// L833
      int32_t v572 = v571 & 3;	// L834
      int v573 = v572;	// L835
      uint8_t v574 = hold_cnt[v573];	// L836
      int32_t v575 = v574;	// L837
      bool v576 = v575 > 0;	// L838
      if (v576) {	// L839
        b_vld = 1;	// L840
      }
    }
    int32_t v577 = s1;	// L843
    bool v578 = v577 < 8;	// L844
    int32_t v579 = dsmask;	// L845
    int32_t v580 = v579 >> v577;	// L846
    int32_t v581 = v580 & 1;	// L847
    bool v582 = v581 == 1;	// L848
    bool v583 = v578 & v582;	// L849
    if (v583) {	// L850
      int32_t v584 = s1;	// L851
      int v585 = v584;	// L852
      int32_t v586 = drf_full[v585];	// L853
      bool v587 = v586 == 0;	// L854
      if (v587) {	// L855
        a_vld = 0;	// L856
      }
    }
    int32_t v588 = s2;	// L859
    bool v589 = v588 < 8;	// L860
    int32_t v590 = dsmask;	// L861
    int32_t v591 = v590 >> v588;	// L862
    int32_t v592 = v591 & 1;	// L863
    bool v593 = v592 == 1;	// L864
    bool v594 = v589 & v593;	// L865
    if (v594) {	// L866
      int32_t v595 = s2;	// L867
      int v596 = v595;	// L868
      int32_t v597 = drf_full[v596];	// L869
      bool v598 = v597 == 0;	// L870
      if (v598) {	// L871
        b_vld = 0;	// L872
      }
    }
    int32_t binop;	// L875
    binop = 0;	// L876
    int32_t v600 = op;	// L877
    bool v601 = v600 == 0;	// L878
    bool v602 = v600 == 1;	// L879
    bool v603 = v600 == 2;	// L880
    bool v604 = v600 == 8;	// L881
    bool v605 = v600 == 9;	// L882
    bool v606 = v601 | v602;	// L883
    bool v607 = v606 | v603;	// L884
    bool v608 = v607 | v604;	// L885
    bool v609 = v608 | v605;	// L886
    if (v609) {	// L887
      binop = 1;	// L888
    }
    int32_t raw;	// L890
    raw = 0;	// L891
    int32_t cmp_busy;	// L892
    cmp_busy = 0;	// L893
    int32_t fwd_a;	// L894
    fwd_a = 0;	// L895
    int32_t fwd_a_ix;	// L896
    fwd_a_ix = 0;	// L897
    int32_t raw_a;	// L898
    raw_a = 0;	// L899
    int32_t fwd_b;	// L900
    fwd_b = 0;	// L901
    int32_t fwd_b_ix;	// L902
    fwd_b_ix = 0;	// L903
    int32_t raw_b;	// L904
    raw_b = 0;	// L905
    l_S_k_7_k: for (int k = 0; k < 4; k++) {	// L906
      ap_int<34> v619 = k;	// L907
      ap_int<34> v620 = v619 + 1;	// L908
      int32_t v621 = v620;	// L909
      int32_t kk;	// L910
      kk = v621;	// L911
      int32_t v623 = kk;	// L912
      ap_int<34> v624 = v623;	// L913
      ap_int<34> v625 = 4 - v624;	// L914
      int32_t v626 = v625;	// L915
      int32_t inflight;	// L916
      inflight = v626;	// L917
      int32_t need;	// L918
      need = 0;	// L919
      int32_t v629 = kk;	// L920
      int v630 = v629;	// L921
      uint8_t v631 = sb_long[v630];	// L922
      int32_t v632 = v631;	// L923
      bool v633 = v632 == 1;	// L924
      if (v633) {	// L925
        need = 3;	// L926
      }
      int32_t rdy;	// L928
      rdy = 0;	// L929
      int32_t v635 = inflight;	// L930
      int32_t v636 = need;	// L931
      bool v637 = v635 >= v636;	// L932
      if (v637) {	// L933
        rdy = 1;	// L934
      }
      int32_t v638 = kk;	// L936
      int v639 = v638;	// L937
      uint8_t v640 = sb_v[v639];	// L938
      int32_t v641 = v640;	// L939
      bool v642 = v641 == 1;	// L940
      uint8_t v643 = sb_rtr[v639];	// L941
      int32_t v644 = v643;	// L942
      bool v645 = v644 == 0;	// L943
      uint8_t v646 = sb_dst[v639];	// L944
      int32_t v647 = v646;	// L945
      bool v648 = v647 < 12;	// L946
      bool v649 = v642 & v645;	// L947
      bool v650 = v649 & v648;	// L948
      if (v650) {	// L949
        int32_t v651 = s1;	// L950
        bool v652 = v651 < 12;	// L951
        int32_t v653 = kk;	// L952
        int v654 = v653;	// L953
        uint8_t v655 = sb_dst[v654];	// L954
        int32_t v656 = v655;	// L955
        int32_t v657 = v656 & 7;	// L956
        int32_t v658 = v651 & 7;	// L957
        bool v659 = v657 == v658;	// L958
        bool v660 = v652 & v659;	// L959
        if (v660) {	// L960
          int32_t v661 = rdy;	// L961
          bool v662 = v661 == 1;	// L962
          if (v662) {	// L963
            fwd_a = 1;	// L964
            int32_t v663 = kk;	// L965
            int v664 = v663;	// L966
            uint8_t v665 = sb_ix[v664];	// L967
            int32_t v666 = v665;	// L968
            fwd_a_ix = v666;	// L969
            raw_a = 0;	// L970
          } else {
            fwd_a = 0;	// L972
            raw_a = 1;	// L973
          }
        }
        int32_t v667 = binop;	// L976
        bool v668 = v667 == 1;	// L977
        int32_t v669 = s2;	// L978
        bool v670 = v669 < 12;	// L979
        int32_t v671 = kk;	// L980
        int v672 = v671;	// L981
        uint8_t v673 = sb_dst[v672];	// L982
        int32_t v674 = v673;	// L983
        int32_t v675 = v674 & 7;	// L984
        int32_t v676 = v669 & 7;	// L985
        bool v677 = v675 == v676;	// L986
        bool v678 = v668 & v670;	// L987
        bool v679 = v678 & v677;	// L988
        if (v679) {	// L989
          int32_t v680 = rdy;	// L990
          bool v681 = v680 == 1;	// L991
          if (v681) {	// L992
            fwd_b = 1;	// L993
            int32_t v682 = kk;	// L994
            int v683 = v682;	// L995
            uint8_t v684 = sb_ix[v683];	// L996
            int32_t v685 = v684;	// L997
            fwd_b_ix = v685;	// L998
            raw_b = 0;	// L999
          } else {
            fwd_b = 0;	// L1001
            raw_b = 1;	// L1002
          }
        }
      }
      int32_t v686 = kk;	// L1006
      int v687 = v686;	// L1007
      uint8_t v688 = sb_v[v687];	// L1008
      int32_t v689 = v688;	// L1009
      bool v690 = v689 == 1;	// L1010
      uint8_t v691 = sb_cmp[v687];	// L1011
      int32_t v692 = v691;	// L1012
      bool v693 = v692 == 1;	// L1013
      bool v694 = v690 & v693;	// L1014
      if (v694) {	// L1015
        cmp_busy = 1;	// L1016
      }
    }
    int32_t v695 = raw_a;	// L1019
    raw = v695;	// L1020
    int32_t v696 = binop;	// L1021
    bool v697 = v696 == 1;	// L1022
    int32_t v698 = raw_b;	// L1023
    bool v699 = v698 == 1;	// L1024
    bool v700 = v697 & v699;	// L1025
    if (v700) {	// L1026
      raw = 1;	// L1027
    }
    int32_t v701 = fwd_a;	// L1029
    bool v702 = v701 == 1;	// L1030
    if (v702) {	// L1031
      int32_t v703 = fwd_a_ix;	// L1032
      int v704 = v703;	// L1033
      half v705 = resq[v704];	// L1034
      a = v705;	// L1035
      a_vld = 1;	// L1036
    }
    int32_t v706 = fwd_b;	// L1038
    bool v707 = v706 == 1;	// L1039
    if (v707) {	// L1040
      int32_t v708 = fwd_b_ix;	// L1041
      int v709 = v708;	// L1042
      half v710 = resq[v709];	// L1043
      b = v710;	// L1044
      b_vld = 1;	// L1045
    }
    int32_t is_cond;	// L1047
    is_cond = 0;	// L1048
    int32_t v712 = op;	// L1049
    bool v713 = v712 >= 12;	// L1050
    ap_int<33> v714 = v712;	// L1051
    bool v715 = v714 <= 15;	// L1052
    bool v716 = v713 & v715;	// L1053
    if (v716) {	// L1054
      is_cond = 1;	// L1055
    }
    int32_t grant;	// L1057
    grant = 0;	// L1058
    int32_t v718 = pc;	// L1059
    bool v719 = v718 >= 0;	// L1060
    if (v719) {	// L1061
      grant = 1;	// L1062
    }
    int32_t v720 = pc;	// L1064
    bool v721 = v720 >= 0;	// L1065
    int32_t v722 = a_vld;	// L1066
    bool v723 = v722 == 0;	// L1067
    int32_t v724 = binop;	// L1068
    bool v725 = v724 == 1;	// L1069
    int32_t v726 = b_vld;	// L1070
    bool v727 = v726 == 0;	// L1071
    bool v728 = v725 & v727;	// L1072
    bool v729 = v723 | v728;	// L1073
    bool v730 = v721 & v729;	// L1074
    if (v730) {	// L1075
      grant = 0;	// L1076
    }
    int32_t v731 = pc;	// L1078
    bool v732 = v731 >= 0;	// L1079
    int32_t v733 = raw;	// L1080
    bool v734 = v733 == 1;	// L1081
    int32_t v735 = is_cond;	// L1082
    bool v736 = v735 == 1;	// L1083
    int32_t v737 = cmp_busy;	// L1084
    bool v738 = v737 == 1;	// L1085
    bool v739 = v736 & v738;	// L1086
    bool v740 = v734 | v739;	// L1087
    bool v741 = v732 & v740;	// L1088
    if (v741) {	// L1089
      grant = 0;	// L1090
    }
    int32_t v742 = retire_ok;	// L1092
    bool v743 = v742 == 0;	// L1093
    if (v743) {	// L1094
      grant = 0;	// L1095
    }
    int32_t v744 = grant;	// L1097
    bool v745 = v744 == 1;	// L1098
    if (v745) {	// L1099
      int8_t v746 = instr_cnt;	// L1100
      int32_t v747 = cfg_isz;	// L1101
      int32_t v748 = v746;	// L1102
      bool v749 = v748 == v747;	// L1103
      if (v749) {	// L1104
        instr_cnt = 0;	// L1105
        int8_t v750 = iter_cnt;	// L1106
        int32_t v751 = cfg_itsz;	// L1107
        ap_int<33> v752 = v751;	// L1108
        ap_int<33> v753 = v752 - 1;	// L1109
        ap_int<33> v754 = v750;	// L1110
        bool v755 = v754 == v753;	// L1111
        if (v755) {	// L1112
          fetch_en = 0;	// L1113
        } else {
          int8_t v756 = iter_cnt;	// L1115
          ap_int<33> v757 = v756;	// L1116
          ap_int<33> v758 = v757 + 1;	// L1117
          uint8_t v759 = v758;	// L1118
          iter_cnt = v759;	// L1119
        }
      } else {
        int8_t v760 = instr_cnt;	// L1122
        ap_int<33> v761 = v760;	// L1123
        ap_int<33> v762 = v761 + 1;	// L1124
        uint8_t v763 = v762;	// L1125
        instr_cnt = v763;	// L1126
      }
    }
    int32_t c1;	// L1129
    c1 = -1;	// L1130
    int32_t c2;	// L1131
    c2 = -1;	// L1132
    int32_t v766 = grant;	// L1133
    bool v767 = v766 == 1;	// L1134
    int32_t v768 = s1;	// L1135
    bool v769 = v768 >= 12;	// L1136
    bool v770 = v767 & v769;	// L1137
    if (v770) {	// L1138
      int32_t v771 = s1;	// L1139
      int32_t v772 = v771 & 3;	// L1140
      c1 = v772;	// L1141
    }
    int32_t v773 = grant;	// L1143
    bool v774 = v773 == 1;	// L1144
    int32_t v775 = s2;	// L1145
    bool v776 = v775 >= 12;	// L1146
    bool v777 = v774 & v776;	// L1147
    if (v777) {	// L1148
      int32_t v778 = s2;	// L1149
      int32_t v779 = v778 & 3;	// L1150
      c2 = v779;	// L1151
    }
    int32_t v780 = c1;	// L1153
    bool v781 = v780 >= 0;	// L1154
    if (v781) {	// L1155
      int32_t v782 = c1;	// L1156
      int v783 = v782;	// L1157
      half v784 = hold_v[v783][1];	// L1158
      hold_v[v783][0] = v784;	// L1159
      int32_t v785 = c1;	// L1160
      int v786 = v785;	// L1161
      uint8_t v787 = hold_cnt[v786];	// L1162
      ap_int<33> v788 = v787;	// L1163
      ap_int<33> v789 = v788 - 1;	// L1164
      uint8_t v790 = v789;	// L1165
      hold_cnt[v786] = v790;	// L1166
    }
    int32_t v791 = c2;	// L1168
    bool v792 = v791 >= 0;	// L1169
    int32_t v793 = c1;	// L1170
    bool v794 = v791 != v793;	// L1171
    bool v795 = v792 & v794;	// L1172
    if (v795) {	// L1173
      int32_t v796 = c2;	// L1174
      int v797 = v796;	// L1175
      half v798 = hold_v[v797][1];	// L1176
      hold_v[v797][0] = v798;	// L1177
      int32_t v799 = c2;	// L1178
      int v800 = v799;	// L1179
      uint8_t v801 = hold_cnt[v800];	// L1180
      ap_int<33> v802 = v801;	// L1181
      ap_int<33> v803 = v802 - 1;	// L1182
      uint8_t v804 = v803;	// L1183
      hold_cnt[v800] = v804;	// L1184
    }
    l_S_d_8_d4: for (int d4 = 0; d4 < 4; d4++) {	// L1186
      sc_r[d4] = 0;	// L1187
    }
    int32_t v806 = c1;	// L1189
    bool v807 = v806 >= 0;	// L1190
    if (v807) {	// L1191
      int32_t v808 = c1;	// L1192
      int v809 = v808;	// L1193
      sc_r[v809] = 1;	// L1194
    }
    int32_t v810 = c2;	// L1196
    bool v811 = v810 >= 0;	// L1197
    int32_t v812 = c1;	// L1198
    bool v813 = v810 != v812;	// L1199
    bool v814 = v811 & v813;	// L1200
    if (v814) {	// L1201
      int32_t v815 = c2;	// L1202
      int v816 = v815;	// L1203
      sc_r[v816] = 1;	// L1204
    }
    int32_t v817 = grant;	// L1206
    bool v818 = v817 == 1;	// L1207
    int32_t v819 = s1;	// L1208
    bool v820 = v819 < 8;	// L1209
    int32_t v821 = dsmask;	// L1210
    int32_t v822 = v821 >> v819;	// L1211
    int32_t v823 = v822 & 1;	// L1212
    bool v824 = v823 == 1;	// L1213
    bool v825 = v818 & v820;	// L1214
    bool v826 = v825 & v824;	// L1215
    if (v826) {	// L1216
      int32_t v827 = s1;	// L1217
      int v828 = v827;	// L1218
      drf_full[v828] = 0;	// L1219
    }
    int32_t v829 = grant;	// L1221
    bool v830 = v829 == 1;	// L1222
    int32_t v831 = s2;	// L1223
    bool v832 = v831 < 8;	// L1224
    int32_t v833 = dsmask;	// L1225
    int32_t v834 = v833 >> v831;	// L1226
    int32_t v835 = v834 & 1;	// L1227
    bool v836 = v835 == 1;	// L1228
    bool v837 = v830 & v832;	// L1229
    bool v838 = v837 & v836;	// L1230
    if (v838) {	// L1231
      int32_t v839 = s2;	// L1232
      int v840 = v839;	// L1233
      drf_full[v840] = 0;	// L1234
    }
    half res;
#pragma HLS dependence variable=res type=inter dependent=false	// L1236
    res = 0.000000;	// L1237
    int32_t v842 = op;	// L1238
    bool v843 = v842 == 0;	// L1239
    if (v843) {	// L1240
      half v844 = a;	// L1241
      half v845 = b;	// L1242
      half v846 = v844 + v845;
#pragma HLS bind_op variable=v846 op=hadd impl=fabric latency=2	// L1243
      res = v846;	// L1244
    } else {
      int32_t v847 = op;	// L1246
      bool v848 = v847 == 1;	// L1247
      if (v848) {	// L1248
        half v849 = a;	// L1249
        half v850 = b;	// L1250
        half v851 = v849 - v850;
#pragma HLS bind_op variable=v851 op=hsub impl=fabric latency=2	// L1251
        res = v851;	// L1252
      } else {
        int32_t v852 = op;	// L1254
        bool v853 = v852 == 2;	// L1255
        if (v853) {	// L1256
          half v854 = a;	// L1257
          half v855 = b;	// L1258
          half v856 = v854 * v855;
#pragma HLS bind_op variable=v856 op=hmul impl=maxdsp latency=2	// L1259
          res = v856;	// L1260
        } else {
          int32_t v857 = op;	// L1262
          bool v858 = v857 == 8;	// L1263
          if (v858) {	// L1264
            half v859 = a;	// L1265
            half v860 = b;	// L1266
            bool v861 = v859 >= v860;	// L1267
            if (v861) {	// L1268
              res = 1.000000;	// L1269
            } else {
              res = -1.000000;	// L1271
            }
          } else {
            int32_t v862 = op;	// L1274
            bool v863 = v862 == 9;	// L1275
            if (v863) {	// L1276
              half v864 = a;	// L1277
              half v865 = b;	// L1278
              bool v866 = v864 < v865;	// L1279
              if (v866) {	// L1280
                res = 1.000000;	// L1281
              } else {
                res = -1.000000;	// L1283
              }
            } else {
              half v867 = a;	// L1286
              res = v867;	// L1287
            }
          }
        }
      }
    }
    int32_t v868 = a_vld;	// L1293
    int32_t res_vld;	// L1294
    res_vld = v868;	// L1295
    int32_t v870 = op;	// L1296
    bool v871 = v870 == 0;	// L1297
    bool v872 = v870 == 1;	// L1298
    bool v873 = v870 == 2;	// L1299
    bool v874 = v870 == 8;	// L1300
    bool v875 = v870 == 9;	// L1301
    bool v876 = v871 | v872;	// L1302
    bool v877 = v876 | v873;	// L1303
    bool v878 = v877 | v874;	// L1304
    bool v879 = v878 | v875;	// L1305
    if (v879) {	// L1306
      int32_t v880 = a_vld;	// L1307
      int32_t v881 = b_vld;	// L1308
      int64_t v882 = v880;	// L1309
      int64_t v883 = v881;	// L1310
      int64_t v884 = v882 * v883;	// L1311
      int32_t v885 = v884;	// L1312
      res_vld = v885;	// L1313
    }
    int32_t v886 = grant;	// L1315
    bool v887 = v886 == 0;	// L1316
    if (v887) {	// L1317
      res_vld = 0;	// L1318
    }
    int32_t is_rtr;	// L1320
    is_rtr = 0;	// L1321
    int32_t v889 = op;	// L1322
    bool v890 = v889 >= 4;	// L1323
    ap_int<33> v891 = v889;	// L1324
    bool v892 = v891 <= 7;	// L1325
    bool v893 = v890 & v892;	// L1326
    if (v893) {	// L1327
      is_rtr = 1;	// L1328
    }
    int32_t v894 = retire_ok;	// L1330
    bool v895 = v894 == 1;	// L1331
    if (v895) {	// L1332
      l_S_k_9_k1: for (int k1 = 0; k1 < 4; k1++) {	// L1333
        uint8_t v897 = sb_v[(k1 + 1)];	// L1334
        sb_v[k1] = v897;	// L1335
        uint8_t v898 = sb_dst[(k1 + 1)];	// L1336
        sb_dst[k1] = v898;	// L1337
        uint8_t v899 = sb_cmp[(k1 + 1)];	// L1338
        sb_cmp[k1] = v899;	// L1339
        uint8_t v900 = sb_rtr[(k1 + 1)];	// L1340
        sb_rtr[k1] = v900;	// L1341
        uint8_t v901 = sb_inj[(k1 + 1)];	// L1342
        sb_inj[k1] = v901;	// L1343
        uint8_t v902 = sb_dir[(k1 + 1)];	// L1344
        sb_dir[k1] = v902;	// L1345
        uint8_t v903 = sb_id[(k1 + 1)];	// L1346
        sb_id[k1] = v903;	// L1347
        uint8_t v904 = sb_rvld[(k1 + 1)];	// L1348
        sb_rvld[k1] = v904;	// L1349
        uint8_t v905 = sb_ix[(k1 + 1)];	// L1350
        sb_ix[k1] = v905;	// L1351
        uint8_t v906 = sb_long[(k1 + 1)];	// L1352
        sb_long[k1] = v906;	// L1353
      }
      sb_v[4] = 0;	// L1355
    }
    int32_t v907 = grant;	// L1357
    bool v908 = v907 == 1;	// L1358
    if (v908) {	// L1359
      half v909 = res;	// L1360
      int8_t v910 = resq_wr;	// L1361
      int v911 = v910;	// L1362
      resq[v911] = v909;	// L1363
      int32_t cq;	// L1364
      cq = 0;	// L1365
      int32_t v913 = op;	// L1366
      bool v914 = v913 == 8;	// L1367
      if (v914) {	// L1368
        half v915 = a;	// L1369
        half v916 = b;	// L1370
        bool v917 = v915 >= v916;	// L1371
        if (v917) {	// L1372
          cq = 1;	// L1373
        }
      }
      int32_t v918 = op;	// L1376
      bool v919 = v918 == 9;	// L1377
      if (v919) {	// L1378
        half v920 = a;	// L1379
        half v921 = b;	// L1380
        bool v922 = v920 < v921;	// L1381
        if (v922) {	// L1382
          cq = 1;	// L1383
        }
      }
      int32_t v923 = cq;	// L1386
      uint8_t v924 = v923;	// L1387
      int8_t v925 = resq_wr;	// L1388
      int v926 = v925;	// L1389
      cmpq[v926] = v924;	// L1390
      sb_v[4] = 1;	// L1391
      int32_t v927 = dst;	// L1392
      uint8_t v928 = v927;	// L1393
      sb_dst[4] = v928;	// L1394
      int8_t v929 = resq_wr;	// L1395
      sb_ix[4] = v929;	// L1396
      int32_t v930 = binop;	// L1397
      uint8_t v931 = v930;	// L1398
      sb_long[4] = v931;	// L1399
      sb_cmp[4] = 0;	// L1400
      int32_t v932 = op;	// L1401
      bool v933 = v932 == 8;	// L1402
      bool v934 = v932 == 9;	// L1403
      bool v935 = v933 | v934;	// L1404
      if (v935) {	// L1405
        sb_cmp[4] = 1;	// L1406
      }
      int32_t v936 = is_rtr;	// L1408
      int32_t rtrf;	// L1409
      rtrf = v936;	// L1410
      int32_t v938 = is_cond;	// L1411
      bool v939 = v938 == 1;	// L1412
      if (v939) {	// L1413
        rtrf = 1;	// L1414
      }
      int32_t v940 = rtrf;	// L1416
      uint8_t v941 = v940;	// L1417
      sb_rtr[4] = v941;	// L1418
      int32_t v942 = is_rtr;	// L1419
      int32_t inj;	// L1420
      inj = v942;	// L1421
      int32_t v944 = is_cond;	// L1422
      bool v945 = v944 == 1;	// L1423
      int8_t v946 = condition_reg;	// L1424
      int32_t v947 = v946;	// L1425
      bool v948 = v947 == 1;	// L1426
      bool v949 = v945 & v948;	// L1427
      if (v949) {	// L1428
        inj = 1;	// L1429
      }
      int32_t v950 = inj;	// L1431
      uint8_t v951 = v950;	// L1432
      sb_inj[4] = v951;	// L1433
      int32_t v952 = op;	// L1434
      int32_t v953 = v952 & 3;	// L1435
      uint8_t v954 = v953;	// L1436
      sb_dir[4] = v954;	// L1437
      int32_t v955 = s2;	// L1438
      uint8_t v956 = v955;	// L1439
      sb_id[4] = v956;	// L1440
      int32_t v957 = res_vld;	// L1441
      uint8_t v958 = v957;	// L1442
      sb_rvld[4] = v958;	// L1443
      int8_t v959 = resq_wr;	// L1444
      ap_int<33> v960 = v959;	// L1445
      ap_int<33> v961 = v960 + 1;	// L1446
      ap_int<33> v962 = v961 & 7;	// L1447
      uint8_t v963 = v962;	// L1448
      resq_wr = v963;	// L1449
    }
    txn_r = 0;	// L1451
    txs_r = 0;	// L1452
    txw_r = 0;	// L1453
    txe_r = 0;	// L1454
    int32_t v964 = txp_v[0];	// L1455
    bool v965 = v964 == 1;	// L1456
    int32_t v966 = scred[0];	// L1457
    bool v967 = v966 > 0;	// L1458
    bool v968 = v965 & v967;	// L1459
    if (v968) {	// L1460
      ap_uint<17> twn;	// L1461
      twn = 0;	// L1462
      ap_int<17> v970 = twn;	// L1463
      ap_int<17> v971;
      ap_int<17> v971_tmp = v970;
      v971_tmp[0] = 1;      v971 = v971_tmp;	// L1464
      twn = v971;	// L1465
      half v972 = txp_d[0];	// L1466
      uint16_t v973;
      union { half from; uint16_t to;} _converter_v972_to_v973 = {};
      _converter_v972_to_v973.from = v972;
      v973 = _converter_v972_to_v973.to;	// L1467
      ap_int<17> v974 = twn;	// L1468
      ap_int<17> v975;
      ap_int<17> v975_tmp = v974;
      v975_tmp(16, 1) = v973;
      v975 = v975_tmp;	// L1469
      twn = v975;	// L1470
      ap_int<17> v976 = twn;	// L1471
      txn_r = v976;	// L1472
      txp_v[0] = 0;	// L1473
      int32_t v977 = scred[0];	// L1474
      ap_int<33> v978 = v977;	// L1475
      ap_int<33> v979 = v978 - 1;	// L1476
      int32_t v980 = v979;	// L1477
      scred[0] = v980;	// L1478
    }
    int32_t v981 = txp_v[1];	// L1480
    bool v982 = v981 == 1;	// L1481
    int32_t v983 = scred[1];	// L1482
    bool v984 = v983 > 0;	// L1483
    bool v985 = v982 & v984;	// L1484
    if (v985) {	// L1485
      ap_uint<17> tws;	// L1486
      tws = 0;	// L1487
      ap_int<17> v987 = tws;	// L1488
      ap_int<17> v988;
      ap_int<17> v988_tmp = v987;
      v988_tmp[0] = 1;      v988 = v988_tmp;	// L1489
      tws = v988;	// L1490
      half v989 = txp_d[1];	// L1491
      uint16_t v990;
      union { half from; uint16_t to;} _converter_v989_to_v990 = {};
      _converter_v989_to_v990.from = v989;
      v990 = _converter_v989_to_v990.to;	// L1492
      ap_int<17> v991 = tws;	// L1493
      ap_int<17> v992;
      ap_int<17> v992_tmp = v991;
      v992_tmp(16, 1) = v990;
      v992 = v992_tmp;	// L1494
      tws = v992;	// L1495
      ap_int<17> v993 = tws;	// L1496
      txs_r = v993;	// L1497
      txp_v[1] = 0;	// L1498
      int32_t v994 = scred[1];	// L1499
      ap_int<33> v995 = v994;	// L1500
      ap_int<33> v996 = v995 - 1;	// L1501
      int32_t v997 = v996;	// L1502
      scred[1] = v997;	// L1503
    }
    int32_t v998 = txp_v[2];	// L1505
    bool v999 = v998 == 1;	// L1506
    int32_t v1000 = scred[2];	// L1507
    bool v1001 = v1000 > 0;	// L1508
    bool v1002 = v999 & v1001;	// L1509
    if (v1002) {	// L1510
      ap_uint<17> tww;	// L1511
      tww = 0;	// L1512
      ap_int<17> v1004 = tww;	// L1513
      ap_int<17> v1005;
      ap_int<17> v1005_tmp = v1004;
      v1005_tmp[0] = 1;      v1005 = v1005_tmp;	// L1514
      tww = v1005;	// L1515
      half v1006 = txp_d[2];	// L1516
      uint16_t v1007;
      union { half from; uint16_t to;} _converter_v1006_to_v1007 = {};
      _converter_v1006_to_v1007.from = v1006;
      v1007 = _converter_v1006_to_v1007.to;	// L1517
      ap_int<17> v1008 = tww;	// L1518
      ap_int<17> v1009;
      ap_int<17> v1009_tmp = v1008;
      v1009_tmp(16, 1) = v1007;
      v1009 = v1009_tmp;	// L1519
      tww = v1009;	// L1520
      ap_int<17> v1010 = tww;	// L1521
      txw_r = v1010;	// L1522
      txp_v[2] = 0;	// L1523
      int32_t v1011 = scred[2];	// L1524
      ap_int<33> v1012 = v1011;	// L1525
      ap_int<33> v1013 = v1012 - 1;	// L1526
      int32_t v1014 = v1013;	// L1527
      scred[2] = v1014;	// L1528
    }
    int32_t v1015 = txp_v[3];	// L1530
    bool v1016 = v1015 == 1;	// L1531
    int32_t v1017 = scred[3];	// L1532
    bool v1018 = v1017 > 0;	// L1533
    bool v1019 = v1016 & v1018;	// L1534
    if (v1019) {	// L1535
      ap_uint<17> twe;	// L1536
      twe = 0;	// L1537
      ap_int<17> v1021 = twe;	// L1538
      ap_int<17> v1022;
      ap_int<17> v1022_tmp = v1021;
      v1022_tmp[0] = 1;      v1022 = v1022_tmp;	// L1539
      twe = v1022;	// L1540
      half v1023 = txp_d[3];	// L1541
      uint16_t v1024;
      union { half from; uint16_t to;} _converter_v1023_to_v1024 = {};
      _converter_v1023_to_v1024.from = v1023;
      v1024 = _converter_v1023_to_v1024.to;	// L1542
      ap_int<17> v1025 = twe;	// L1543
      ap_int<17> v1026;
      ap_int<17> v1026_tmp = v1025;
      v1026_tmp(16, 1) = v1024;
      v1026 = v1026_tmp;	// L1544
      twe = v1026;	// L1545
      ap_int<17> v1027 = twe;	// L1546
      txe_r = v1027;	// L1547
      txp_v[3] = 0;	// L1548
      int32_t v1028 = scred[3];	// L1549
      ap_int<33> v1029 = v1028;	// L1550
      ap_int<33> v1030 = v1029 - 1;	// L1551
      int32_t v1031 = v1030;	// L1552
      scred[3] = v1031;	// L1553
    }
    int32_t v1032 = crv_vld;	// L1555
    bool v1033 = v1032 == 1;	// L1556
    if (v1033) {	// L1557
      int32_t v1034 = crv_mode;	// L1558
      bool v1035 = v1034 == 1;	// L1559
      if (v1035) {	// L1560
        int32_t v1036 = crv_addr;	// L1561
        int32_t v1037 = v1036 >> 3;	// L1562
        int32_t v1038 = v1037 & 1;	// L1563
        bool v1039 = v1038 == 1;	// L1564
        if (v1039) {	// L1565
          int32_t v1040 = crv_raw;	// L1566
          int32_t v1041 = crv_addr;	// L1567
          int32_t v1042 = v1041 & 7;	// L1568
          int v1043 = v1042;	// L1569
          irf[v1043] = v1040;	// L1570
        } else {
          int32_t v1044 = crv_addr;	// L1572
          bool v1045 = v1044 == 0;	// L1573
          if (v1045) {	// L1574
            int32_t v1046 = crv_raw;	// L1575
            int32_t v1047 = v1046 & 255;	// L1576
            dsmask = v1047;	// L1577
            int32_t v1048 = crv_raw;	// L1578
            int32_t v1049 = v1048 >> 8;	// L1579
            int32_t v1050 = v1049 & 7;	// L1580
            cfg_isz = v1050;	// L1581
            int32_t v1051 = crv_raw;	// L1582
            int32_t v1052 = v1051 >> 15;	// L1583
            int32_t v1053 = v1052 & 1;	// L1584
            bool v1054 = v1053 == 1;	// L1585
            if (v1054) {	// L1586
              fetch_en = 1;	// L1587
              instr_cnt = 0;	// L1588
              iter_cnt = 0;	// L1589
            }
          } else {
            int32_t v1055 = crv_addr;	// L1592
            bool v1056 = v1055 == 1;	// L1593
            if (v1056) {	// L1594
              int32_t v1057 = crv_raw;	// L1595
              int32_t v1058 = v1057 & 255;	// L1596
              cfg_itsz = v1058;	// L1597
            }
          }
        }
      } else {
        int32_t v1059 = crv_addr;	// L1602
        int32_t v1060 = v1059 >> 2;	// L1603
        int32_t v1061 = v1060 & 3;	// L1604
        bool v1062 = v1061 == 3;	// L1605
        if (v1062) {	// L1606
          int32_t v1063 = crv_addr;	// L1607
          int32_t v1064 = v1063 & 3;	// L1608
          int v1065 = v1064;	// L1609
          txp_v[v1065] = 1;	// L1610
          half v1066 = crv_data;	// L1611
          int32_t v1067 = crv_addr;	// L1612
          int32_t v1068 = v1067 & 3;	// L1613
          int v1069 = v1068;	// L1614
          txp_d[v1069] = v1066;	// L1615
          int32_t v1070 = crv_addr;	// L1616
          int32_t v1071 = v1070 & 3;	// L1617
          int v1072 = v1071;	// L1618
          txp_r[v1072] = 1;	// L1619
        } else {
          int32_t v1073 = crv_addr;	// L1621
          bool v1074 = v1073 < 8;	// L1622
          int32_t v1075 = dsmask;	// L1623
          int32_t v1076 = v1075 >> v1073;	// L1624
          int32_t v1077 = v1076 & 1;	// L1625
          bool v1078 = v1077 == 1;	// L1626
          bool v1079 = v1074 & v1078;	// L1627
          if (v1079) {	// L1628
            int32_t v1080 = crv_addr;	// L1629
            int v1081 = v1080;	// L1630
            int32_t v1082 = drf_full[v1081];	// L1631
            bool v1083 = v1082 == 0;	// L1632
            if (v1083) {	// L1633
              half v1084 = crv_data;	// L1634
              int32_t v1085 = crv_addr;	// L1635
              int v1086 = v1085;	// L1636
              drf[v1086] = v1084;	// L1637
              int32_t v1087 = crv_addr;	// L1638
              int v1088 = v1087;	// L1639
              drf_full[v1088] = 1;	// L1640
            }
          } else {
            half v1089 = crv_data;	// L1643
            int32_t v1090 = crv_addr;	// L1644
            int v1091 = v1090;	// L1645
            drf[v1091] = v1089;	// L1646
          }
        }
      }
    }
    ap_int<26> v1092 = oe_r;	// L1651
    v1.write(v1092);	// L1652
    ap_int<26> v1093 = ow_r;	// L1653
    v2.write(v1093);	// L1654
    ap_int<26> v1094 = os_r;	// L1655
    v3.write(v1094);	// L1656
    ap_int<26> v1095 = on_r;	// L1657
    v4.write(v1095);	// L1658
    ap_int<17> v1096 = txe_r;	// L1659
    v5.write(v1096);	// L1660
    ap_int<17> v1097 = txw_r;	// L1661
    v6.write(v1097);	// L1662
    ap_int<17> v1098 = txs_r;	// L1663
    v7.write(v1098);	// L1664
    ap_int<17> v1099 = txn_r;	// L1665
    v8.write(v1099);	// L1666
    int8_t v1100 = cre_r;	// L1667
    v9.write(v1100);	// L1668
    int8_t v1101 = crw_r;	// L1669
    v10.write(v1101);	// L1670
    int8_t v1102 = crs_r;	// L1671
    v11.write(v1102);	// L1672
    int8_t v1103 = crn_r;	// L1673
    v12.write(v1103);	// L1674
    int32_t v1104 = sc_r[0];	// L1675
    v15.write(v1104);	// L1676
    int32_t v1105 = sc_r[1];	// L1677
    v16.write(v1105);	// L1678
    int32_t v1106 = sc_r[2];	// L1679
    v13.write(v1106);	// L1680
    int32_t v1107 = sc_r[3];	// L1681
    v14.write(v1107);	// L1682
  }
}

void drv_w_0(
  half v1108[1][120],
  int32_t v1109[1][120],
  int32_t v1110[1][1],
  hls::stream< ap_uint<17> >& v1111,
  hls::stream< int32_t >& v1112
) {	// L1686
  int32_t dcred[1];	// L1695
  for (int v1114 = 0; v1114 < 1; v1114++) {	// L1696
    dcred[v1114] = 0;	// L1696
  }
  int32_t sp[1];	// L1697
  for (int v1116 = 0; v1116 < 1; v1116++) {	// L1698
    sp[v1116] = 0;	// L1698
  }
  ap_uint<17> zw;	// L1699
  zw = 0;	// L1700
  int32_t v1118 = v1110[0][0];	// L1701
  ap_int<33> v1119 = v1118;	// L1702
  ap_int<33> v1120 = v1119 - 1;	// L1703
  int v1121 = v1120;	// L1704
  for (int v1122 = 0; v1122 < v1121; v1122 += 1) {	// L1705
    ap_int<17> v1123 = zw;	// L1706
    v1111.write(v1123);	// L1707
  }
  l_S_t_1_t1: for (int t1 = 0; t1 < 120; t1++) {	// L1709
    int32_t v1125 = v1112.read();	// L1710
    int32_t v1126 = dcred[0];	// L1711
    ap_int<33> v1127 = v1126;	// L1712
    ap_int<33> v1128 = v1125;	// L1713
    ap_int<33> v1129 = v1127 + v1128;	// L1714
    int32_t v1130 = v1129;	// L1715
    dcred[0] = v1130;	// L1716
    ap_uint<17> w;	// L1717
    w = 0;	// L1718
    int32_t v1132 = sp[0];	// L1719
    bool v1133 = v1132 < 120;	// L1720
    ap_int<33> v1134 = t1;	// L1721
    ap_int<33> v1135 = v1132;	// L1722
    bool v1136 = v1134 >= v1135;	// L1723
    bool v1137 = v1133 & v1136;	// L1724
    if (v1137) {	// L1725
      int32_t v1138 = sp[0];	// L1726
      int v1139 = v1138;	// L1727
      int32_t v1140 = v1109[0][v1139];	// L1728
      bool v1141 = v1140 == 0;	// L1729
      if (v1141) {	// L1730
        int32_t v1142 = sp[0];	// L1731
        ap_int<33> v1143 = v1142;	// L1732
        ap_int<33> v1144 = v1143 + 1;	// L1733
        int32_t v1145 = v1144;	// L1734
        sp[0] = v1145;	// L1735
      } else {
        int32_t v1146 = dcred[0];	// L1737
        bool v1147 = v1146 > 0;	// L1738
        if (v1147) {	// L1739
          ap_int<17> v1148 = w;	// L1740
          ap_int<17> v1149;
          ap_int<17> v1149_tmp = v1148;
          v1149_tmp[0] = 1;          v1149 = v1149_tmp;	// L1741
          w = v1149;	// L1742
          int32_t v1150 = sp[0];	// L1743
          int v1151 = v1150;	// L1744
          half v1152 = v1108[0][v1151];	// L1745
          uint16_t v1153;
          union { half from; uint16_t to;} _converter_v1152_to_v1153 = {};
          _converter_v1152_to_v1153.from = v1152;
          v1153 = _converter_v1152_to_v1153.to;	// L1746
          ap_int<17> v1154 = w;	// L1747
          ap_int<17> v1155;
          ap_int<17> v1155_tmp = v1154;
          v1155_tmp(16, 1) = v1153;
          v1155 = v1155_tmp;	// L1748
          w = v1155;	// L1749
          int32_t v1156 = dcred[0];	// L1750
          ap_int<33> v1157 = v1156;	// L1751
          ap_int<33> v1158 = v1157 - 1;	// L1752
          int32_t v1159 = v1158;	// L1753
          dcred[0] = v1159;	// L1754
          int32_t v1160 = sp[0];	// L1755
          ap_int<33> v1161 = v1160;	// L1756
          ap_int<33> v1162 = v1161 + 1;	// L1757
          int32_t v1163 = v1162;	// L1758
          sp[0] = v1163;	// L1759
        }
      }
    }
    ap_int<17> v1164 = w;	// L1763
    v1111.write(v1164);	// L1764
  }
}

void drv_e_0(
  half v1165[1][120],
  int32_t v1166[1][120],
  int32_t v1167[1][1],
  hls::stream< ap_uint<17> >& v1168,
  hls::stream< int32_t >& v1169
) {	// L1768
  int32_t dcred1[1];	// L1777
  for (int v1171 = 0; v1171 < 1; v1171++) {	// L1778
    dcred1[v1171] = 0;	// L1778
  }
  int32_t sp1[1];	// L1779
  for (int v1173 = 0; v1173 < 1; v1173++) {	// L1780
    sp1[v1173] = 0;	// L1780
  }
  ap_uint<17> zw1;	// L1781
  zw1 = 0;	// L1782
  int32_t v1175 = v1167[0][0];	// L1783
  ap_int<33> v1176 = v1175;	// L1784
  ap_int<33> v1177 = v1176 - 1;	// L1785
  int v1178 = v1177;	// L1786
  for (int v1179 = 0; v1179 < v1178; v1179 += 1) {	// L1787
    ap_int<17> v1180 = zw1;	// L1788
    v1168.write(v1180);	// L1789
  }
  l_S_t_1_t2: for (int t2 = 0; t2 < 120; t2++) {	// L1791
    int32_t v1182 = v1169.read();	// L1792
    int32_t v1183 = dcred1[0];	// L1793
    ap_int<33> v1184 = v1183;	// L1794
    ap_int<33> v1185 = v1182;	// L1795
    ap_int<33> v1186 = v1184 + v1185;	// L1796
    int32_t v1187 = v1186;	// L1797
    dcred1[0] = v1187;	// L1798
    ap_uint<17> w1;	// L1799
    w1 = 0;	// L1800
    int32_t v1189 = sp1[0];	// L1801
    bool v1190 = v1189 < 120;	// L1802
    ap_int<33> v1191 = t2;	// L1803
    ap_int<33> v1192 = v1189;	// L1804
    bool v1193 = v1191 >= v1192;	// L1805
    bool v1194 = v1190 & v1193;	// L1806
    if (v1194) {	// L1807
      int32_t v1195 = sp1[0];	// L1808
      int v1196 = v1195;	// L1809
      int32_t v1197 = v1166[0][v1196];	// L1810
      bool v1198 = v1197 == 0;	// L1811
      if (v1198) {	// L1812
        int32_t v1199 = sp1[0];	// L1813
        ap_int<33> v1200 = v1199;	// L1814
        ap_int<33> v1201 = v1200 + 1;	// L1815
        int32_t v1202 = v1201;	// L1816
        sp1[0] = v1202;	// L1817
      } else {
        int32_t v1203 = dcred1[0];	// L1819
        bool v1204 = v1203 > 0;	// L1820
        if (v1204) {	// L1821
          ap_int<17> v1205 = w1;	// L1822
          ap_int<17> v1206;
          ap_int<17> v1206_tmp = v1205;
          v1206_tmp[0] = 1;          v1206 = v1206_tmp;	// L1823
          w1 = v1206;	// L1824
          int32_t v1207 = sp1[0];	// L1825
          int v1208 = v1207;	// L1826
          half v1209 = v1165[0][v1208];	// L1827
          uint16_t v1210;
          union { half from; uint16_t to;} _converter_v1209_to_v1210 = {};
          _converter_v1209_to_v1210.from = v1209;
          v1210 = _converter_v1209_to_v1210.to;	// L1828
          ap_int<17> v1211 = w1;	// L1829
          ap_int<17> v1212;
          ap_int<17> v1212_tmp = v1211;
          v1212_tmp(16, 1) = v1210;
          v1212 = v1212_tmp;	// L1830
          w1 = v1212;	// L1831
          int32_t v1213 = dcred1[0];	// L1832
          ap_int<33> v1214 = v1213;	// L1833
          ap_int<33> v1215 = v1214 - 1;	// L1834
          int32_t v1216 = v1215;	// L1835
          dcred1[0] = v1216;	// L1836
          int32_t v1217 = sp1[0];	// L1837
          ap_int<33> v1218 = v1217;	// L1838
          ap_int<33> v1219 = v1218 + 1;	// L1839
          int32_t v1220 = v1219;	// L1840
          sp1[0] = v1220;	// L1841
        }
      }
    }
    ap_int<17> v1221 = w1;	// L1845
    v1168.write(v1221);	// L1846
  }
}

void drv_n_0(
  half v1222[1][120],
  int32_t v1223[1][120],
  int32_t v1224[1][1],
  hls::stream< ap_uint<17> >& v1225,
  hls::stream< int32_t >& v1226
) {	// L1850
  int32_t dcred2[1];	// L1859
  for (int v1228 = 0; v1228 < 1; v1228++) {	// L1860
    dcred2[v1228] = 0;	// L1860
  }
  int32_t sp2[1];	// L1861
  for (int v1230 = 0; v1230 < 1; v1230++) {	// L1862
    sp2[v1230] = 0;	// L1862
  }
  ap_uint<17> zw2;	// L1863
  zw2 = 0;	// L1864
  int32_t v1232 = v1224[0][0];	// L1865
  ap_int<33> v1233 = v1232;	// L1866
  ap_int<33> v1234 = v1233 - 1;	// L1867
  int v1235 = v1234;	// L1868
  for (int v1236 = 0; v1236 < v1235; v1236 += 1) {	// L1869
    ap_int<17> v1237 = zw2;	// L1870
    v1225.write(v1237);	// L1871
  }
  l_S_t_1_t3: for (int t3 = 0; t3 < 120; t3++) {	// L1873
    int32_t v1239 = v1226.read();	// L1874
    int32_t v1240 = dcred2[0];	// L1875
    ap_int<33> v1241 = v1240;	// L1876
    ap_int<33> v1242 = v1239;	// L1877
    ap_int<33> v1243 = v1241 + v1242;	// L1878
    int32_t v1244 = v1243;	// L1879
    dcred2[0] = v1244;	// L1880
    ap_uint<17> w2;	// L1881
    w2 = 0;	// L1882
    int32_t v1246 = sp2[0];	// L1883
    bool v1247 = v1246 < 120;	// L1884
    ap_int<33> v1248 = t3;	// L1885
    ap_int<33> v1249 = v1246;	// L1886
    bool v1250 = v1248 >= v1249;	// L1887
    bool v1251 = v1247 & v1250;	// L1888
    if (v1251) {	// L1889
      int32_t v1252 = sp2[0];	// L1890
      int v1253 = v1252;	// L1891
      int32_t v1254 = v1223[0][v1253];	// L1892
      bool v1255 = v1254 == 0;	// L1893
      if (v1255) {	// L1894
        int32_t v1256 = sp2[0];	// L1895
        ap_int<33> v1257 = v1256;	// L1896
        ap_int<33> v1258 = v1257 + 1;	// L1897
        int32_t v1259 = v1258;	// L1898
        sp2[0] = v1259;	// L1899
      } else {
        int32_t v1260 = dcred2[0];	// L1901
        bool v1261 = v1260 > 0;	// L1902
        if (v1261) {	// L1903
          ap_int<17> v1262 = w2;	// L1904
          ap_int<17> v1263;
          ap_int<17> v1263_tmp = v1262;
          v1263_tmp[0] = 1;          v1263 = v1263_tmp;	// L1905
          w2 = v1263;	// L1906
          int32_t v1264 = sp2[0];	// L1907
          int v1265 = v1264;	// L1908
          half v1266 = v1222[0][v1265];	// L1909
          uint16_t v1267;
          union { half from; uint16_t to;} _converter_v1266_to_v1267 = {};
          _converter_v1266_to_v1267.from = v1266;
          v1267 = _converter_v1266_to_v1267.to;	// L1910
          ap_int<17> v1268 = w2;	// L1911
          ap_int<17> v1269;
          ap_int<17> v1269_tmp = v1268;
          v1269_tmp(16, 1) = v1267;
          v1269 = v1269_tmp;	// L1912
          w2 = v1269;	// L1913
          int32_t v1270 = dcred2[0];	// L1914
          ap_int<33> v1271 = v1270;	// L1915
          ap_int<33> v1272 = v1271 - 1;	// L1916
          int32_t v1273 = v1272;	// L1917
          dcred2[0] = v1273;	// L1918
          int32_t v1274 = sp2[0];	// L1919
          ap_int<33> v1275 = v1274;	// L1920
          ap_int<33> v1276 = v1275 + 1;	// L1921
          int32_t v1277 = v1276;	// L1922
          sp2[0] = v1277;	// L1923
        }
      }
    }
    ap_int<17> v1278 = w2;	// L1927
    v1225.write(v1278);	// L1928
  }
}

void drv_s_0(
  half v1279[1][120],
  int32_t v1280[1][120],
  int32_t v1281[1][1],
  hls::stream< ap_uint<17> >& v1282,
  hls::stream< int32_t >& v1283
) {	// L1932
  int32_t dcred3[1];	// L1941
  for (int v1285 = 0; v1285 < 1; v1285++) {	// L1942
    dcred3[v1285] = 0;	// L1942
  }
  int32_t sp3[1];	// L1943
  for (int v1287 = 0; v1287 < 1; v1287++) {	// L1944
    sp3[v1287] = 0;	// L1944
  }
  ap_uint<17> zw3;	// L1945
  zw3 = 0;	// L1946
  int32_t v1289 = v1281[0][0];	// L1947
  ap_int<33> v1290 = v1289;	// L1948
  ap_int<33> v1291 = v1290 - 1;	// L1949
  int v1292 = v1291;	// L1950
  for (int v1293 = 0; v1293 < v1292; v1293 += 1) {	// L1951
    ap_int<17> v1294 = zw3;	// L1952
    v1282.write(v1294);	// L1953
  }
  l_S_t_1_t4: for (int t4 = 0; t4 < 120; t4++) {	// L1955
    int32_t v1296 = v1283.read();	// L1956
    int32_t v1297 = dcred3[0];	// L1957
    ap_int<33> v1298 = v1297;	// L1958
    ap_int<33> v1299 = v1296;	// L1959
    ap_int<33> v1300 = v1298 + v1299;	// L1960
    int32_t v1301 = v1300;	// L1961
    dcred3[0] = v1301;	// L1962
    ap_uint<17> w3;	// L1963
    w3 = 0;	// L1964
    int32_t v1303 = sp3[0];	// L1965
    bool v1304 = v1303 < 120;	// L1966
    ap_int<33> v1305 = t4;	// L1967
    ap_int<33> v1306 = v1303;	// L1968
    bool v1307 = v1305 >= v1306;	// L1969
    bool v1308 = v1304 & v1307;	// L1970
    if (v1308) {	// L1971
      int32_t v1309 = sp3[0];	// L1972
      int v1310 = v1309;	// L1973
      int32_t v1311 = v1280[0][v1310];	// L1974
      bool v1312 = v1311 == 0;	// L1975
      if (v1312) {	// L1976
        int32_t v1313 = sp3[0];	// L1977
        ap_int<33> v1314 = v1313;	// L1978
        ap_int<33> v1315 = v1314 + 1;	// L1979
        int32_t v1316 = v1315;	// L1980
        sp3[0] = v1316;	// L1981
      } else {
        int32_t v1317 = dcred3[0];	// L1983
        bool v1318 = v1317 > 0;	// L1984
        if (v1318) {	// L1985
          ap_int<17> v1319 = w3;	// L1986
          ap_int<17> v1320;
          ap_int<17> v1320_tmp = v1319;
          v1320_tmp[0] = 1;          v1320 = v1320_tmp;	// L1987
          w3 = v1320;	// L1988
          int32_t v1321 = sp3[0];	// L1989
          int v1322 = v1321;	// L1990
          half v1323 = v1279[0][v1322];	// L1991
          uint16_t v1324;
          union { half from; uint16_t to;} _converter_v1323_to_v1324 = {};
          _converter_v1323_to_v1324.from = v1323;
          v1324 = _converter_v1323_to_v1324.to;	// L1992
          ap_int<17> v1325 = w3;	// L1993
          ap_int<17> v1326;
          ap_int<17> v1326_tmp = v1325;
          v1326_tmp(16, 1) = v1324;
          v1326 = v1326_tmp;	// L1994
          w3 = v1326;	// L1995
          int32_t v1327 = dcred3[0];	// L1996
          ap_int<33> v1328 = v1327;	// L1997
          ap_int<33> v1329 = v1328 - 1;	// L1998
          int32_t v1330 = v1329;	// L1999
          dcred3[0] = v1330;	// L2000
          int32_t v1331 = sp3[0];	// L2001
          ap_int<33> v1332 = v1331;	// L2002
          ap_int<33> v1333 = v1332 + 1;	// L2003
          int32_t v1334 = v1333;	// L2004
          sp3[0] = v1334;	// L2005
        }
      }
    }
    ap_int<17> v1335 = w3;	// L2009
    v1282.write(v1335);	// L2010
  }
}

void col_w_0(
  half v1336[1][120],
  int32_t v1337[1][1],
  hls::stream< int32_t >& v1338,
  hls::stream< ap_uint<17> >& v1339
) {	// L2014
  int32_t k2[1];	// L2023
  for (int v1341 = 0; v1341 < 1; v1341++) {	// L2024
    k2[v1341] = 0;	// L2024
  }
  int32_t cret[1];	// L2025
  for (int v1343 = 0; v1343 < 1; v1343++) {	// L2026
    cret[v1343] = 0;	// L2026
  }
  int32_t zc;	// L2027
  zc = 0;	// L2028
  int32_t v1345 = v1337[0][0];	// L2029
  ap_int<33> v1346 = v1345;	// L2030
  ap_int<33> v1347 = v1346 - 1;	// L2031
  int v1348 = v1347;	// L2032
  for (int v1349 = 0; v1349 < v1348; v1349 += 1) {	// L2033
    int32_t v1350 = zc;	// L2034
    v1338.write(v1350);	// L2035
  }
  cret[0] = 2;	// L2037
  int32_t v1351 = cret[0];	// L2038
  v1338.write(v1351);	// L2039
  l_S_t_1_t5: for (int t5 = 0; t5 < 120; t5++) {	// L2040
    ap_uint<17> v1353 = v1339.read();	// L2041
    ap_uint<17> w4;	// L2042
    w4 = v1353;	// L2043
    cret[0] = 0;	// L2044
    ap_int<17> v1355 = w4;	// L2045
    bool v1356;
    ap_int<17> v1356_tmp = v1355;
    v1356 = v1356_tmp[0];	// L2046
    int32_t v1357 = v1356;	// L2047
    bool v1358 = v1357 == 1;	// L2048
    if (v1358) {	// L2049
      cret[0] = 1;	// L2050
      int32_t v1359 = k2[0];	// L2051
      bool v1360 = v1359 < 120;	// L2052
      if (v1360) {	// L2053
        ap_int<17> v1361 = w4;	// L2054
        int16_t v1362;
        ap_int<17> v1362_tmp = v1361;
        v1362 = v1362_tmp(16, 1);	// L2055
        half v1363;
        union { uint16_t from; half to;} _converter_v1362_to_v1363 = {};
        _converter_v1362_to_v1363.from = v1362;
        v1363 = _converter_v1362_to_v1363.to;	// L2056
        int32_t v1364 = k2[0];	// L2057
        int v1365 = v1364;	// L2058
        v1336[0][v1365] = v1363;	// L2059
        int32_t v1366 = k2[0];	// L2060
        ap_int<33> v1367 = v1366;	// L2061
        ap_int<33> v1368 = v1367 + 1;	// L2062
        int32_t v1369 = v1368;	// L2063
        k2[0] = v1369;	// L2064
      }
    }
    int32_t v1370 = cret[0];	// L2067
    v1338.write(v1370);	// L2068
  }
}

void col_e_0(
  half v1371[1][120],
  int32_t v1372[1][1],
  hls::stream< int32_t >& v1373,
  hls::stream< ap_uint<17> >& v1374
) {	// L2072
  int32_t k3[1];	// L2081
  for (int v1376 = 0; v1376 < 1; v1376++) {	// L2082
    k3[v1376] = 0;	// L2082
  }
  int32_t cret1[1];	// L2083
  for (int v1378 = 0; v1378 < 1; v1378++) {	// L2084
    cret1[v1378] = 0;	// L2084
  }
  int32_t zc1;	// L2085
  zc1 = 0;	// L2086
  int32_t v1380 = v1372[0][0];	// L2087
  ap_int<33> v1381 = v1380;	// L2088
  ap_int<33> v1382 = v1381 - 1;	// L2089
  int v1383 = v1382;	// L2090
  for (int v1384 = 0; v1384 < v1383; v1384 += 1) {	// L2091
    int32_t v1385 = zc1;	// L2092
    v1373.write(v1385);	// L2093
  }
  cret1[0] = 2;	// L2095
  int32_t v1386 = cret1[0];	// L2096
  v1373.write(v1386);	// L2097
  l_S_t_1_t6: for (int t6 = 0; t6 < 120; t6++) {	// L2098
    ap_uint<17> v1388 = v1374.read();	// L2099
    ap_uint<17> w5;	// L2100
    w5 = v1388;	// L2101
    cret1[0] = 0;	// L2102
    ap_int<17> v1390 = w5;	// L2103
    bool v1391;
    ap_int<17> v1391_tmp = v1390;
    v1391 = v1391_tmp[0];	// L2104
    int32_t v1392 = v1391;	// L2105
    bool v1393 = v1392 == 1;	// L2106
    if (v1393) {	// L2107
      cret1[0] = 1;	// L2108
      int32_t v1394 = k3[0];	// L2109
      bool v1395 = v1394 < 120;	// L2110
      if (v1395) {	// L2111
        ap_int<17> v1396 = w5;	// L2112
        int16_t v1397;
        ap_int<17> v1397_tmp = v1396;
        v1397 = v1397_tmp(16, 1);	// L2113
        half v1398;
        union { uint16_t from; half to;} _converter_v1397_to_v1398 = {};
        _converter_v1397_to_v1398.from = v1397;
        v1398 = _converter_v1397_to_v1398.to;	// L2114
        int32_t v1399 = k3[0];	// L2115
        int v1400 = v1399;	// L2116
        v1371[0][v1400] = v1398;	// L2117
        int32_t v1401 = k3[0];	// L2118
        ap_int<33> v1402 = v1401;	// L2119
        ap_int<33> v1403 = v1402 + 1;	// L2120
        int32_t v1404 = v1403;	// L2121
        k3[0] = v1404;	// L2122
      }
    }
    int32_t v1405 = cret1[0];	// L2125
    v1373.write(v1405);	// L2126
  }
}

void col_n_0(
  half v1406[1][120],
  int32_t v1407[1][1],
  hls::stream< int32_t >& v1408,
  hls::stream< ap_uint<17> >& v1409
) {	// L2130
  int32_t k4[1];	// L2139
  for (int v1411 = 0; v1411 < 1; v1411++) {	// L2140
    k4[v1411] = 0;	// L2140
  }
  int32_t cret2[1];	// L2141
  for (int v1413 = 0; v1413 < 1; v1413++) {	// L2142
    cret2[v1413] = 0;	// L2142
  }
  int32_t zc2;	// L2143
  zc2 = 0;	// L2144
  int32_t v1415 = v1407[0][0];	// L2145
  ap_int<33> v1416 = v1415;	// L2146
  ap_int<33> v1417 = v1416 - 1;	// L2147
  int v1418 = v1417;	// L2148
  for (int v1419 = 0; v1419 < v1418; v1419 += 1) {	// L2149
    int32_t v1420 = zc2;	// L2150
    v1408.write(v1420);	// L2151
  }
  cret2[0] = 2;	// L2153
  int32_t v1421 = cret2[0];	// L2154
  v1408.write(v1421);	// L2155
  l_S_t_1_t7: for (int t7 = 0; t7 < 120; t7++) {	// L2156
    ap_uint<17> v1423 = v1409.read();	// L2157
    ap_uint<17> w6;	// L2158
    w6 = v1423;	// L2159
    cret2[0] = 0;	// L2160
    ap_int<17> v1425 = w6;	// L2161
    bool v1426;
    ap_int<17> v1426_tmp = v1425;
    v1426 = v1426_tmp[0];	// L2162
    int32_t v1427 = v1426;	// L2163
    bool v1428 = v1427 == 1;	// L2164
    if (v1428) {	// L2165
      cret2[0] = 1;	// L2166
      int32_t v1429 = k4[0];	// L2167
      bool v1430 = v1429 < 120;	// L2168
      if (v1430) {	// L2169
        ap_int<17> v1431 = w6;	// L2170
        int16_t v1432;
        ap_int<17> v1432_tmp = v1431;
        v1432 = v1432_tmp(16, 1);	// L2171
        half v1433;
        union { uint16_t from; half to;} _converter_v1432_to_v1433 = {};
        _converter_v1432_to_v1433.from = v1432;
        v1433 = _converter_v1432_to_v1433.to;	// L2172
        int32_t v1434 = k4[0];	// L2173
        int v1435 = v1434;	// L2174
        v1406[0][v1435] = v1433;	// L2175
        int32_t v1436 = k4[0];	// L2176
        ap_int<33> v1437 = v1436;	// L2177
        ap_int<33> v1438 = v1437 + 1;	// L2178
        int32_t v1439 = v1438;	// L2179
        k4[0] = v1439;	// L2180
      }
    }
    int32_t v1440 = cret2[0];	// L2183
    v1408.write(v1440);	// L2184
  }
}

void col_s_0(
  half v1441[1][120],
  int32_t v1442[1][1],
  hls::stream< int32_t >& v1443,
  hls::stream< ap_uint<17> >& v1444
) {	// L2188
  int32_t k5[1];	// L2197
  for (int v1446 = 0; v1446 < 1; v1446++) {	// L2198
    k5[v1446] = 0;	// L2198
  }
  int32_t cret3[1];	// L2199
  for (int v1448 = 0; v1448 < 1; v1448++) {	// L2200
    cret3[v1448] = 0;	// L2200
  }
  int32_t zc3;	// L2201
  zc3 = 0;	// L2202
  int32_t v1450 = v1442[0][0];	// L2203
  ap_int<33> v1451 = v1450;	// L2204
  ap_int<33> v1452 = v1451 - 1;	// L2205
  int v1453 = v1452;	// L2206
  for (int v1454 = 0; v1454 < v1453; v1454 += 1) {	// L2207
    int32_t v1455 = zc3;	// L2208
    v1443.write(v1455);	// L2209
  }
  cret3[0] = 2;	// L2211
  int32_t v1456 = cret3[0];	// L2212
  v1443.write(v1456);	// L2213
  l_S_t_1_t8: for (int t8 = 0; t8 < 120; t8++) {	// L2214
    ap_uint<17> v1458 = v1444.read();	// L2215
    ap_uint<17> w7;	// L2216
    w7 = v1458;	// L2217
    cret3[0] = 0;	// L2218
    ap_int<17> v1460 = w7;	// L2219
    bool v1461;
    ap_int<17> v1461_tmp = v1460;
    v1461 = v1461_tmp[0];	// L2220
    int32_t v1462 = v1461;	// L2221
    bool v1463 = v1462 == 1;	// L2222
    if (v1463) {	// L2223
      cret3[0] = 1;	// L2224
      int32_t v1464 = k5[0];	// L2225
      bool v1465 = v1464 < 120;	// L2226
      if (v1465) {	// L2227
        ap_int<17> v1466 = w7;	// L2228
        int16_t v1467;
        ap_int<17> v1467_tmp = v1466;
        v1467 = v1467_tmp(16, 1);	// L2229
        half v1468;
        union { uint16_t from; half to;} _converter_v1467_to_v1468 = {};
        _converter_v1467_to_v1468.from = v1467;
        v1468 = _converter_v1467_to_v1468.to;	// L2230
        int32_t v1469 = k5[0];	// L2231
        int v1470 = v1469;	// L2232
        v1441[0][v1470] = v1468;	// L2233
        int32_t v1471 = k5[0];	// L2234
        ap_int<33> v1472 = v1471;	// L2235
        ap_int<33> v1473 = v1472 + 1;	// L2236
        int32_t v1474 = v1473;	// L2237
        k5[0] = v1474;	// L2238
      }
    }
    int32_t v1475 = cret3[0];	// L2241
    v1443.write(v1475);	// L2242
  }
}

void rdrv_w_0(
  int32_t v1476[1][120],
  int32_t v1477[1][1],
  hls::stream< ap_uint<26> >& v1478,
  hls::stream< int32_t >& v1479
) {	// L2246
  int32_t dcred4[1];	// L2254
  for (int v1481 = 0; v1481 < 1; v1481++) {	// L2255
    dcred4[v1481] = 0;	// L2255
  }
  int32_t sp4[1];	// L2256
  for (int v1483 = 0; v1483 < 1; v1483++) {	// L2257
    sp4[v1483] = 0;	// L2257
  }
  ap_uint<26> zp;	// L2258
  zp = 0;	// L2259
  int32_t v1485 = v1477[0][0];	// L2260
  ap_int<33> v1486 = v1485;	// L2261
  ap_int<33> v1487 = v1486 - 1;	// L2262
  int v1488 = v1487;	// L2263
  for (int v1489 = 0; v1489 < v1488; v1489 += 1) {	// L2264
    ap_int<26> v1490 = zp;	// L2265
    v1478.write(v1490);	// L2266
  }
  l_S_t_1_t9: for (int t9 = 0; t9 < 120; t9++) {	// L2268
    int32_t v1492 = v1479.read();	// L2269
    int32_t v1493 = dcred4[0];	// L2270
    ap_int<33> v1494 = v1493;	// L2271
    ap_int<33> v1495 = v1492;	// L2272
    ap_int<33> v1496 = v1494 + v1495;	// L2273
    int32_t v1497 = v1496;	// L2274
    dcred4[0] = v1497;	// L2275
    ap_uint<26> pw;	// L2276
    pw = 0;	// L2277
    int32_t v1499 = sp4[0];	// L2278
    bool v1500 = v1499 < 120;	// L2279
    if (v1500) {	// L2280
      ap_uint<26> cand;	// L2281
      cand = 0;	// L2282
      int32_t v1502 = sp4[0];	// L2283
      int v1503 = v1502;	// L2284
      int32_t v1504 = v1476[0][v1503];	// L2285
      ap_uint<26> v1505 = v1504;	// L2286
      ap_int<26> v1506 = cand;	// L2287
      ap_int<26> v1507;
      ap_int<26> v1507_tmp = v1506;
      v1507_tmp(25, 0) = v1505;
      v1507 = v1507_tmp;	// L2288
      cand = v1507;	// L2289
      ap_int<26> v1508 = cand;	// L2290
      bool v1509;
      ap_int<26> v1509_tmp = v1508;
      v1509 = v1509_tmp[25];	// L2291
      int32_t v1510 = v1509;	// L2292
      bool v1511 = v1510 == 0;	// L2293
      if (v1511) {	// L2294
        int32_t v1512 = sp4[0];	// L2295
        ap_int<33> v1513 = v1512;	// L2296
        ap_int<33> v1514 = v1513 + 1;	// L2297
        int32_t v1515 = v1514;	// L2298
        sp4[0] = v1515;	// L2299
      } else {
        int32_t v1516 = dcred4[0];	// L2301
        bool v1517 = v1516 > 0;	// L2302
        if (v1517) {	// L2303
          ap_int<26> v1518 = cand;	// L2304
          pw = v1518;	// L2305
          int32_t v1519 = dcred4[0];	// L2306
          ap_int<33> v1520 = v1519;	// L2307
          ap_int<33> v1521 = v1520 - 1;	// L2308
          int32_t v1522 = v1521;	// L2309
          dcred4[0] = v1522;	// L2310
          int32_t v1523 = sp4[0];	// L2311
          ap_int<33> v1524 = v1523;	// L2312
          ap_int<33> v1525 = v1524 + 1;	// L2313
          int32_t v1526 = v1525;	// L2314
          sp4[0] = v1526;	// L2315
        }
      }
    }
    ap_int<26> v1527 = pw;	// L2319
    v1478.write(v1527);	// L2320
  }
}

void rdrv_e_0(
  int32_t v1528[1][120],
  int32_t v1529[1][1],
  hls::stream< ap_uint<26> >& v1530,
  hls::stream< int32_t >& v1531
) {	// L2324
  int32_t dcred5[1];	// L2332
  for (int v1533 = 0; v1533 < 1; v1533++) {	// L2333
    dcred5[v1533] = 0;	// L2333
  }
  int32_t sp5[1];	// L2334
  for (int v1535 = 0; v1535 < 1; v1535++) {	// L2335
    sp5[v1535] = 0;	// L2335
  }
  ap_uint<26> zp1;	// L2336
  zp1 = 0;	// L2337
  int32_t v1537 = v1529[0][0];	// L2338
  ap_int<33> v1538 = v1537;	// L2339
  ap_int<33> v1539 = v1538 - 1;	// L2340
  int v1540 = v1539;	// L2341
  for (int v1541 = 0; v1541 < v1540; v1541 += 1) {	// L2342
    ap_int<26> v1542 = zp1;	// L2343
    v1530.write(v1542);	// L2344
  }
  l_S_t_1_t10: for (int t10 = 0; t10 < 120; t10++) {	// L2346
    int32_t v1544 = v1531.read();	// L2347
    int32_t v1545 = dcred5[0];	// L2348
    ap_int<33> v1546 = v1545;	// L2349
    ap_int<33> v1547 = v1544;	// L2350
    ap_int<33> v1548 = v1546 + v1547;	// L2351
    int32_t v1549 = v1548;	// L2352
    dcred5[0] = v1549;	// L2353
    ap_uint<26> pw1;	// L2354
    pw1 = 0;	// L2355
    int32_t v1551 = sp5[0];	// L2356
    bool v1552 = v1551 < 120;	// L2357
    if (v1552) {	// L2358
      ap_uint<26> cand1;	// L2359
      cand1 = 0;	// L2360
      int32_t v1554 = sp5[0];	// L2361
      int v1555 = v1554;	// L2362
      int32_t v1556 = v1528[0][v1555];	// L2363
      ap_uint<26> v1557 = v1556;	// L2364
      ap_int<26> v1558 = cand1;	// L2365
      ap_int<26> v1559;
      ap_int<26> v1559_tmp = v1558;
      v1559_tmp(25, 0) = v1557;
      v1559 = v1559_tmp;	// L2366
      cand1 = v1559;	// L2367
      ap_int<26> v1560 = cand1;	// L2368
      bool v1561;
      ap_int<26> v1561_tmp = v1560;
      v1561 = v1561_tmp[25];	// L2369
      int32_t v1562 = v1561;	// L2370
      bool v1563 = v1562 == 0;	// L2371
      if (v1563) {	// L2372
        int32_t v1564 = sp5[0];	// L2373
        ap_int<33> v1565 = v1564;	// L2374
        ap_int<33> v1566 = v1565 + 1;	// L2375
        int32_t v1567 = v1566;	// L2376
        sp5[0] = v1567;	// L2377
      } else {
        int32_t v1568 = dcred5[0];	// L2379
        bool v1569 = v1568 > 0;	// L2380
        if (v1569) {	// L2381
          ap_int<26> v1570 = cand1;	// L2382
          pw1 = v1570;	// L2383
          int32_t v1571 = dcred5[0];	// L2384
          ap_int<33> v1572 = v1571;	// L2385
          ap_int<33> v1573 = v1572 - 1;	// L2386
          int32_t v1574 = v1573;	// L2387
          dcred5[0] = v1574;	// L2388
          int32_t v1575 = sp5[0];	// L2389
          ap_int<33> v1576 = v1575;	// L2390
          ap_int<33> v1577 = v1576 + 1;	// L2391
          int32_t v1578 = v1577;	// L2392
          sp5[0] = v1578;	// L2393
        }
      }
    }
    ap_int<26> v1579 = pw1;	// L2397
    v1530.write(v1579);	// L2398
  }
}

void rdrv_n_0(
  int32_t v1580[1][120],
  int32_t v1581[1][1],
  hls::stream< ap_uint<26> >& v1582,
  hls::stream< int32_t >& v1583
) {	// L2402
  int32_t dcred6[1];	// L2410
  for (int v1585 = 0; v1585 < 1; v1585++) {	// L2411
    dcred6[v1585] = 0;	// L2411
  }
  int32_t sp6[1];	// L2412
  for (int v1587 = 0; v1587 < 1; v1587++) {	// L2413
    sp6[v1587] = 0;	// L2413
  }
  ap_uint<26> zp2;	// L2414
  zp2 = 0;	// L2415
  int32_t v1589 = v1581[0][0];	// L2416
  ap_int<33> v1590 = v1589;	// L2417
  ap_int<33> v1591 = v1590 - 1;	// L2418
  int v1592 = v1591;	// L2419
  for (int v1593 = 0; v1593 < v1592; v1593 += 1) {	// L2420
    ap_int<26> v1594 = zp2;	// L2421
    v1582.write(v1594);	// L2422
  }
  l_S_t_1_t11: for (int t11 = 0; t11 < 120; t11++) {	// L2424
    int32_t v1596 = v1583.read();	// L2425
    int32_t v1597 = dcred6[0];	// L2426
    ap_int<33> v1598 = v1597;	// L2427
    ap_int<33> v1599 = v1596;	// L2428
    ap_int<33> v1600 = v1598 + v1599;	// L2429
    int32_t v1601 = v1600;	// L2430
    dcred6[0] = v1601;	// L2431
    ap_uint<26> pw2;	// L2432
    pw2 = 0;	// L2433
    int32_t v1603 = sp6[0];	// L2434
    bool v1604 = v1603 < 120;	// L2435
    if (v1604) {	// L2436
      ap_uint<26> cand2;	// L2437
      cand2 = 0;	// L2438
      int32_t v1606 = sp6[0];	// L2439
      int v1607 = v1606;	// L2440
      int32_t v1608 = v1580[0][v1607];	// L2441
      ap_uint<26> v1609 = v1608;	// L2442
      ap_int<26> v1610 = cand2;	// L2443
      ap_int<26> v1611;
      ap_int<26> v1611_tmp = v1610;
      v1611_tmp(25, 0) = v1609;
      v1611 = v1611_tmp;	// L2444
      cand2 = v1611;	// L2445
      ap_int<26> v1612 = cand2;	// L2446
      bool v1613;
      ap_int<26> v1613_tmp = v1612;
      v1613 = v1613_tmp[25];	// L2447
      int32_t v1614 = v1613;	// L2448
      bool v1615 = v1614 == 0;	// L2449
      if (v1615) {	// L2450
        int32_t v1616 = sp6[0];	// L2451
        ap_int<33> v1617 = v1616;	// L2452
        ap_int<33> v1618 = v1617 + 1;	// L2453
        int32_t v1619 = v1618;	// L2454
        sp6[0] = v1619;	// L2455
      } else {
        int32_t v1620 = dcred6[0];	// L2457
        bool v1621 = v1620 > 0;	// L2458
        if (v1621) {	// L2459
          ap_int<26> v1622 = cand2;	// L2460
          pw2 = v1622;	// L2461
          int32_t v1623 = dcred6[0];	// L2462
          ap_int<33> v1624 = v1623;	// L2463
          ap_int<33> v1625 = v1624 - 1;	// L2464
          int32_t v1626 = v1625;	// L2465
          dcred6[0] = v1626;	// L2466
          int32_t v1627 = sp6[0];	// L2467
          ap_int<33> v1628 = v1627;	// L2468
          ap_int<33> v1629 = v1628 + 1;	// L2469
          int32_t v1630 = v1629;	// L2470
          sp6[0] = v1630;	// L2471
        }
      }
    }
    ap_int<26> v1631 = pw2;	// L2475
    v1582.write(v1631);	// L2476
  }
}

void rdrv_s_0(
  int32_t v1632[1][120],
  int32_t v1633[1][1],
  hls::stream< ap_uint<26> >& v1634,
  hls::stream< int32_t >& v1635
) {	// L2480
  int32_t dcred7[1];	// L2488
  for (int v1637 = 0; v1637 < 1; v1637++) {	// L2489
    dcred7[v1637] = 0;	// L2489
  }
  int32_t sp7[1];	// L2490
  for (int v1639 = 0; v1639 < 1; v1639++) {	// L2491
    sp7[v1639] = 0;	// L2491
  }
  ap_uint<26> zp3;	// L2492
  zp3 = 0;	// L2493
  int32_t v1641 = v1633[0][0];	// L2494
  ap_int<33> v1642 = v1641;	// L2495
  ap_int<33> v1643 = v1642 - 1;	// L2496
  int v1644 = v1643;	// L2497
  for (int v1645 = 0; v1645 < v1644; v1645 += 1) {	// L2498
    ap_int<26> v1646 = zp3;	// L2499
    v1634.write(v1646);	// L2500
  }
  l_S_t_1_t12: for (int t12 = 0; t12 < 120; t12++) {	// L2502
    int32_t v1648 = v1635.read();	// L2503
    int32_t v1649 = dcred7[0];	// L2504
    ap_int<33> v1650 = v1649;	// L2505
    ap_int<33> v1651 = v1648;	// L2506
    ap_int<33> v1652 = v1650 + v1651;	// L2507
    int32_t v1653 = v1652;	// L2508
    dcred7[0] = v1653;	// L2509
    ap_uint<26> pw3;	// L2510
    pw3 = 0;	// L2511
    int32_t v1655 = sp7[0];	// L2512
    bool v1656 = v1655 < 120;	// L2513
    if (v1656) {	// L2514
      ap_uint<26> cand3;	// L2515
      cand3 = 0;	// L2516
      int32_t v1658 = sp7[0];	// L2517
      int v1659 = v1658;	// L2518
      int32_t v1660 = v1632[0][v1659];	// L2519
      ap_uint<26> v1661 = v1660;	// L2520
      ap_int<26> v1662 = cand3;	// L2521
      ap_int<26> v1663;
      ap_int<26> v1663_tmp = v1662;
      v1663_tmp(25, 0) = v1661;
      v1663 = v1663_tmp;	// L2522
      cand3 = v1663;	// L2523
      ap_int<26> v1664 = cand3;	// L2524
      bool v1665;
      ap_int<26> v1665_tmp = v1664;
      v1665 = v1665_tmp[25];	// L2525
      int32_t v1666 = v1665;	// L2526
      bool v1667 = v1666 == 0;	// L2527
      if (v1667) {	// L2528
        int32_t v1668 = sp7[0];	// L2529
        ap_int<33> v1669 = v1668;	// L2530
        ap_int<33> v1670 = v1669 + 1;	// L2531
        int32_t v1671 = v1670;	// L2532
        sp7[0] = v1671;	// L2533
      } else {
        int32_t v1672 = dcred7[0];	// L2535
        bool v1673 = v1672 > 0;	// L2536
        if (v1673) {	// L2537
          ap_int<26> v1674 = cand3;	// L2538
          pw3 = v1674;	// L2539
          int32_t v1675 = dcred7[0];	// L2540
          ap_int<33> v1676 = v1675;	// L2541
          ap_int<33> v1677 = v1676 - 1;	// L2542
          int32_t v1678 = v1677;	// L2543
          dcred7[0] = v1678;	// L2544
          int32_t v1679 = sp7[0];	// L2545
          ap_int<33> v1680 = v1679;	// L2546
          ap_int<33> v1681 = v1680 + 1;	// L2547
          int32_t v1682 = v1681;	// L2548
          sp7[0] = v1682;	// L2549
        }
      }
    }
    ap_int<26> v1683 = pw3;	// L2553
    v1634.write(v1683);	// L2554
  }
}

void rclc_w_0(
  int32_t v1684[1][120],
  int32_t v1685[1][1],
  hls::stream< int32_t >& v1686,
  hls::stream< ap_uint<26> >& v1687
) {	// L2558
  int32_t k6[1];	// L2568
  for (int v1689 = 0; v1689 < 1; v1689++) {	// L2569
    k6[v1689] = 0;	// L2569
  }
  int32_t cret4[1];	// L2570
  for (int v1691 = 0; v1691 < 1; v1691++) {	// L2571
    cret4[v1691] = 0;	// L2571
  }
  int32_t zc4;	// L2572
  zc4 = 0;	// L2573
  int32_t v1693 = v1685[0][0];	// L2574
  ap_int<33> v1694 = v1693;	// L2575
  ap_int<33> v1695 = v1694 - 1;	// L2576
  int v1696 = v1695;	// L2577
  for (int v1697 = 0; v1697 < v1696; v1697 += 1) {	// L2578
    int32_t v1698 = zc4;	// L2579
    v1686.write(v1698);	// L2580
  }
  cret4[0] = 2;	// L2582
  int32_t v1699 = cret4[0];	// L2583
  v1686.write(v1699);	// L2584
  l_S_t_1_t13: for (int t13 = 0; t13 < 120; t13++) {	// L2585
    ap_uint<26> v1701 = v1687.read();	// L2586
    ap_uint<26> pw4;	// L2587
    pw4 = v1701;	// L2588
    cret4[0] = 0;	// L2589
    ap_int<26> v1703 = pw4;	// L2590
    bool v1704;
    ap_int<26> v1704_tmp = v1703;
    v1704 = v1704_tmp[25];	// L2591
    int32_t v1705 = v1704;	// L2592
    bool v1706 = v1705 == 1;	// L2593
    if (v1706) {	// L2594
      cret4[0] = 1;	// L2595
      int32_t v1707 = k6[0];	// L2596
      bool v1708 = v1707 < 120;	// L2597
      if (v1708) {	// L2598
        ap_int<26> v1709 = pw4;	// L2599
        int32_t v1710 = v1709;	// L2600
        int32_t v1711 = v1710 & 67108863;	// L2601
        int32_t v1712 = k6[0];	// L2602
        int v1713 = v1712;	// L2603
        v1684[0][v1713] = v1711;	// L2604
        int32_t v1714 = k6[0];	// L2605
        ap_int<33> v1715 = v1714;	// L2606
        ap_int<33> v1716 = v1715 + 1;	// L2607
        int32_t v1717 = v1716;	// L2608
        k6[0] = v1717;	// L2609
      }
    }
    int32_t v1718 = cret4[0];	// L2612
    v1686.write(v1718);	// L2613
  }
}

void rclc_e_0(
  int32_t v1719[1][120],
  int32_t v1720[1][1],
  hls::stream< int32_t >& v1721,
  hls::stream< ap_uint<26> >& v1722
) {	// L2617
  int32_t k7[1];	// L2627
  for (int v1724 = 0; v1724 < 1; v1724++) {	// L2628
    k7[v1724] = 0;	// L2628
  }
  int32_t cret5[1];	// L2629
  for (int v1726 = 0; v1726 < 1; v1726++) {	// L2630
    cret5[v1726] = 0;	// L2630
  }
  int32_t zc5;	// L2631
  zc5 = 0;	// L2632
  int32_t v1728 = v1720[0][0];	// L2633
  ap_int<33> v1729 = v1728;	// L2634
  ap_int<33> v1730 = v1729 - 1;	// L2635
  int v1731 = v1730;	// L2636
  for (int v1732 = 0; v1732 < v1731; v1732 += 1) {	// L2637
    int32_t v1733 = zc5;	// L2638
    v1721.write(v1733);	// L2639
  }
  cret5[0] = 2;	// L2641
  int32_t v1734 = cret5[0];	// L2642
  v1721.write(v1734);	// L2643
  l_S_t_1_t14: for (int t14 = 0; t14 < 120; t14++) {	// L2644
    ap_uint<26> v1736 = v1722.read();	// L2645
    ap_uint<26> pw5;	// L2646
    pw5 = v1736;	// L2647
    cret5[0] = 0;	// L2648
    ap_int<26> v1738 = pw5;	// L2649
    bool v1739;
    ap_int<26> v1739_tmp = v1738;
    v1739 = v1739_tmp[25];	// L2650
    int32_t v1740 = v1739;	// L2651
    bool v1741 = v1740 == 1;	// L2652
    if (v1741) {	// L2653
      cret5[0] = 1;	// L2654
      int32_t v1742 = k7[0];	// L2655
      bool v1743 = v1742 < 120;	// L2656
      if (v1743) {	// L2657
        ap_int<26> v1744 = pw5;	// L2658
        int32_t v1745 = v1744;	// L2659
        int32_t v1746 = v1745 & 67108863;	// L2660
        int32_t v1747 = k7[0];	// L2661
        int v1748 = v1747;	// L2662
        v1719[0][v1748] = v1746;	// L2663
        int32_t v1749 = k7[0];	// L2664
        ap_int<33> v1750 = v1749;	// L2665
        ap_int<33> v1751 = v1750 + 1;	// L2666
        int32_t v1752 = v1751;	// L2667
        k7[0] = v1752;	// L2668
      }
    }
    int32_t v1753 = cret5[0];	// L2671
    v1721.write(v1753);	// L2672
  }
}

void rclc_n_0(
  int32_t v1754[1][120],
  int32_t v1755[1][1],
  hls::stream< int32_t >& v1756,
  hls::stream< ap_uint<26> >& v1757
) {	// L2676
  int32_t k8[1];	// L2686
  for (int v1759 = 0; v1759 < 1; v1759++) {	// L2687
    k8[v1759] = 0;	// L2687
  }
  int32_t cret6[1];	// L2688
  for (int v1761 = 0; v1761 < 1; v1761++) {	// L2689
    cret6[v1761] = 0;	// L2689
  }
  int32_t zc6;	// L2690
  zc6 = 0;	// L2691
  int32_t v1763 = v1755[0][0];	// L2692
  ap_int<33> v1764 = v1763;	// L2693
  ap_int<33> v1765 = v1764 - 1;	// L2694
  int v1766 = v1765;	// L2695
  for (int v1767 = 0; v1767 < v1766; v1767 += 1) {	// L2696
    int32_t v1768 = zc6;	// L2697
    v1756.write(v1768);	// L2698
  }
  cret6[0] = 2;	// L2700
  int32_t v1769 = cret6[0];	// L2701
  v1756.write(v1769);	// L2702
  l_S_t_1_t15: for (int t15 = 0; t15 < 120; t15++) {	// L2703
    ap_uint<26> v1771 = v1757.read();	// L2704
    ap_uint<26> pw6;	// L2705
    pw6 = v1771;	// L2706
    cret6[0] = 0;	// L2707
    ap_int<26> v1773 = pw6;	// L2708
    bool v1774;
    ap_int<26> v1774_tmp = v1773;
    v1774 = v1774_tmp[25];	// L2709
    int32_t v1775 = v1774;	// L2710
    bool v1776 = v1775 == 1;	// L2711
    if (v1776) {	// L2712
      cret6[0] = 1;	// L2713
      int32_t v1777 = k8[0];	// L2714
      bool v1778 = v1777 < 120;	// L2715
      if (v1778) {	// L2716
        ap_int<26> v1779 = pw6;	// L2717
        int32_t v1780 = v1779;	// L2718
        int32_t v1781 = v1780 & 67108863;	// L2719
        int32_t v1782 = k8[0];	// L2720
        int v1783 = v1782;	// L2721
        v1754[0][v1783] = v1781;	// L2722
        int32_t v1784 = k8[0];	// L2723
        ap_int<33> v1785 = v1784;	// L2724
        ap_int<33> v1786 = v1785 + 1;	// L2725
        int32_t v1787 = v1786;	// L2726
        k8[0] = v1787;	// L2727
      }
    }
    int32_t v1788 = cret6[0];	// L2730
    v1756.write(v1788);	// L2731
  }
}

void rclc_s_0(
  int32_t v1789[1][120],
  int32_t v1790[1][1],
  hls::stream< int32_t >& v1791,
  hls::stream< ap_uint<26> >& v1792
) {	// L2735
  int32_t k9[1];	// L2745
  for (int v1794 = 0; v1794 < 1; v1794++) {	// L2746
    k9[v1794] = 0;	// L2746
  }
  int32_t cret7[1];	// L2747
  for (int v1796 = 0; v1796 < 1; v1796++) {	// L2748
    cret7[v1796] = 0;	// L2748
  }
  int32_t zc7;	// L2749
  zc7 = 0;	// L2750
  int32_t v1798 = v1790[0][0];	// L2751
  ap_int<33> v1799 = v1798;	// L2752
  ap_int<33> v1800 = v1799 - 1;	// L2753
  int v1801 = v1800;	// L2754
  for (int v1802 = 0; v1802 < v1801; v1802 += 1) {	// L2755
    int32_t v1803 = zc7;	// L2756
    v1791.write(v1803);	// L2757
  }
  cret7[0] = 2;	// L2759
  int32_t v1804 = cret7[0];	// L2760
  v1791.write(v1804);	// L2761
  l_S_t_1_t16: for (int t16 = 0; t16 < 120; t16++) {	// L2762
    ap_uint<26> v1806 = v1792.read();	// L2763
    ap_uint<26> pw7;	// L2764
    pw7 = v1806;	// L2765
    cret7[0] = 0;	// L2766
    ap_int<26> v1808 = pw7;	// L2767
    bool v1809;
    ap_int<26> v1809_tmp = v1808;
    v1809 = v1809_tmp[25];	// L2768
    int32_t v1810 = v1809;	// L2769
    bool v1811 = v1810 == 1;	// L2770
    if (v1811) {	// L2771
      cret7[0] = 1;	// L2772
      int32_t v1812 = k9[0];	// L2773
      bool v1813 = v1812 < 120;	// L2774
      if (v1813) {	// L2775
        ap_int<26> v1814 = pw7;	// L2776
        int32_t v1815 = v1814;	// L2777
        int32_t v1816 = v1815 & 67108863;	// L2778
        int32_t v1817 = k9[0];	// L2779
        int v1818 = v1817;	// L2780
        v1789[0][v1818] = v1816;	// L2781
        int32_t v1819 = k9[0];	// L2782
        ap_int<33> v1820 = v1819;	// L2783
        ap_int<33> v1821 = v1820 + 1;	// L2784
        int32_t v1822 = v1821;	// L2785
        k9[0] = v1822;	// L2786
      }
    }
    int32_t v1823 = cret7[0];	// L2789
    v1791.write(v1823);	// L2790
  }
}

/// This is top function.
void top(
  int32_t v1824[1][1],
  half v1825[1][120],
  int32_t v1826[1][120],
  half v1827[1][120],
  int32_t v1828[1][120],
  half v1829[1][120],
  int32_t v1830[1][120],
  half v1831[1][120],
  int32_t v1832[1][120],
  half v1833[1][120],
  half v1834[1][120],
  half v1835[1][120],
  half v1836[1][120],
  int32_t v1837[1][120],
  int32_t v1838[1][120],
  int32_t v1839[1][120],
  int32_t v1840[1][120],
  int32_t v1841[1][120],
  int32_t v1842[1][120],
  int32_t v1843[1][120],
  int32_t v1844[1][120]
) {	// L2794
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v1845;
  #pragma HLS stream variable=v1845 depth=8	// L2795
  hls::stream< ap_uint<17> > v1846;
  #pragma HLS stream variable=v1846 depth=8	// L2796
  hls::stream< ap_uint<17> > v1847;
  #pragma HLS stream variable=v1847 depth=8	// L2797
  hls::stream< ap_uint<17> > v1848;
  #pragma HLS stream variable=v1848 depth=8	// L2798
  hls::stream< ap_uint<17> > v1849;
  #pragma HLS stream variable=v1849 depth=8	// L2799
  hls::stream< ap_uint<17> > v1850;
  #pragma HLS stream variable=v1850 depth=8	// L2800
  hls::stream< ap_uint<17> > v1851;
  #pragma HLS stream variable=v1851 depth=8	// L2801
  hls::stream< ap_uint<17> > v1852;
  #pragma HLS stream variable=v1852 depth=8	// L2802
  hls::stream< ap_uint<26> > v1853;
  #pragma HLS stream variable=v1853 depth=8	// L2803
  hls::stream< ap_uint<26> > v1854;
  #pragma HLS stream variable=v1854 depth=8	// L2804
  hls::stream< ap_uint<26> > v1855;
  #pragma HLS stream variable=v1855 depth=8	// L2805
  hls::stream< ap_uint<26> > v1856;
  #pragma HLS stream variable=v1856 depth=8	// L2806
  hls::stream< ap_uint<26> > v1857;
  #pragma HLS stream variable=v1857 depth=8	// L2807
  hls::stream< ap_uint<26> > v1858;
  #pragma HLS stream variable=v1858 depth=8	// L2808
  hls::stream< ap_uint<26> > v1859;
  #pragma HLS stream variable=v1859 depth=8	// L2809
  hls::stream< ap_uint<26> > v1860;
  #pragma HLS stream variable=v1860 depth=8	// L2810
  hls::stream< int32_t > v1861;
  #pragma HLS stream variable=v1861 depth=8	// L2811
  hls::stream< int32_t > v1862;
  #pragma HLS stream variable=v1862 depth=8	// L2812
  hls::stream< int32_t > v1863;
  #pragma HLS stream variable=v1863 depth=8	// L2813
  hls::stream< int32_t > v1864;
  #pragma HLS stream variable=v1864 depth=8	// L2814
  hls::stream< int32_t > v1865;
  #pragma HLS stream variable=v1865 depth=8	// L2815
  hls::stream< int32_t > v1866;
  #pragma HLS stream variable=v1866 depth=8	// L2816
  hls::stream< int32_t > v1867;
  #pragma HLS stream variable=v1867 depth=8	// L2817
  hls::stream< int32_t > v1868;
  #pragma HLS stream variable=v1868 depth=8	// L2818
  hls::stream< int32_t > v1869;
  #pragma HLS stream variable=v1869 depth=8	// L2819
  hls::stream< int32_t > v1870;
  #pragma HLS stream variable=v1870 depth=8	// L2820
  hls::stream< int32_t > v1871;
  #pragma HLS stream variable=v1871 depth=8	// L2821
  hls::stream< int32_t > v1872;
  #pragma HLS stream variable=v1872 depth=8	// L2822
  hls::stream< int32_t > v1873;
  #pragma HLS stream variable=v1873 depth=8	// L2823
  hls::stream< int32_t > v1874;
  #pragma HLS stream variable=v1874 depth=8	// L2824
  hls::stream< int32_t > v1875;
  #pragma HLS stream variable=v1875 depth=8	// L2825
  hls::stream< int32_t > v1876;
  #pragma HLS stream variable=v1876 depth=8	// L2826
  node_0_0(v1824, v1854, v1855, v1858, v1859, v1846, v1847, v1850, v1851, v1861, v1864, v1865, v1868, v1869, v1872, v1873, v1876, v1853, v1856, v1857, v1860, v1862, v1863, v1866, v1867, v1875, v1874, v1871, v1870, v1845, v1848, v1849, v1852);	// L2827
  drv_w_0(v1825, v1826, v1824, v1845, v1869);	// L2828
  drv_e_0(v1827, v1828, v1824, v1848, v1872);	// L2829
  drv_n_0(v1829, v1830, v1824, v1849, v1873);	// L2830
  drv_s_0(v1831, v1832, v1824, v1852, v1876);	// L2831
  col_w_0(v1833, v1824, v1871, v1847);	// L2832
  col_e_0(v1834, v1824, v1870, v1846);	// L2833
  col_n_0(v1835, v1824, v1875, v1851);	// L2834
  col_s_0(v1836, v1824, v1874, v1850);	// L2835
  rdrv_w_0(v1837, v1824, v1853, v1861);	// L2836
  rdrv_e_0(v1838, v1824, v1856, v1864);	// L2837
  rdrv_n_0(v1839, v1824, v1857, v1865);	// L2838
  rdrv_s_0(v1840, v1824, v1860, v1868);	// L2839
  rclc_w_0(v1841, v1824, v1863, v1855);	// L2840
  rclc_e_0(v1842, v1824, v1862, v1854);	// L2841
  rclc_n_0(v1843, v1824, v1867, v1859);	// L2842
  rclc_s_0(v1844, v1824, v1866, v1858);	// L2843
}

