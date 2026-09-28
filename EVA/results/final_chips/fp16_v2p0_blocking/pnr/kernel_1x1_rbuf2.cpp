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
) {	// L2
  int32_t irf[8];	// L39
  for (int v34 = 0; v34 < 8; v34++) {	// L40
    irf[v34] = 0;	// L40
  }
  half drf[8];	// L41
  for (int v36 = 0; v36 < 8; v36++) {	// L42
    drf[v36] = 0.000000;	// L42
  }
  int32_t drf_full[8];	// L43
  for (int v38 = 0; v38 < 8; v38++) {	// L44
    drf_full[v38] = 0;	// L44
  }
  int32_t dsmask;	// L45
  dsmask = 0;	// L46
  int32_t crv_vld;	// L47
  crv_vld = 0;	// L48
  half crv_data;	// L49
  crv_data = 0.000000;	// L50
  int32_t crv_addr;	// L51
  crv_addr = 0;	// L52
  int32_t crv_mode;	// L53
  crv_mode = 0;	// L54
  int32_t crv_raw;	// L55
  crv_raw = 0;	// L56
  int32_t csd_vld;	// L57
  csd_vld = 0;	// L58
  ap_uint<26> csd_pkt;	// L59
  csd_pkt = 0;	// L60
  int32_t csd_dir;	// L61
  csd_dir = 0;	// L62
  int32_t row_id;	// L63
  row_id = 0;	// L64
  int32_t col_id;	// L65
  col_id = 0;	// L66
  ap_uint<26> oe_r;	// L67
  oe_r = 0;	// L68
  ap_uint<26> ow_r;	// L69
  ow_r = 0;	// L70
  ap_uint<26> on_r;	// L71
  on_r = 0;	// L72
  ap_uint<26> os_r;	// L73
  os_r = 0;	// L74
  ap_uint<17> txn_r;	// L75
  txn_r = 0;	// L76
  ap_uint<17> txs_r;	// L77
  txs_r = 0;	// L78
  ap_uint<17> txw_r;	// L79
  txw_r = 0;	// L80
  ap_uint<17> txe_r;	// L81
  txe_r = 0;	// L82
  half hold_v[4][2];	// L83
  for (int v59 = 0; v59 < 4; v59++) {	// L84
    for (int v60 = 0; v60 < 2; v60++) {	// L84
      hold_v[v59][v60] = 0.000000;	// L84
    }
  }
  uint8_t hold_cnt[4];	// L85
  for (int v62 = 0; v62 < 4; v62++) {	// L86
    hold_cnt[v62] = 0;	// L86
  }
  ap_uint<26> rbuf[4][2];	// L87
  for (int v64 = 0; v64 < 4; v64++) {	// L88
    for (int v65 = 0; v65 < 2; v65++) {	// L88
      rbuf[v64][v65] = 0;	// L88
    }
  }
  uint8_t rbcnt[4];	// L89
  for (int v67 = 0; v67 < 4; v67++) {	// L90
    rbcnt[v67] = 0;	// L90
  }
  uint8_t rcred[4];	// L91
  for (int v69 = 0; v69 < 4; v69++) {	// L92
    rcred[v69] = 0;	// L92
  }
  int32_t cre_r;	// L93
  cre_r = 2;	// L94
  int32_t crw_r;	// L95
  crw_r = 2;	// L96
  int32_t crs_r;	// L97
  crs_r = 2;	// L98
  int32_t crn_r;	// L99
  crn_r = 2;	// L100
  int32_t scred[4];	// L101
  for (int v75 = 0; v75 < 4; v75++) {	// L102
    scred[v75] = 0;	// L102
  }
  int32_t txp_v[4];	// L103
  for (int v77 = 0; v77 < 4; v77++) {	// L104
    txp_v[v77] = 0;	// L104
  }
  half txp_d[4];	// L105
  for (int v79 = 0; v79 < 4; v79++) {	// L106
    txp_d[v79] = 0.000000;	// L106
  }
  int32_t sc_r[4];	// L107
  for (int v81 = 0; v81 < 4; v81++) {	// L108
    sc_r[v81] = 2;	// L108
  }
  int32_t cfg_isz;	// L109
  cfg_isz = 0;	// L110
  int32_t cfg_itsz;	// L111
  cfg_itsz = 0;	// L112
  uint8_t fetch_en;	// L113
  fetch_en = 0;	// L114
  uint8_t instr_cnt;	// L115
  instr_cnt = 0;	// L116
  uint8_t iter_cnt;	// L117
  iter_cnt = 0;	// L118
  uint8_t condition_reg;	// L119
  condition_reg = 0;	// L120
  uint8_t sb_v[5];	// L121
  for (int v89 = 0; v89 < 5; v89++) {	// L122
    sb_v[v89] = 0;	// L122
  }
  uint8_t sb_dst[5];	// L123
  for (int v91 = 0; v91 < 5; v91++) {	// L124
    sb_dst[v91] = 0;	// L124
  }
  uint8_t sb_cmp[5];	// L125
  for (int v93 = 0; v93 < 5; v93++) {	// L126
    sb_cmp[v93] = 0;	// L126
  }
  uint8_t sb_rtr[5];	// L127
  for (int v95 = 0; v95 < 5; v95++) {	// L128
    sb_rtr[v95] = 0;	// L128
  }
  uint8_t sb_inj[5];	// L129
  for (int v97 = 0; v97 < 5; v97++) {	// L130
    sb_inj[v97] = 0;	// L130
  }
  uint8_t sb_dir[5];	// L131
  for (int v99 = 0; v99 < 5; v99++) {	// L132
    sb_dir[v99] = 0;	// L132
  }
  uint8_t sb_id[5];	// L133
  for (int v101 = 0; v101 < 5; v101++) {	// L134
    sb_id[v101] = 0;	// L134
  }
  uint8_t sb_rvld[5];	// L135
  for (int v103 = 0; v103 < 5; v103++) {	// L136
    sb_rvld[v103] = 0;	// L136
  }
  uint8_t sb_ix[5];	// L137
  for (int v105 = 0; v105 < 5; v105++) {	// L138
    sb_ix[v105] = 0;	// L138
  }
  uint8_t sb_long[5];	// L139
  for (int v107 = 0; v107 < 5; v107++) {	// L140
    sb_long[v107] = 0;	// L140
  }
  half resq[8];	// L141
  for (int v109 = 0; v109 < 8; v109++) {	// L142
    resq[v109] = 0.000000;	// L142
  }
  uint8_t cmpq[8];	// L143
  for (int v111 = 0; v111 < 8; v111++) {	// L144
    cmpq[v111] = 0;	// L144
  }
  uint8_t resq_wr;	// L145
  resq_wr = 0;	// L146
  ap_uint<26> zpkt;	// L147
  zpkt = 0;	// L148
  ap_uint<17> zsys;	// L149
  zsys = 0;	// L150
  int32_t zcr;	// L151
  zcr = 0;	// L152
  int32_t v116 = v0[0][0];	// L153
  ap_int<33> v117 = v116;	// L154
  ap_int<33> v118 = v117 - 1;	// L155
  int v119 = v118;	// L156
  for (int v120 = 0; v120 < v119; v120 += 1) {	// L157
    ap_int<26> v121 = zpkt;	// L158
    v1.write(v121);	// L159
    ap_int<26> v122 = zpkt;	// L160
    v2.write(v122);	// L161
    ap_int<26> v123 = zpkt;	// L162
    v3.write(v123);	// L163
    ap_int<26> v124 = zpkt;	// L164
    v4.write(v124);	// L165
    ap_int<17> v125 = zsys;	// L166
    v5.write(v125);	// L167
    ap_int<17> v126 = zsys;	// L168
    v6.write(v126);	// L169
    ap_int<17> v127 = zsys;	// L170
    v7.write(v127);	// L171
    ap_int<17> v128 = zsys;	// L172
    v8.write(v128);	// L173
    int32_t v129 = zcr;	// L174
    v9.write(v129);	// L175
    int32_t v130 = zcr;	// L176
    v10.write(v130);	// L177
    int32_t v131 = zcr;	// L178
    v11.write(v131);	// L179
    int32_t v132 = zcr;	// L180
    v12.write(v132);	// L181
    int32_t v133 = zcr;	// L182
    v13.write(v133);	// L183
    int32_t v134 = zcr;	// L184
    v14.write(v134);	// L185
    int32_t v135 = zcr;	// L186
    v15.write(v135);	// L187
    int32_t v136 = zcr;	// L188
    v16.write(v136);	// L189
  }
  ap_int<26> v137 = oe_r;	// L191
  v1.write(v137);	// L192
  ap_int<26> v138 = ow_r;	// L193
  v2.write(v138);	// L194
  ap_int<26> v139 = os_r;	// L195
  v3.write(v139);	// L196
  ap_int<26> v140 = on_r;	// L197
  v4.write(v140);	// L198
  ap_int<17> v141 = txe_r;	// L199
  v5.write(v141);	// L200
  ap_int<17> v142 = txw_r;	// L201
  v6.write(v142);	// L202
  ap_int<17> v143 = txs_r;	// L203
  v7.write(v143);	// L204
  ap_int<17> v144 = txn_r;	// L205
  v8.write(v144);	// L206
  int32_t v145 = cre_r;	// L207
  v9.write(v145);	// L208
  int32_t v146 = crw_r;	// L209
  v10.write(v146);	// L210
  int32_t v147 = crs_r;	// L211
  v11.write(v147);	// L212
  int32_t v148 = crn_r;	// L213
  v12.write(v148);	// L214
  int32_t v149 = sc_r[0];	// L215
  v15.write(v149);	// L216
  int32_t v150 = sc_r[1];	// L217
  v16.write(v150);	// L218
  int32_t v151 = sc_r[2];	// L219
  v13.write(v151);	// L220
  int32_t v152 = sc_r[3];	// L221
  v14.write(v152);	// L222
  l_S_t_1_t: for (int t = 0; t < 2000; t++) {	// L223
  #pragma HLS pipeline II=1
  #pragma HLS array_partition variable=cmpq complete dim=1
  #pragma HLS array_partition variable=drf complete dim=1
  #pragma HLS array_partition variable=drf_full complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=2
  #pragma HLS array_partition variable=rbcnt complete dim=1
  #pragma HLS array_partition variable=rcred complete dim=1
  #pragma HLS array_partition variable=scred complete dim=1
  #pragma HLS array_partition variable=hold_cnt complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=2
  #pragma HLS array_partition variable=irf complete dim=1
  #pragma HLS array_partition variable=resq complete dim=1
  #pragma HLS array_partition variable=sb_cmp complete dim=1
  #pragma HLS array_partition variable=sb_dir complete dim=1
  #pragma HLS array_partition variable=sb_dst complete dim=1
  #pragma HLS array_partition variable=sb_id complete dim=1
  #pragma HLS array_partition variable=sb_inj complete dim=1
  #pragma HLS array_partition variable=sb_ix complete dim=1
  #pragma HLS array_partition variable=sb_long complete dim=1
  #pragma HLS array_partition variable=sb_rtr complete dim=1
  #pragma HLS array_partition variable=sb_rvld complete dim=1
  #pragma HLS array_partition variable=sb_v complete dim=1
  #pragma HLS array_partition variable=txp_d complete dim=1
  #pragma HLS array_partition variable=txp_v complete dim=1
    ap_uint<26> v154 = v17.read();	// L224
    ap_uint<26> p_w;	// L225
    p_w = v154;	// L226
    ap_uint<26> v156 = v18.read();	// L227
    ap_uint<26> p_e;	// L228
    p_e = v156;	// L229
    ap_uint<26> v158 = v19.read();	// L230
    ap_uint<26> p_n;	// L231
    p_n = v158;	// L232
    ap_uint<26> v160 = v20.read();	// L233
    ap_uint<26> p_s;	// L234
    p_s = v160;	// L235
    int32_t v162 = v21.read();	// L236
    int32_t cg0;	// L237
    cg0 = v162;	// L238
    int32_t v164 = cg0;	// L239
    uint8_t v165 = rcred[0];	// L240
    ap_int<33> v166 = v165;	// L241
    ap_int<33> v167 = v164;	// L242
    ap_int<33> v168 = v166 + v167;	// L243
    uint8_t v169 = v168;	// L244
    rcred[0] = v169;	// L245
    int32_t v170 = v22.read();	// L246
    int32_t cg1;	// L247
    cg1 = v170;	// L248
    int32_t v172 = cg1;	// L249
    uint8_t v173 = rcred[1];	// L250
    ap_int<33> v174 = v173;	// L251
    ap_int<33> v175 = v172;	// L252
    ap_int<33> v176 = v174 + v175;	// L253
    uint8_t v177 = v176;	// L254
    rcred[1] = v177;	// L255
    int32_t v178 = v23.read();	// L256
    int32_t cg2;	// L257
    cg2 = v178;	// L258
    int32_t v180 = cg2;	// L259
    uint8_t v181 = rcred[2];	// L260
    ap_int<33> v182 = v181;	// L261
    ap_int<33> v183 = v180;	// L262
    ap_int<33> v184 = v182 + v183;	// L263
    uint8_t v185 = v184;	// L264
    rcred[2] = v185;	// L265
    int32_t v186 = v24.read();	// L266
    int32_t cg3;	// L267
    cg3 = v186;	// L268
    int32_t v188 = cg3;	// L269
    uint8_t v189 = rcred[3];	// L270
    ap_int<33> v190 = v189;	// L271
    ap_int<33> v191 = v188;	// L272
    ap_int<33> v192 = v190 + v191;	// L273
    uint8_t v193 = v192;	// L274
    rcred[3] = v193;	// L275
    int32_t v194 = v25.read();	// L276
    int32_t cg4;	// L277
    cg4 = v194;	// L278
    int32_t v196 = cg4;	// L279
    int32_t v197 = scred[0];	// L280
    ap_int<33> v198 = v197;	// L281
    ap_int<33> v199 = v196;	// L282
    ap_int<33> v200 = v198 + v199;	// L283
    int32_t v201 = v200;	// L284
    scred[0] = v201;	// L285
    int32_t v202 = v26.read();	// L286
    int32_t cg5;	// L287
    cg5 = v202;	// L288
    int32_t v204 = cg5;	// L289
    int32_t v205 = scred[1];	// L290
    ap_int<33> v206 = v205;	// L291
    ap_int<33> v207 = v204;	// L292
    ap_int<33> v208 = v206 + v207;	// L293
    int32_t v209 = v208;	// L294
    scred[1] = v209;	// L295
    int32_t v210 = v27.read();	// L296
    int32_t cg6;	// L297
    cg6 = v210;	// L298
    int32_t v212 = cg6;	// L299
    int32_t v213 = scred[2];	// L300
    ap_int<33> v214 = v213;	// L301
    ap_int<33> v215 = v212;	// L302
    ap_int<33> v216 = v214 + v215;	// L303
    int32_t v217 = v216;	// L304
    scred[2] = v217;	// L305
    int32_t v218 = v28.read();	// L306
    int32_t cg7;	// L307
    cg7 = v218;	// L308
    int32_t v220 = cg7;	// L309
    int32_t v221 = scred[3];	// L310
    ap_int<33> v222 = v221;	// L311
    ap_int<33> v223 = v220;	// L312
    ap_int<33> v224 = v222 + v223;	// L313
    int32_t v225 = v224;	// L314
    scred[3] = v225;	// L315
    ap_uint<26> fin[4];	// L316
    for (int v227 = 0; v227 < 4; v227++) {	// L317
      fin[v227] = 0;	// L317
    }
    ap_int<26> v228 = p_w;	// L318
    fin[0] = v228;	// L319
    ap_int<26> v229 = p_e;	// L320
    fin[1] = v229;	// L321
    ap_int<26> v230 = p_n;	// L322
    fin[2] = v230;	// L323
    ap_int<26> v231 = p_s;	// L324
    fin[3] = v231;	// L325
    l_S_d_1_d: for (int d = 0; d < 4; d++) {	// L326
      ap_uint<26> v233 = fin[d];	// L327
      bool v234;
      ap_int<26> v234_tmp = v233;
      v234 = v234_tmp[25];	// L328
      int32_t v235 = v234;	// L329
      bool v236 = v235 == 1;	// L330
      uint8_t v237 = rbcnt[d];	// L331
      int32_t v238 = v237;	// L332
      bool v239 = v238 < 2;	// L333
      bool v240 = v236 & v239;	// L334
      if (v240) {	// L335
        ap_uint<26> v241 = fin[d];	// L336
        uint8_t v242 = rbcnt[d];	// L337
        int v243 = v242;	// L338
        rbuf[d][v243] = v241;	// L339
        uint8_t v244 = rbcnt[d];	// L340
        ap_int<33> v245 = v244;	// L341
        ap_int<33> v246 = v245 + 1;	// L342
        uint8_t v247 = v246;	// L343
        rbcnt[d] = v247;	// L344
      }
    }
    ap_uint<26> hd[4];	// L347
    for (int v249 = 0; v249 < 4; v249++) {	// L348
      hd[v249] = 0;	// L348
    }
    int32_t hvld[4];	// L349
    for (int v251 = 0; v251 < 4; v251++) {	// L350
      hvld[v251] = 0;	// L350
    }
    int32_t hit[4];	// L351
    for (int v253 = 0; v253 < 4; v253++) {	// L352
      hit[v253] = 0;	// L352
    }
    int32_t axis[4];	// L353
    for (int v255 = 0; v255 < 4; v255++) {	// L354
      axis[v255] = 0;	// L354
    }
    int32_t v256 = col_id;	// L355
    axis[0] = v256;	// L356
    int32_t v257 = col_id;	// L357
    axis[1] = v257;	// L358
    int32_t v258 = row_id;	// L359
    axis[2] = v258;	// L360
    int32_t v259 = row_id;	// L361
    axis[3] = v259;	// L362
    l_S_d_2_d1: for (int d1 = 0; d1 < 4; d1++) {	// L363
      uint8_t v261 = rbcnt[d1];	// L364
      int32_t v262 = v261;	// L365
      bool v263 = v262 > 0;	// L366
      if (v263) {	// L367
        ap_uint<26> v264 = rbuf[d1][0];	// L368
        hd[d1] = v264;	// L369
        hvld[d1] = 1;	// L370
        ap_uint<26> v265 = hd[d1];	// L371
        ap_int<4> v266;
        ap_int<26> v266_tmp = v265;
        v266 = v266_tmp(24, 21);	// L372
        int32_t v267 = axis[d1];	// L373
        int32_t v268 = v266;	// L374
        bool v269 = v268 == v267;	// L375
        if (v269) {	// L376
          hit[d1] = 1;	// L377
        }
      }
    }
    ap_uint<26> o_crv;	// L381
    o_crv = 0;	// L382
    int32_t crv_in;	// L383
    crv_in = -1;	// L384
    int32_t v272 = hit[3];	// L385
    bool v273 = v272 == 1;	// L386
    if (v273) {	// L387
      ap_uint<26> v274 = hd[3];	// L388
      o_crv = v274;	// L389
      crv_in = 3;	// L390
    } else {
      int32_t v275 = hit[2];	// L392
      bool v276 = v275 == 1;	// L393
      if (v276) {	// L394
        ap_uint<26> v277 = hd[2];	// L395
        o_crv = v277;	// L396
        crv_in = 2;	// L397
      } else {
        int32_t v278 = hit[1];	// L399
        bool v279 = v278 == 1;	// L400
        if (v279) {	// L401
          ap_uint<26> v280 = hd[1];	// L402
          o_crv = v280;	// L403
          crv_in = 1;	// L404
        } else {
          int32_t v281 = hit[0];	// L406
          bool v282 = v281 == 1;	// L407
          if (v282) {	// L408
            ap_uint<26> v283 = hd[0];	// L409
            o_crv = v283;	// L410
            crv_in = 0;	// L411
          }
        }
      }
    }
    ap_uint<26> o_out[4];	// L416
    for (int v285 = 0; v285 < 4; v285++) {	// L417
      o_out[v285] = 0;	// L417
    }
    int32_t pop[4];	// L418
    for (int v287 = 0; v287 < 4; v287++) {	// L419
      pop[v287] = 0;	// L419
    }
    int32_t inj_done;	// L420
    inj_done = 0;	// L421
    int32_t idir;	// L422
    idir = -1;	// L423
    ap_int<26> v290 = csd_pkt;	// L424
    bool v291;
    ap_int<26> v291_tmp = v290;
    v291 = v291_tmp[25];	// L425
    int32_t v292 = v291;	// L426
    bool v293 = v292 == 1;	// L427
    if (v293) {	// L428
      int32_t v294 = csd_dir;	// L429
      ap_int<33> v295 = v294;	// L430
      ap_int<33> v296 = 3 - v295;	// L431
      int32_t v297 = v296;	// L432
      idir = v297;	// L433
    }
    l_S_o_3_o: for (int o = 0; o < 4; o++) {	// L435
      uint8_t v299 = rcred[o];	// L436
      int32_t v300 = v299;	// L437
      bool v301 = v300 > 0;	// L438
      if (v301) {	// L439
        int32_t v302 = idir;	// L440
        ap_int<33> v303 = v302;	// L441
        ap_int<33> v304 = o;	// L442
        bool v305 = v303 == v304;	// L443
        if (v305) {	// L444
          ap_int<26> v306 = csd_pkt;	// L445
          o_out[o] = v306;	// L446
          uint8_t v307 = rcred[o];	// L447
          ap_int<33> v308 = v307;	// L448
          ap_int<33> v309 = v308 - 1;	// L449
          uint8_t v310 = v309;	// L450
          rcred[o] = v310;	// L451
          inj_done = 1;	// L452
        } else {
          int32_t v311 = hvld[o];	// L454
          bool v312 = v311 == 1;	// L455
          int32_t v313 = hit[o];	// L456
          bool v314 = v313 == 0;	// L457
          bool v315 = v312 & v314;	// L458
          if (v315) {	// L459
            ap_uint<26> v316 = hd[o];	// L460
            o_out[o] = v316;	// L461
            uint8_t v317 = rcred[o];	// L462
            ap_int<33> v318 = v317;	// L463
            ap_int<33> v319 = v318 - 1;	// L464
            uint8_t v320 = v319;	// L465
            rcred[o] = v320;	// L466
            pop[o] = 1;	// L467
          }
        }
      }
    }
    int32_t v321 = crv_in;	// L472
    bool v322 = v321 >= 0;	// L473
    if (v322) {	// L474
      int32_t v323 = crv_in;	// L475
      int v324 = v323;	// L476
      pop[v324] = 1;	// L477
    }
    int32_t ret[4];	// L479
    for (int v326 = 0; v326 < 4; v326++) {	// L480
      ret[v326] = 0;	// L480
    }
    l_S_d_4_d2: for (int d2 = 0; d2 < 4; d2++) {	// L481
      int32_t v328 = pop[d2];	// L482
      bool v329 = v328 == 1;	// L483
      if (v329) {	// L484
        l_S_sft_4_sft: for (int sft = 0; sft < 1; sft++) {	// L485
          ap_uint<26> v331 = rbuf[d2][(sft + 1)];	// L486
          rbuf[d2][sft] = v331;	// L487
        }
        uint8_t v332 = rbcnt[d2];	// L489
        ap_int<33> v333 = v332;	// L490
        ap_int<33> v334 = v333 - 1;	// L491
        uint8_t v335 = v334;	// L492
        rbcnt[d2] = v335;	// L493
        ret[d2] = 1;	// L494
      }
    }
    int32_t v336 = ret[0];	// L497
    cre_r = v336;	// L498
    int32_t v337 = ret[1];	// L499
    crw_r = v337;	// L500
    int32_t v338 = ret[2];	// L501
    crs_r = v338;	// L502
    int32_t v339 = ret[3];	// L503
    crn_r = v339;	// L504
    ap_uint<26> v340 = o_out[0];	// L505
    oe_r = v340;	// L506
    ap_uint<26> v341 = o_out[1];	// L507
    ow_r = v341;	// L508
    ap_uint<26> v342 = o_out[2];	// L509
    os_r = v342;	// L510
    ap_uint<26> v343 = o_out[3];	// L511
    on_r = v343;	// L512
    int32_t v344 = inj_done;	// L513
    bool v345 = v344 == 1;	// L514
    if (v345) {	// L515
      csd_pkt = 0;	// L516
    }
    ap_int<26> v346 = o_crv;	// L518
    bool v347;
    ap_int<26> v347_tmp = v346;
    v347 = v347_tmp[25];	// L519
    int32_t v348 = v347;	// L520
    crv_vld = v348;	// L521
    ap_int<26> v349 = o_crv;	// L522
    int16_t v350;
    ap_int<26> v350_tmp = v349;
    v350 = v350_tmp(15, 0);	// L523
    half v351;
    union { uint16_t from; half to;} _converter_v350_to_v351 = {};
    _converter_v350_to_v351.from = v350;
    v351 = _converter_v350_to_v351.to;	// L524
    crv_data = v351;	// L525
    ap_int<26> v352 = o_crv;	// L526
    ap_int<4> v353;
    ap_int<26> v353_tmp = v352;
    v353 = v353_tmp(19, 16);	// L527
    int32_t v354 = v353;	// L528
    crv_addr = v354;	// L529
    ap_int<26> v355 = o_crv;	// L530
    bool v356;
    ap_int<26> v356_tmp = v355;
    v356 = v356_tmp[20];	// L531
    int32_t v357 = v356;	// L532
    crv_mode = v357;	// L533
    ap_int<26> v358 = o_crv;	// L534
    int16_t v359;
    ap_int<26> v359_tmp = v358;
    v359 = v359_tmp(15, 0);	// L535
    int32_t v360 = v359;	// L536
    crv_raw = v360;	// L537
    ap_uint<17> v361 = v29.read();	// L538
    ap_uint<17> rx_w;	// L539
    rx_w = v361;	// L540
    ap_uint<17> v363 = v30.read();	// L541
    ap_uint<17> rx_e;	// L542
    rx_e = v363;	// L543
    ap_uint<17> v365 = v31.read();	// L544
    ap_uint<17> rx_n;	// L545
    rx_n = v365;	// L546
    ap_uint<17> v367 = v32.read();	// L547
    ap_uint<17> rx_s;	// L548
    rx_s = v367;	// L549
    half rxv[4];	// L550
    for (int v370 = 0; v370 < 4; v370++) {	// L551
      rxv[v370] = 0.000000;	// L551
    }
    int32_t rxvld[4];	// L552
    for (int v372 = 0; v372 < 4; v372++) {	// L553
      rxvld[v372] = 0;	// L553
    }
    ap_int<17> v373 = rx_n;	// L554
    int16_t v374;
    ap_int<17> v374_tmp = v373;
    v374 = v374_tmp(16, 1);	// L555
    half v375;
    union { uint16_t from; half to;} _converter_v374_to_v375 = {};
    _converter_v374_to_v375.from = v374;
    v375 = _converter_v374_to_v375.to;	// L556
    rxv[0] = v375;	// L557
    ap_int<17> v376 = rx_n;	// L558
    bool v377;
    ap_int<17> v377_tmp = v376;
    v377 = v377_tmp[0];	// L559
    int32_t v378 = v377;	// L560
    rxvld[0] = v378;	// L561
    ap_int<17> v379 = rx_s;	// L562
    int16_t v380;
    ap_int<17> v380_tmp = v379;
    v380 = v380_tmp(16, 1);	// L563
    half v381;
    union { uint16_t from; half to;} _converter_v380_to_v381 = {};
    _converter_v380_to_v381.from = v380;
    v381 = _converter_v380_to_v381.to;	// L564
    rxv[1] = v381;	// L565
    ap_int<17> v382 = rx_s;	// L566
    bool v383;
    ap_int<17> v383_tmp = v382;
    v383 = v383_tmp[0];	// L567
    int32_t v384 = v383;	// L568
    rxvld[1] = v384;	// L569
    ap_int<17> v385 = rx_w;	// L570
    int16_t v386;
    ap_int<17> v386_tmp = v385;
    v386 = v386_tmp(16, 1);	// L571
    half v387;
    union { uint16_t from; half to;} _converter_v386_to_v387 = {};
    _converter_v386_to_v387.from = v386;
    v387 = _converter_v386_to_v387.to;	// L572
    rxv[2] = v387;	// L573
    ap_int<17> v388 = rx_w;	// L574
    bool v389;
    ap_int<17> v389_tmp = v388;
    v389 = v389_tmp[0];	// L575
    int32_t v390 = v389;	// L576
    rxvld[2] = v390;	// L577
    ap_int<17> v391 = rx_e;	// L578
    int16_t v392;
    ap_int<17> v392_tmp = v391;
    v392 = v392_tmp(16, 1);	// L579
    half v393;
    union { uint16_t from; half to;} _converter_v392_to_v393 = {};
    _converter_v392_to_v393.from = v392;
    v393 = _converter_v392_to_v393.to;	// L580
    rxv[3] = v393;	// L581
    ap_int<17> v394 = rx_e;	// L582
    bool v395;
    ap_int<17> v395_tmp = v394;
    v395 = v395_tmp[0];	// L583
    int32_t v396 = v395;	// L584
    rxvld[3] = v396;	// L585
    l_S_d_6_d3: for (int d3 = 0; d3 < 4; d3++) {	// L586
      int32_t v398 = rxvld[d3];	// L587
      bool v399 = v398 == 1;	// L588
      uint8_t v400 = hold_cnt[d3];	// L589
      int32_t v401 = v400;	// L590
      bool v402 = v401 < 2;	// L591
      bool v403 = v399 & v402;	// L592
      if (v403) {	// L593
        half v404 = rxv[d3];	// L594
        uint8_t v405 = hold_cnt[d3];	// L595
        int v406 = v405;	// L596
        hold_v[d3][v406] = v404;	// L597
        uint8_t v407 = hold_cnt[d3];	// L598
        ap_int<33> v408 = v407;	// L599
        ap_int<33> v409 = v408 + 1;	// L600
        uint8_t v410 = v409;	// L601
        hold_cnt[d3] = v410;	// L602
      }
    }
    int32_t retire_ok;	// L605
    retire_ok = 1;	// L606
    uint8_t v412 = sb_v[0];	// L607
    int32_t v413 = v412;	// L608
    bool v414 = v413 == 1;	// L609
    uint8_t v415 = sb_rtr[0];	// L610
    int32_t v416 = v415;	// L611
    bool v417 = v416 == 0;	// L612
    uint8_t v418 = sb_dst[0];	// L613
    int32_t v419 = v418;	// L614
    bool v420 = v419 >= 12;	// L615
    bool v421 = v414 & v417;	// L616
    bool v422 = v421 & v420;	// L617
    if (v422) {	// L618
      uint8_t v423 = sb_rvld[0];	// L619
      int32_t v424 = v423;	// L620
      bool v425 = v424 == 1;	// L621
      uint8_t v426 = sb_dst[0];	// L622
      int32_t v427 = v426;	// L623
      int32_t v428 = v427 & 3;	// L624
      int v429 = v428;	// L625
      int32_t v430 = txp_v[v429];	// L626
      bool v431 = v430 == 1;	// L627
      bool v432 = v425 & v431;	// L628
      if (v432) {	// L629
        retire_ok = 0;	// L630
      }
    }
    uint8_t v433 = sb_v[0];	// L633
    int32_t v434 = v433;	// L634
    bool v435 = v434 == 1;	// L635
    int32_t v436 = retire_ok;	// L636
    bool v437 = v436 == 1;	// L637
    bool v438 = v435 & v437;	// L638
    if (v438) {	// L639
      uint8_t v439 = sb_ix[0];	// L640
      int v440 = v439;	// L641
      half v441 = resq[v440];	// L642
      half wb;	// L643
      wb = v441;	// L644
      uint8_t v443 = sb_cmp[0];	// L645
      int32_t v444 = v443;	// L646
      bool v445 = v444 == 1;	// L647
      if (v445) {	// L648
        uint8_t v446 = sb_ix[0];	// L649
        int v447 = v446;	// L650
        uint8_t v448 = cmpq[v447];	// L651
        condition_reg = v448;	// L652
      }
      uint8_t v449 = sb_rtr[0];	// L654
      int32_t v450 = v449;	// L655
      bool v451 = v450 == 1;	// L656
      if (v451) {	// L657
        uint8_t v452 = sb_inj[0];	// L658
        int32_t v453 = v452;	// L659
        bool v454 = v453 == 1;	// L660
        ap_int<26> v455 = csd_pkt;	// L661
        bool v456;
        ap_int<26> v456_tmp = v455;
        v456 = v456_tmp[25];	// L662
        int32_t v457 = v456;	// L663
        bool v458 = v457 == 0;	// L664
        bool v459 = v454 & v458;	// L665
        if (v459) {	// L666
          half v460 = wb;	// L667
          uint16_t v461;
          union { half from; uint16_t to;} _converter_v460_to_v461 = {};
          _converter_v460_to_v461.from = v460;
          v461 = _converter_v460_to_v461.to;	// L668
          ap_int<26> v462 = csd_pkt;	// L669
          ap_int<26> v463;
          ap_int<26> v463_tmp = v462;
          v463_tmp(15, 0) = v461;
          v463 = v463_tmp;	// L670
          csd_pkt = v463;	// L671
          uint8_t v464 = sb_dst[0];	// L672
          ap_uint<4> v465 = v464;	// L673
          ap_int<26> v466 = csd_pkt;	// L674
          ap_int<26> v467;
          ap_int<26> v467_tmp = v466;
          v467_tmp(19, 16) = v465;
          v467 = v467_tmp;	// L675
          csd_pkt = v467;	// L676
          uint8_t v468 = sb_id[0];	// L677
          ap_uint<4> v469 = v468;	// L678
          ap_int<26> v470 = csd_pkt;	// L679
          ap_int<26> v471;
          ap_int<26> v471_tmp = v470;
          v471_tmp(24, 21) = v469;
          v471 = v471_tmp;	// L680
          csd_pkt = v471;	// L681
          uint8_t v472 = sb_rvld[0];	// L682
          bool v473 = v472;	// L683
          ap_int<26> v474 = csd_pkt;	// L684
          ap_int<26> v475;
          ap_int<26> v475_tmp = v474;
          v475_tmp[25] = v473;          v475 = v475_tmp;	// L685
          csd_pkt = v475;	// L686
          uint8_t v476 = sb_dir[0];	// L687
          int32_t v477 = v476;	// L688
          csd_dir = v477;	// L689
        }
      } else {
        uint8_t v478 = sb_dst[0];	// L692
        int32_t v479 = v478;	// L693
        bool v480 = v479 >= 12;	// L694
        if (v480) {	// L695
          uint8_t v481 = sb_rvld[0];	// L696
          int32_t v482 = v481;	// L697
          bool v483 = v482 == 1;	// L698
          if (v483) {	// L699
            uint8_t v484 = sb_dst[0];	// L700
            int32_t v485 = v484;	// L701
            int32_t v486 = v485 & 3;	// L702
            int v487 = v486;	// L703
            txp_v[v487] = 1;	// L704
            half v488 = wb;	// L705
            uint8_t v489 = sb_dst[0];	// L706
            int32_t v490 = v489;	// L707
            int32_t v491 = v490 & 3;	// L708
            int v492 = v491;	// L709
            txp_d[v492] = v488;	// L710
          }
        } else {
          uint8_t v493 = sb_rvld[0];	// L713
          int32_t v494 = v493;	// L714
          bool v495 = v494 == 1;	// L715
          if (v495) {	// L716
            uint8_t v496 = sb_dst[0];	// L717
            int32_t v497 = v496;	// L718
            bool v498 = v497 < 8;	// L719
            int32_t v499 = dsmask;	// L720
            int32_t v500 = v499 >> v497;	// L723
            int32_t v501 = v500 & 1;	// L724
            bool v502 = v501 == 1;	// L725
            bool v503 = v498 & v502;	// L726
            if (v503) {	// L727
              uint8_t v504 = sb_dst[0];	// L728
              int v505 = v504;	// L729
              int32_t v506 = drf_full[v505];	// L730
              bool v507 = v506 == 0;	// L731
              if (v507) {	// L732
                half v508 = wb;	// L733
                uint8_t v509 = sb_dst[0];	// L734
                int v510 = v509;	// L735
                drf[v510] = v508;	// L736
                uint8_t v511 = sb_dst[0];	// L737
                int v512 = v511;	// L738
                drf_full[v512] = 1;	// L739
              }
            } else {
              half v513 = wb;	// L742
              uint8_t v514 = sb_dst[0];	// L743
              int32_t v515 = v514;	// L744
              int32_t v516 = v515 & 7;	// L745
              int v517 = v516;	// L746
              drf[v517] = v513;	// L747
            }
          }
        }
      }
    }
    int32_t pc;	// L753
    pc = -1;	// L754
    int8_t v519 = fetch_en;	// L755
    int32_t v520 = v519;	// L756
    bool v521 = v520 == 1;	// L757
    if (v521) {	// L758
      int8_t v522 = instr_cnt;	// L759
      int32_t v523 = v522;	// L760
      pc = v523;	// L761
    }
    int32_t instr;	// L763
    instr = 0;	// L764
    int32_t v525 = pc;	// L765
    bool v526 = v525 >= 0;	// L766
    if (v526) {	// L767
      int32_t v527 = pc;	// L768
      int v528 = v527;	// L769
      int32_t v529 = irf[v528];	// L770
      instr = v529;	// L771
    }
    int32_t v530 = instr;	// L773
    int32_t v531 = v530 & 15;	// L774
    int32_t op;	// L775
    op = v531;	// L776
    int32_t v533 = instr;	// L777
    int32_t v534 = v533 >> 4;	// L778
    int32_t v535 = v534 & 15;	// L779
    int32_t dst;	// L780
    dst = v535;	// L781
    int32_t v537 = instr;	// L782
    int32_t v538 = v537 >> 8;	// L783
    int32_t v539 = v538 & 15;	// L784
    int32_t s1;	// L785
    s1 = v539;	// L786
    int32_t v541 = instr;	// L787
    int32_t v542 = v541 >> 12;	// L788
    int32_t v543 = v542 & 15;	// L789
    int32_t s2;	// L790
    s2 = v543;	// L791
    half a;	// L792
    a = 0.000000;	// L793
    half b;	// L794
    b = 0.000000;	// L795
    int32_t v547 = s1;	// L796
    bool v548 = v547 >= 12;	// L797
    if (v548) {	// L798
      int32_t v549 = s1;	// L799
      int32_t v550 = v549 & 3;	// L800
      int v551 = v550;	// L801
      half v552 = hold_v[v551][0];	// L802
      a = v552;	// L803
    } else {
      int32_t v553 = s1;	// L805
      int v554 = v553;	// L806
      half v555 = drf[v554];	// L807
      a = v555;	// L808
    }
    int32_t v556 = s2;	// L810
    bool v557 = v556 >= 12;	// L811
    if (v557) {	// L812
      int32_t v558 = s2;	// L813
      int32_t v559 = v558 & 3;	// L814
      int v560 = v559;	// L815
      half v561 = hold_v[v560][0];	// L816
      b = v561;	// L817
    } else {
      int32_t v562 = s2;	// L819
      int v563 = v562;	// L820
      half v564 = drf[v563];	// L821
      b = v564;	// L822
    }
    int32_t a_vld;	// L824
    a_vld = 1;	// L825
    int32_t b_vld;	// L826
    b_vld = 1;	// L827
    int32_t v567 = s1;	// L828
    bool v568 = v567 >= 12;	// L829
    if (v568) {	// L830
      a_vld = 0;	// L831
      int32_t v569 = s1;	// L832
      int32_t v570 = v569 & 3;	// L833
      int v571 = v570;	// L834
      uint8_t v572 = hold_cnt[v571];	// L835
      int32_t v573 = v572;	// L836
      bool v574 = v573 > 0;	// L837
      if (v574) {	// L838
        a_vld = 1;	// L839
      }
    }
    int32_t v575 = s2;	// L842
    bool v576 = v575 >= 12;	// L843
    if (v576) {	// L844
      b_vld = 0;	// L845
      int32_t v577 = s2;	// L846
      int32_t v578 = v577 & 3;	// L847
      int v579 = v578;	// L848
      uint8_t v580 = hold_cnt[v579];	// L849
      int32_t v581 = v580;	// L850
      bool v582 = v581 > 0;	// L851
      if (v582) {	// L852
        b_vld = 1;	// L853
      }
    }
    int32_t v583 = s1;	// L856
    bool v584 = v583 < 8;	// L857
    int32_t v585 = dsmask;	// L858
    int32_t v586 = v585 >> v583;	// L860
    int32_t v587 = v586 & 1;	// L861
    bool v588 = v587 == 1;	// L862
    bool v589 = v584 & v588;	// L863
    if (v589) {	// L864
      int32_t v590 = s1;	// L865
      int v591 = v590;	// L866
      int32_t v592 = drf_full[v591];	// L867
      bool v593 = v592 == 0;	// L868
      if (v593) {	// L869
        a_vld = 0;	// L870
      }
    }
    int32_t v594 = s2;	// L873
    bool v595 = v594 < 8;	// L874
    int32_t v596 = dsmask;	// L875
    int32_t v597 = v596 >> v594;	// L877
    int32_t v598 = v597 & 1;	// L878
    bool v599 = v598 == 1;	// L879
    bool v600 = v595 & v599;	// L880
    if (v600) {	// L881
      int32_t v601 = s2;	// L882
      int v602 = v601;	// L883
      int32_t v603 = drf_full[v602];	// L884
      bool v604 = v603 == 0;	// L885
      if (v604) {	// L886
        b_vld = 0;	// L887
      }
    }
    int32_t binop;	// L890
    binop = 0;	// L891
    int32_t v606 = op;	// L892
    bool v607 = v606 == 0;	// L893
    bool v608 = v606 == 1;	// L895
    bool v609 = v606 == 2;	// L897
    bool v610 = v606 == 8;	// L899
    bool v611 = v606 == 9;	// L901
    bool v612 = v607 | v608;	// L902
    bool v613 = v612 | v609;	// L903
    bool v614 = v613 | v610;	// L904
    bool v615 = v614 | v611;	// L905
    if (v615) {	// L906
      binop = 1;	// L907
    }
    int32_t raw;	// L909
    raw = 0;	// L910
    int32_t cmp_busy;	// L911
    cmp_busy = 0;	// L912
    int32_t fwd_a;	// L913
    fwd_a = 0;	// L914
    int32_t fwd_a_ix;	// L915
    fwd_a_ix = 0;	// L916
    int32_t raw_a;	// L917
    raw_a = 0;	// L918
    int32_t fwd_b;	// L919
    fwd_b = 0;	// L920
    int32_t fwd_b_ix;	// L921
    fwd_b_ix = 0;	// L922
    int32_t raw_b;	// L923
    raw_b = 0;	// L924
    l_S_k_7_k: for (int k = 0; k < 4; k++) {	// L925
      ap_int<34> v625 = k;	// L926
      ap_int<34> v626 = v625 + 1;	// L927
      int32_t v627 = v626;	// L928
      int32_t kk;	// L929
      kk = v627;	// L930
      int32_t v629 = kk;	// L931
      ap_int<34> v630 = v629;	// L932
      ap_int<34> v631 = 4 - v630;	// L933
      int32_t v632 = v631;	// L934
      int32_t inflight;	// L935
      inflight = v632;	// L936
      int32_t need;	// L937
      need = 0;	// L938
      int32_t v635 = kk;	// L939
      int v636 = v635;	// L940
      uint8_t v637 = sb_long[v636];	// L941
      int32_t v638 = v637;	// L942
      bool v639 = v638 == 1;	// L943
      if (v639) {	// L944
        need = 1;	// L945
      }
      int32_t rdy;	// L947
      rdy = 0;	// L948
      int32_t v641 = inflight;	// L949
      int32_t v642 = need;	// L950
      bool v643 = v641 >= v642;	// L951
      if (v643) {	// L952
        rdy = 1;	// L953
      }
      int32_t v644 = kk;	// L955
      int v645 = v644;	// L956
      uint8_t v646 = sb_v[v645];	// L957
      int32_t v647 = v646;	// L958
      bool v648 = v647 == 1;	// L959
      uint8_t v649 = sb_rtr[v645];	// L962
      int32_t v650 = v649;	// L963
      bool v651 = v650 == 0;	// L964
      uint8_t v652 = sb_dst[v645];	// L967
      int32_t v653 = v652;	// L968
      bool v654 = v653 < 12;	// L969
      bool v655 = v648 & v651;	// L970
      bool v656 = v655 & v654;	// L971
      if (v656) {	// L972
        int32_t v657 = s1;	// L973
        bool v658 = v657 < 12;	// L974
        int32_t v659 = kk;	// L975
        int v660 = v659;	// L976
        uint8_t v661 = sb_dst[v660];	// L977
        int32_t v662 = v661;	// L978
        int32_t v663 = v662 & 7;	// L979
        int32_t v664 = v657 & 7;	// L981
        bool v665 = v663 == v664;	// L982
        bool v666 = v658 & v665;	// L983
        if (v666) {	// L984
          int32_t v667 = rdy;	// L985
          bool v668 = v667 == 1;	// L986
          if (v668) {	// L987
            fwd_a = 1;	// L988
            int32_t v669 = kk;	// L989
            int v670 = v669;	// L990
            uint8_t v671 = sb_ix[v670];	// L991
            int32_t v672 = v671;	// L992
            fwd_a_ix = v672;	// L993
            raw_a = 0;	// L994
          } else {
            fwd_a = 0;	// L996
            raw_a = 1;	// L997
          }
        }
        int32_t v673 = binop;	// L1000
        bool v674 = v673 == 1;	// L1001
        int32_t v675 = s2;	// L1002
        bool v676 = v675 < 12;	// L1003
        int32_t v677 = kk;	// L1004
        int v678 = v677;	// L1005
        uint8_t v679 = sb_dst[v678];	// L1006
        int32_t v680 = v679;	// L1007
        int32_t v681 = v680 & 7;	// L1008
        int32_t v682 = v675 & 7;	// L1010
        bool v683 = v681 == v682;	// L1011
        bool v684 = v674 & v676;	// L1012
        bool v685 = v684 & v683;	// L1013
        if (v685) {	// L1014
          int32_t v686 = rdy;	// L1015
          bool v687 = v686 == 1;	// L1016
          if (v687) {	// L1017
            fwd_b = 1;	// L1018
            int32_t v688 = kk;	// L1019
            int v689 = v688;	// L1020
            uint8_t v690 = sb_ix[v689];	// L1021
            int32_t v691 = v690;	// L1022
            fwd_b_ix = v691;	// L1023
            raw_b = 0;	// L1024
          } else {
            fwd_b = 0;	// L1026
            raw_b = 1;	// L1027
          }
        }
      }
      int32_t v692 = kk;	// L1031
      int v693 = v692;	// L1032
      uint8_t v694 = sb_v[v693];	// L1033
      int32_t v695 = v694;	// L1034
      bool v696 = v695 == 1;	// L1035
      uint8_t v697 = sb_cmp[v693];	// L1038
      int32_t v698 = v697;	// L1039
      bool v699 = v698 == 1;	// L1040
      bool v700 = v696 & v699;	// L1041
      if (v700) {	// L1042
        cmp_busy = 1;	// L1043
      }
    }
    int32_t v701 = raw_a;	// L1046
    raw = v701;	// L1047
    int32_t v702 = binop;	// L1048
    bool v703 = v702 == 1;	// L1049
    int32_t v704 = raw_b;	// L1050
    bool v705 = v704 == 1;	// L1051
    bool v706 = v703 & v705;	// L1052
    if (v706) {	// L1053
      raw = 1;	// L1054
    }
    int32_t v707 = fwd_a;	// L1056
    bool v708 = v707 == 1;	// L1057
    if (v708) {	// L1058
      int32_t v709 = fwd_a_ix;	// L1059
      int v710 = v709;	// L1060
      half v711 = resq[v710];	// L1061
      a = v711;	// L1062
      a_vld = 1;	// L1063
    }
    int32_t v712 = fwd_b;	// L1065
    bool v713 = v712 == 1;	// L1066
    if (v713) {	// L1067
      int32_t v714 = fwd_b_ix;	// L1068
      int v715 = v714;	// L1069
      half v716 = resq[v715];	// L1070
      b = v716;	// L1071
      b_vld = 1;	// L1072
    }
    int32_t is_cond;	// L1074
    is_cond = 0;	// L1075
    int32_t v718 = op;	// L1076
    bool v719 = v718 >= 12;	// L1077
    ap_int<33> v720 = v718;	// L1079
    bool v721 = v720 <= 15;	// L1080
    bool v722 = v719 & v721;	// L1081
    if (v722) {	// L1082
      is_cond = 1;	// L1083
    }
    int32_t grant;	// L1085
    grant = 0;	// L1086
    int32_t v724 = pc;	// L1087
    bool v725 = v724 >= 0;	// L1088
    if (v725) {	// L1089
      grant = 1;	// L1090
    }
    int32_t v726 = pc;	// L1092
    bool v727 = v726 >= 0;	// L1093
    int32_t v728 = a_vld;	// L1094
    bool v729 = v728 == 0;	// L1095
    int32_t v730 = binop;	// L1096
    bool v731 = v730 == 1;	// L1097
    int32_t v732 = b_vld;	// L1098
    bool v733 = v732 == 0;	// L1099
    bool v734 = v731 & v733;	// L1100
    bool v735 = v729 | v734;	// L1101
    bool v736 = v727 & v735;	// L1102
    if (v736) {	// L1103
      grant = 0;	// L1104
    }
    int32_t v737 = pc;	// L1106
    bool v738 = v737 >= 0;	// L1107
    int32_t v739 = raw;	// L1108
    bool v740 = v739 == 1;	// L1109
    int32_t v741 = is_cond;	// L1110
    bool v742 = v741 == 1;	// L1111
    int32_t v743 = cmp_busy;	// L1112
    bool v744 = v743 == 1;	// L1113
    bool v745 = v742 & v744;	// L1114
    bool v746 = v740 | v745;	// L1115
    bool v747 = v738 & v746;	// L1116
    if (v747) {	// L1117
      grant = 0;	// L1118
    }
    int32_t v748 = retire_ok;	// L1120
    bool v749 = v748 == 0;	// L1121
    if (v749) {	// L1122
      grant = 0;	// L1123
    }
    int32_t v750 = grant;	// L1125
    bool v751 = v750 == 1;	// L1126
    if (v751) {	// L1127
      int8_t v752 = instr_cnt;	// L1128
      int32_t v753 = cfg_isz;	// L1129
      int32_t v754 = v752;	// L1130
      bool v755 = v754 == v753;	// L1131
      if (v755) {	// L1132
        instr_cnt = 0;	// L1133
        int8_t v756 = iter_cnt;	// L1134
        int32_t v757 = cfg_itsz;	// L1135
        ap_int<33> v758 = v757;	// L1136
        ap_int<33> v759 = v758 - 1;	// L1137
        ap_int<33> v760 = v756;	// L1138
        bool v761 = v760 == v759;	// L1139
        if (v761) {	// L1140
          fetch_en = 0;	// L1141
        } else {
          int8_t v762 = iter_cnt;	// L1143
          ap_int<33> v763 = v762;	// L1144
          ap_int<33> v764 = v763 + 1;	// L1145
          uint8_t v765 = v764;	// L1146
          iter_cnt = v765;	// L1147
        }
      } else {
        int8_t v766 = instr_cnt;	// L1150
        ap_int<33> v767 = v766;	// L1151
        ap_int<33> v768 = v767 + 1;	// L1152
        uint8_t v769 = v768;	// L1153
        instr_cnt = v769;	// L1154
      }
    }
    int32_t c1;	// L1157
    c1 = -1;	// L1158
    int32_t c2;	// L1159
    c2 = -1;	// L1160
    int32_t v772 = grant;	// L1161
    bool v773 = v772 == 1;	// L1162
    int32_t v774 = s1;	// L1163
    bool v775 = v774 >= 12;	// L1164
    bool v776 = v773 & v775;	// L1165
    if (v776) {	// L1166
      int32_t v777 = s1;	// L1167
      int32_t v778 = v777 & 3;	// L1168
      c1 = v778;	// L1169
    }
    int32_t v779 = grant;	// L1171
    bool v780 = v779 == 1;	// L1172
    int32_t v781 = s2;	// L1173
    bool v782 = v781 >= 12;	// L1174
    bool v783 = v780 & v782;	// L1175
    if (v783) {	// L1176
      int32_t v784 = s2;	// L1177
      int32_t v785 = v784 & 3;	// L1178
      c2 = v785;	// L1179
    }
    int32_t v786 = c1;	// L1181
    bool v787 = v786 >= 0;	// L1182
    if (v787) {	// L1183
      int32_t v788 = c1;	// L1184
      int v789 = v788;	// L1185
      half v790 = hold_v[v789][1];	// L1186
      hold_v[v789][0] = v790;	// L1189
      int32_t v791 = c1;	// L1190
      int v792 = v791;	// L1191
      uint8_t v793 = hold_cnt[v792];	// L1192
      ap_int<33> v794 = v793;	// L1193
      ap_int<33> v795 = v794 - 1;	// L1194
      uint8_t v796 = v795;	// L1195
      hold_cnt[v792] = v796;	// L1198
    }
    int32_t v797 = c2;	// L1200
    bool v798 = v797 >= 0;	// L1201
    int32_t v799 = c1;	// L1203
    bool v800 = v797 != v799;	// L1204
    bool v801 = v798 & v800;	// L1205
    if (v801) {	// L1206
      int32_t v802 = c2;	// L1207
      int v803 = v802;	// L1208
      half v804 = hold_v[v803][1];	// L1209
      hold_v[v803][0] = v804;	// L1212
      int32_t v805 = c2;	// L1213
      int v806 = v805;	// L1214
      uint8_t v807 = hold_cnt[v806];	// L1215
      ap_int<33> v808 = v807;	// L1216
      ap_int<33> v809 = v808 - 1;	// L1217
      uint8_t v810 = v809;	// L1218
      hold_cnt[v806] = v810;	// L1221
    }
    l_S_d_8_d4: for (int d4 = 0; d4 < 4; d4++) {	// L1223
      sc_r[d4] = 0;	// L1224
    }
    int32_t v812 = c1;	// L1226
    bool v813 = v812 >= 0;	// L1227
    if (v813) {	// L1228
      int32_t v814 = c1;	// L1229
      int v815 = v814;	// L1230
      sc_r[v815] = 1;	// L1231
    }
    int32_t v816 = c2;	// L1233
    bool v817 = v816 >= 0;	// L1234
    int32_t v818 = c1;	// L1236
    bool v819 = v816 != v818;	// L1237
    bool v820 = v817 & v819;	// L1238
    if (v820) {	// L1239
      int32_t v821 = c2;	// L1240
      int v822 = v821;	// L1241
      sc_r[v822] = 1;	// L1242
    }
    int32_t v823 = grant;	// L1244
    bool v824 = v823 == 1;	// L1245
    int32_t v825 = s1;	// L1246
    bool v826 = v825 < 8;	// L1247
    int32_t v827 = dsmask;	// L1248
    int32_t v828 = v827 >> v825;	// L1250
    int32_t v829 = v828 & 1;	// L1251
    bool v830 = v829 == 1;	// L1252
    bool v831 = v824 & v826;	// L1253
    bool v832 = v831 & v830;	// L1254
    if (v832) {	// L1255
      int32_t v833 = s1;	// L1256
      int v834 = v833;	// L1257
      drf_full[v834] = 0;	// L1258
    }
    int32_t v835 = grant;	// L1260
    bool v836 = v835 == 1;	// L1261
    int32_t v837 = s2;	// L1262
    bool v838 = v837 < 8;	// L1263
    int32_t v839 = dsmask;	// L1264
    int32_t v840 = v839 >> v837;	// L1266
    int32_t v841 = v840 & 1;	// L1267
    bool v842 = v841 == 1;	// L1268
    bool v843 = v836 & v838;	// L1269
    bool v844 = v843 & v842;	// L1270
    if (v844) {	// L1271
      int32_t v845 = s2;	// L1272
      int v846 = v845;	// L1273
      drf_full[v846] = 0;	// L1274
    }
    half res;	// L1276
    res = 0.000000;	// L1277
    half v848 = b;	// L1278
    uint16_t v849;
    union { half from; uint16_t to;} _converter_v848_to_v849 = {};
    _converter_v848_to_v849.from = v848;
    v849 = _converter_v848_to_v849.to;	// L1279
    uint16_t bbits;	// L1280
    bbits = v849;	// L1281
    int32_t v851 = op;	// L1282
    bool v852 = v851 == 1;	// L1283
    if (v852) {	// L1284
      int16_t v853 = bbits;	// L1285
      int32_t v854 = v853;	// L1286
      int32_t v855 = v854 ^ 32768;	// L1287
      uint16_t v856 = v855;	// L1288
      bbits = v856;	// L1289
    }
    int16_t v857 = bbits;	// L1291
    half v858;
    union { uint16_t from; half to;} _converter_v857_to_v858 = {};
    _converter_v857_to_v858.from = v857;
    v858 = _converter_v857_to_v858.to;	// L1292
    half b_eff;	// L1293
    b_eff = v858;	// L1294
    int32_t v860 = op;	// L1295
    bool v861 = v860 == 0;	// L1296
    bool v862 = v860 == 1;	// L1298
    bool v863 = v861 | v862;	// L1299
    if (v863) {	// L1300
      half v864 = a;	// L1301
      half v865 = b_eff;	// L1302
      half v866 = v864 + v865;
#pragma HLS bind_op variable=v866 op=hadd impl=fabric latency=2	// L1303
      res = v866;	// L1304
    } else {
      int32_t v867 = op;	// L1306
      bool v868 = v867 == 2;	// L1307
      if (v868) {	// L1308
        half v869 = a;	// L1309
        half v870 = b;	// L1310
        half v871 = v869 * v870;
#pragma HLS bind_op variable=v871 op=hmul impl=maxdsp latency=2	// L1311
        res = v871;	// L1312
      } else {
        int32_t v872 = op;	// L1314
        bool v873 = v872 == 8;	// L1315
        if (v873) {	// L1316
          half v874 = a;	// L1317
          half v875 = b;	// L1318
          bool v876 = v874 >= v875;	// L1319
          if (v876) {	// L1320
            res = 1.000000;	// L1321
          } else {
            res = -1.000000;	// L1323
          }
        } else {
          int32_t v877 = op;	// L1326
          bool v878 = v877 == 9;	// L1327
          if (v878) {	// L1328
            half v879 = a;	// L1329
            half v880 = b;	// L1330
            bool v881 = v879 < v880;	// L1331
            if (v881) {	// L1332
              res = 1.000000;	// L1333
            } else {
              res = -1.000000;	// L1335
            }
          } else {
            half v882 = a;	// L1338
            res = v882;	// L1339
          }
        }
      }
    }
    int32_t v883 = a_vld;	// L1344
    int32_t res_vld;	// L1345
    res_vld = v883;	// L1346
    int32_t v885 = op;	// L1347
    bool v886 = v885 == 0;	// L1348
    bool v887 = v885 == 1;	// L1350
    bool v888 = v885 == 2;	// L1352
    bool v889 = v885 == 8;	// L1354
    bool v890 = v885 == 9;	// L1356
    bool v891 = v886 | v887;	// L1357
    bool v892 = v891 | v888;	// L1358
    bool v893 = v892 | v889;	// L1359
    bool v894 = v893 | v890;	// L1360
    if (v894) {	// L1361
      int32_t v895 = a_vld;	// L1362
      int32_t v896 = b_vld;	// L1363
      int64_t v897 = v895;	// L1364
      int64_t v898 = v896;	// L1365
      int64_t v899 = v897 * v898;	// L1366
      int32_t v900 = v899;	// L1367
      res_vld = v900;	// L1368
    }
    int32_t v901 = grant;	// L1370
    bool v902 = v901 == 0;	// L1371
    if (v902) {	// L1372
      res_vld = 0;	// L1373
    }
    int32_t is_rtr;	// L1375
    is_rtr = 0;	// L1376
    int32_t v904 = op;	// L1377
    bool v905 = v904 >= 4;	// L1378
    ap_int<33> v906 = v904;	// L1380
    bool v907 = v906 <= 7;	// L1381
    bool v908 = v905 & v907;	// L1382
    if (v908) {	// L1383
      is_rtr = 1;	// L1384
    }
    int32_t v909 = retire_ok;	// L1386
    bool v910 = v909 == 1;	// L1387
    if (v910) {	// L1388
      l_S_k_9_k1: for (int k1 = 0; k1 < 4; k1++) {	// L1389
        uint8_t v912 = sb_v[(k1 + 1)];	// L1390
        sb_v[k1] = v912;	// L1391
        uint8_t v913 = sb_dst[(k1 + 1)];	// L1392
        sb_dst[k1] = v913;	// L1393
        uint8_t v914 = sb_cmp[(k1 + 1)];	// L1394
        sb_cmp[k1] = v914;	// L1395
        uint8_t v915 = sb_rtr[(k1 + 1)];	// L1396
        sb_rtr[k1] = v915;	// L1397
        uint8_t v916 = sb_inj[(k1 + 1)];	// L1398
        sb_inj[k1] = v916;	// L1399
        uint8_t v917 = sb_dir[(k1 + 1)];	// L1400
        sb_dir[k1] = v917;	// L1401
        uint8_t v918 = sb_id[(k1 + 1)];	// L1402
        sb_id[k1] = v918;	// L1403
        uint8_t v919 = sb_rvld[(k1 + 1)];	// L1404
        sb_rvld[k1] = v919;	// L1405
        uint8_t v920 = sb_ix[(k1 + 1)];	// L1406
        sb_ix[k1] = v920;	// L1407
        uint8_t v921 = sb_long[(k1 + 1)];	// L1408
        sb_long[k1] = v921;	// L1409
      }
      sb_v[4] = 0;	// L1411
    }
    int32_t v922 = grant;	// L1413
    bool v923 = v922 == 1;	// L1414
    if (v923) {	// L1415
      half v924 = res;	// L1416
      int8_t v925 = resq_wr;	// L1417
      int v926 = v925;	// L1418
      resq[v926] = v924;	// L1419
      int32_t cq;	// L1420
      cq = 0;	// L1421
      int32_t v928 = op;	// L1422
      bool v929 = v928 == 8;	// L1423
      if (v929) {	// L1424
        half v930 = a;	// L1425
        half v931 = b;	// L1426
        bool v932 = v930 >= v931;	// L1427
        if (v932) {	// L1428
          cq = 1;	// L1429
        }
      }
      int32_t v933 = op;	// L1432
      bool v934 = v933 == 9;	// L1433
      if (v934) {	// L1434
        half v935 = a;	// L1435
        half v936 = b;	// L1436
        bool v937 = v935 < v936;	// L1437
        if (v937) {	// L1438
          cq = 1;	// L1439
        }
      }
      int32_t v938 = cq;	// L1442
      uint8_t v939 = v938;	// L1443
      int8_t v940 = resq_wr;	// L1444
      int v941 = v940;	// L1445
      cmpq[v941] = v939;	// L1446
      sb_v[4] = 1;	// L1447
      int32_t v942 = dst;	// L1448
      uint8_t v943 = v942;	// L1449
      sb_dst[4] = v943;	// L1450
      int8_t v944 = resq_wr;	// L1451
      sb_ix[4] = v944;	// L1452
      int32_t v945 = binop;	// L1453
      uint8_t v946 = v945;	// L1454
      sb_long[4] = v946;	// L1455
      sb_cmp[4] = 0;	// L1456
      int32_t v947 = op;	// L1457
      bool v948 = v947 == 8;	// L1458
      bool v949 = v947 == 9;	// L1460
      bool v950 = v948 | v949;	// L1461
      if (v950) {	// L1462
        sb_cmp[4] = 1;	// L1463
      }
      int32_t v951 = is_rtr;	// L1465
      int32_t rtrf;	// L1466
      rtrf = v951;	// L1467
      int32_t v953 = is_cond;	// L1468
      bool v954 = v953 == 1;	// L1469
      if (v954) {	// L1470
        rtrf = 1;	// L1471
      }
      int32_t v955 = rtrf;	// L1473
      uint8_t v956 = v955;	// L1474
      sb_rtr[4] = v956;	// L1475
      int32_t v957 = is_rtr;	// L1476
      int32_t inj;	// L1477
      inj = v957;	// L1478
      int32_t v959 = is_cond;	// L1479
      bool v960 = v959 == 1;	// L1480
      int8_t v961 = condition_reg;	// L1481
      int32_t v962 = v961;	// L1482
      bool v963 = v962 == 1;	// L1483
      bool v964 = v960 & v963;	// L1484
      if (v964) {	// L1485
        inj = 1;	// L1486
      }
      int32_t v965 = inj;	// L1488
      uint8_t v966 = v965;	// L1489
      sb_inj[4] = v966;	// L1490
      int32_t v967 = op;	// L1491
      int32_t v968 = v967 & 3;	// L1492
      uint8_t v969 = v968;	// L1493
      sb_dir[4] = v969;	// L1494
      int32_t v970 = s2;	// L1495
      uint8_t v971 = v970;	// L1496
      sb_id[4] = v971;	// L1497
      int32_t v972 = res_vld;	// L1498
      uint8_t v973 = v972;	// L1499
      sb_rvld[4] = v973;	// L1500
      int8_t v974 = resq_wr;	// L1501
      ap_int<33> v975 = v974;	// L1502
      ap_int<33> v976 = v975 + 1;	// L1503
      ap_int<33> v977 = v976 & 7;	// L1504
      uint8_t v978 = v977;	// L1505
      resq_wr = v978;	// L1506
    }
    txn_r = 0;	// L1508
    txs_r = 0;	// L1509
    txw_r = 0;	// L1510
    txe_r = 0;	// L1511
    int32_t v979 = txp_v[0];	// L1512
    bool v980 = v979 == 1;	// L1513
    int32_t v981 = scred[0];	// L1514
    bool v982 = v981 > 0;	// L1515
    bool v983 = v980 & v982;	// L1516
    if (v983) {	// L1517
      ap_uint<17> twn;	// L1518
      twn = 0;	// L1519
      ap_int<17> v985 = twn;	// L1520
      ap_int<17> v986;
      ap_int<17> v986_tmp = v985;
      v986_tmp[0] = 1;      v986 = v986_tmp;	// L1521
      twn = v986;	// L1522
      half v987 = txp_d[0];	// L1523
      uint16_t v988;
      union { half from; uint16_t to;} _converter_v987_to_v988 = {};
      _converter_v987_to_v988.from = v987;
      v988 = _converter_v987_to_v988.to;	// L1524
      ap_int<17> v989 = twn;	// L1525
      ap_int<17> v990;
      ap_int<17> v990_tmp = v989;
      v990_tmp(16, 1) = v988;
      v990 = v990_tmp;	// L1526
      twn = v990;	// L1527
      ap_int<17> v991 = twn;	// L1528
      txn_r = v991;	// L1529
      txp_v[0] = 0;	// L1530
      int32_t v992 = scred[0];	// L1531
      ap_int<33> v993 = v992;	// L1532
      ap_int<33> v994 = v993 - 1;	// L1533
      int32_t v995 = v994;	// L1534
      scred[0] = v995;	// L1535
    }
    int32_t v996 = txp_v[1];	// L1537
    bool v997 = v996 == 1;	// L1538
    int32_t v998 = scred[1];	// L1539
    bool v999 = v998 > 0;	// L1540
    bool v1000 = v997 & v999;	// L1541
    if (v1000) {	// L1542
      ap_uint<17> tws;	// L1543
      tws = 0;	// L1544
      ap_int<17> v1002 = tws;	// L1545
      ap_int<17> v1003;
      ap_int<17> v1003_tmp = v1002;
      v1003_tmp[0] = 1;      v1003 = v1003_tmp;	// L1546
      tws = v1003;	// L1547
      half v1004 = txp_d[1];	// L1548
      uint16_t v1005;
      union { half from; uint16_t to;} _converter_v1004_to_v1005 = {};
      _converter_v1004_to_v1005.from = v1004;
      v1005 = _converter_v1004_to_v1005.to;	// L1549
      ap_int<17> v1006 = tws;	// L1550
      ap_int<17> v1007;
      ap_int<17> v1007_tmp = v1006;
      v1007_tmp(16, 1) = v1005;
      v1007 = v1007_tmp;	// L1551
      tws = v1007;	// L1552
      ap_int<17> v1008 = tws;	// L1553
      txs_r = v1008;	// L1554
      txp_v[1] = 0;	// L1555
      int32_t v1009 = scred[1];	// L1556
      ap_int<33> v1010 = v1009;	// L1557
      ap_int<33> v1011 = v1010 - 1;	// L1558
      int32_t v1012 = v1011;	// L1559
      scred[1] = v1012;	// L1560
    }
    int32_t v1013 = txp_v[2];	// L1562
    bool v1014 = v1013 == 1;	// L1563
    int32_t v1015 = scred[2];	// L1564
    bool v1016 = v1015 > 0;	// L1565
    bool v1017 = v1014 & v1016;	// L1566
    if (v1017) {	// L1567
      ap_uint<17> tww;	// L1568
      tww = 0;	// L1569
      ap_int<17> v1019 = tww;	// L1570
      ap_int<17> v1020;
      ap_int<17> v1020_tmp = v1019;
      v1020_tmp[0] = 1;      v1020 = v1020_tmp;	// L1571
      tww = v1020;	// L1572
      half v1021 = txp_d[2];	// L1573
      uint16_t v1022;
      union { half from; uint16_t to;} _converter_v1021_to_v1022 = {};
      _converter_v1021_to_v1022.from = v1021;
      v1022 = _converter_v1021_to_v1022.to;	// L1574
      ap_int<17> v1023 = tww;	// L1575
      ap_int<17> v1024;
      ap_int<17> v1024_tmp = v1023;
      v1024_tmp(16, 1) = v1022;
      v1024 = v1024_tmp;	// L1576
      tww = v1024;	// L1577
      ap_int<17> v1025 = tww;	// L1578
      txw_r = v1025;	// L1579
      txp_v[2] = 0;	// L1580
      int32_t v1026 = scred[2];	// L1581
      ap_int<33> v1027 = v1026;	// L1582
      ap_int<33> v1028 = v1027 - 1;	// L1583
      int32_t v1029 = v1028;	// L1584
      scred[2] = v1029;	// L1585
    }
    int32_t v1030 = txp_v[3];	// L1587
    bool v1031 = v1030 == 1;	// L1588
    int32_t v1032 = scred[3];	// L1589
    bool v1033 = v1032 > 0;	// L1590
    bool v1034 = v1031 & v1033;	// L1591
    if (v1034) {	// L1592
      ap_uint<17> twe;	// L1593
      twe = 0;	// L1594
      ap_int<17> v1036 = twe;	// L1595
      ap_int<17> v1037;
      ap_int<17> v1037_tmp = v1036;
      v1037_tmp[0] = 1;      v1037 = v1037_tmp;	// L1596
      twe = v1037;	// L1597
      half v1038 = txp_d[3];	// L1598
      uint16_t v1039;
      union { half from; uint16_t to;} _converter_v1038_to_v1039 = {};
      _converter_v1038_to_v1039.from = v1038;
      v1039 = _converter_v1038_to_v1039.to;	// L1599
      ap_int<17> v1040 = twe;	// L1600
      ap_int<17> v1041;
      ap_int<17> v1041_tmp = v1040;
      v1041_tmp(16, 1) = v1039;
      v1041 = v1041_tmp;	// L1601
      twe = v1041;	// L1602
      ap_int<17> v1042 = twe;	// L1603
      txe_r = v1042;	// L1604
      txp_v[3] = 0;	// L1605
      int32_t v1043 = scred[3];	// L1606
      ap_int<33> v1044 = v1043;	// L1607
      ap_int<33> v1045 = v1044 - 1;	// L1608
      int32_t v1046 = v1045;	// L1609
      scred[3] = v1046;	// L1610
    }
    int32_t v1047 = crv_vld;	// L1612
    bool v1048 = v1047 == 1;	// L1613
    if (v1048) {	// L1614
      int32_t v1049 = crv_mode;	// L1615
      bool v1050 = v1049 == 1;	// L1616
      if (v1050) {	// L1617
        int32_t v1051 = crv_addr;	// L1618
        int32_t v1052 = v1051 >> 3;	// L1619
        int32_t v1053 = v1052 & 1;	// L1620
        bool v1054 = v1053 == 1;	// L1621
        if (v1054) {	// L1622
          int32_t v1055 = crv_raw;	// L1623
          int32_t v1056 = crv_addr;	// L1624
          int32_t v1057 = v1056 & 7;	// L1625
          int v1058 = v1057;	// L1626
          irf[v1058] = v1055;	// L1627
        } else {
          int32_t v1059 = crv_addr;	// L1629
          bool v1060 = v1059 == 0;	// L1630
          if (v1060) {	// L1631
            int32_t v1061 = crv_raw;	// L1632
            int32_t v1062 = v1061 & 255;	// L1633
            dsmask = v1062;	// L1634
            int32_t v1063 = crv_raw;	// L1635
            int32_t v1064 = v1063 >> 8;	// L1636
            int32_t v1065 = v1064 & 7;	// L1637
            cfg_isz = v1065;	// L1638
            int32_t v1066 = crv_raw;	// L1639
            int32_t v1067 = v1066 >> 15;	// L1640
            int32_t v1068 = v1067 & 1;	// L1641
            bool v1069 = v1068 == 1;	// L1642
            if (v1069) {	// L1643
              fetch_en = 1;	// L1644
              instr_cnt = 0;	// L1645
              iter_cnt = 0;	// L1646
            }
          } else {
            int32_t v1070 = crv_addr;	// L1649
            bool v1071 = v1070 == 1;	// L1650
            if (v1071) {	// L1651
              int32_t v1072 = crv_raw;	// L1652
              int32_t v1073 = v1072 & 255;	// L1653
              cfg_itsz = v1073;	// L1654
            }
          }
        }
      } else {
        int32_t v1074 = crv_addr;	// L1659
        int32_t v1075 = v1074 >> 2;	// L1660
        int32_t v1076 = v1075 & 3;	// L1661
        bool v1077 = v1076 == 3;	// L1662
        if (v1077) {	// L1663
          int32_t v1078 = crv_addr;	// L1664
          int32_t v1079 = v1078 & 3;	// L1665
          int v1080 = v1079;	// L1666
          txp_v[v1080] = 1;	// L1667
          half v1081 = crv_data;	// L1668
          int32_t v1082 = crv_addr;	// L1669
          int32_t v1083 = v1082 & 3;	// L1670
          int v1084 = v1083;	// L1671
          txp_d[v1084] = v1081;	// L1672
        } else {
          int32_t v1085 = crv_addr;	// L1674
          bool v1086 = v1085 < 8;	// L1675
          int32_t v1087 = dsmask;	// L1676
          int32_t v1088 = v1087 >> v1085;	// L1678
          int32_t v1089 = v1088 & 1;	// L1679
          bool v1090 = v1089 == 1;	// L1680
          bool v1091 = v1086 & v1090;	// L1681
          if (v1091) {	// L1682
            int32_t v1092 = crv_addr;	// L1683
            int v1093 = v1092;	// L1684
            int32_t v1094 = drf_full[v1093];	// L1685
            bool v1095 = v1094 == 0;	// L1686
            if (v1095) {	// L1687
              half v1096 = crv_data;	// L1688
              int32_t v1097 = crv_addr;	// L1689
              int v1098 = v1097;	// L1690
              drf[v1098] = v1096;	// L1691
              int32_t v1099 = crv_addr;	// L1692
              int v1100 = v1099;	// L1693
              drf_full[v1100] = 1;	// L1694
            }
          } else {
            half v1101 = crv_data;	// L1697
            int32_t v1102 = crv_addr;	// L1698
            int v1103 = v1102;	// L1699
            drf[v1103] = v1101;	// L1700
            int32_t v1104 = crv_addr;	// L1701
            int v1105 = v1104;	// L1702
            drf_full[v1105] = 1;	// L1703
          }
        }
      }
    }
    ap_int<26> v1106 = oe_r;	// L1708
    v1.write(v1106);	// L1709
    ap_int<26> v1107 = ow_r;	// L1710
    v2.write(v1107);	// L1711
    ap_int<26> v1108 = os_r;	// L1712
    v3.write(v1108);	// L1713
    ap_int<26> v1109 = on_r;	// L1714
    v4.write(v1109);	// L1715
    ap_int<17> v1110 = txe_r;	// L1716
    v5.write(v1110);	// L1717
    ap_int<17> v1111 = txw_r;	// L1718
    v6.write(v1111);	// L1719
    ap_int<17> v1112 = txs_r;	// L1720
    v7.write(v1112);	// L1721
    ap_int<17> v1113 = txn_r;	// L1722
    v8.write(v1113);	// L1723
    int32_t v1114 = cre_r;	// L1724
    v9.write(v1114);	// L1725
    int32_t v1115 = crw_r;	// L1726
    v10.write(v1115);	// L1727
    int32_t v1116 = crs_r;	// L1728
    v11.write(v1116);	// L1729
    int32_t v1117 = crn_r;	// L1730
    v12.write(v1117);	// L1731
    int32_t v1118 = sc_r[0];	// L1732
    v15.write(v1118);	// L1733
    int32_t v1119 = sc_r[1];	// L1734
    v16.write(v1119);	// L1735
    int32_t v1120 = sc_r[2];	// L1736
    v13.write(v1120);	// L1737
    int32_t v1121 = sc_r[3];	// L1738
    v14.write(v1121);	// L1739
  }
}

void drv_w_0(
  half v1122[1][2000],
  int32_t v1123[1][2000],
  int32_t v1124[1][1],
  hls::stream< ap_uint<17> >& v1125,
  hls::stream< int32_t >& v1126
) {
  #pragma HLS array_partition variable=v1122 complete dim=1
  #pragma HLS array_partition variable=v1123 complete dim=1	// L1743
  int32_t dcred[1];	// L1755
  for (int v1128 = 0; v1128 < 1; v1128++) {	// L1756
    dcred[v1128] = 0;	// L1756
  }
  int32_t rp[1];	// L1757
  for (int v1130 = 0; v1130 < 1; v1130++) {	// L1758
    rp[v1130] = 0;	// L1758
  }
  int32_t wcnt[1];	// L1759
  for (int v1132 = 0; v1132 < 1; v1132++) {	// L1760
    wcnt[v1132] = 0;	// L1760
  }
  half win_d[1][4];	// L1761
  for (int v1134 = 0; v1134 < 1; v1134++) {	// L1762
    for (int v1135 = 0; v1135 < 4; v1135++) {	// L1762
      win_d[v1134][v1135] = 0.000000;	// L1762
    }
  }
  int32_t win_f[1][4];	// L1763
  for (int v1137 = 0; v1137 < 1; v1137++) {	// L1764
    for (int v1138 = 0; v1138 < 4; v1138++) {	// L1764
      win_f[v1137][v1138] = 0;	// L1764
    }
  }
  int32_t win_s[1][4];	// L1765
  for (int v1140 = 0; v1140 < 1; v1140++) {	// L1766
    for (int v1141 = 0; v1141 < 4; v1141++) {	// L1766
      win_s[v1140][v1141] = 0;	// L1766
    }
  }
  ap_uint<17> zw;	// L1767
  zw = 0;	// L1768
  int32_t v1143 = v1124[0][0];	// L1769
  ap_int<33> v1144 = v1143;	// L1770
  ap_int<33> v1145 = v1144 - 1;	// L1771
  int v1146 = v1145;	// L1772
  for (int v1147 = 0; v1147 < v1146; v1147 += 1) {	// L1773
    ap_int<17> v1148 = zw;	// L1774
    v1125.write(v1148);	// L1775
  }
  l_S__pf_1__pf: for (int _pf = 0; _pf < 2; _pf++) {	// L1777
    int32_t v1150 = rp[0];	// L1778
    bool v1151 = v1150 < 2000;	// L1779
    if (v1151) {	// L1780
      int32_t v1152 = rp[0];	// L1781
      int v1153 = v1152;	// L1782
      half v1154 = v1122[0][v1153];	// L1783
      int32_t v1155 = wcnt[0];	// L1784
      int v1156 = v1155;	// L1785
      win_d[0][v1156] = v1154;	// L1786
      int32_t v1157 = rp[0];	// L1787
      int v1158 = v1157;	// L1788
      int32_t v1159 = v1123[0][v1158];	// L1789
      int32_t v1160 = wcnt[0];	// L1790
      int v1161 = v1160;	// L1791
      win_f[0][v1161] = v1159;	// L1792
      int32_t v1162 = rp[0];	// L1793
      int32_t v1163 = wcnt[0];	// L1794
      int v1164 = v1163;	// L1795
      win_s[0][v1164] = v1162;	// L1796
      int32_t v1165 = wcnt[0];	// L1797
      ap_int<33> v1166 = v1165;	// L1798
      ap_int<33> v1167 = v1166 + 1;	// L1799
      int32_t v1168 = v1167;	// L1800
      wcnt[0] = v1168;	// L1801
      int32_t v1169 = rp[0];	// L1802
      ap_int<33> v1170 = v1169;	// L1803
      ap_int<33> v1171 = v1170 + 1;	// L1804
      int32_t v1172 = v1171;	// L1805
      rp[0] = v1172;	// L1806
    }
  }
  l_S_t_2_t1: for (int t1 = 0; t1 < 2000; t1++) {	// L1809
  #pragma HLS pipeline II=1
    int32_t v1174 = v1126.read();	// L1810
    int32_t cin;	// L1811
    cin = v1174;	// L1812
    int32_t v1176 = cin;	// L1813
    int32_t v1177 = dcred[0];	// L1814
    ap_int<33> v1178 = v1177;	// L1815
    ap_int<33> v1179 = v1176;	// L1816
    ap_int<33> v1180 = v1178 + v1179;	// L1817
    int32_t v1181 = v1180;	// L1818
    dcred[0] = v1181;	// L1819
    ap_uint<17> w;	// L1820
    w = 0;	// L1821
    int32_t popd;	// L1822
    popd = 0;	// L1823
    int32_t v1184 = wcnt[0];	// L1824
    bool v1185 = v1184 > 0;	// L1825
    int32_t v1186 = win_s[0][0];	// L1826
    ap_int<33> v1187 = t1;	// L1827
    ap_int<33> v1188 = v1186;	// L1828
    bool v1189 = v1187 >= v1188;	// L1829
    bool v1190 = v1185 & v1189;	// L1830
    if (v1190) {	// L1831
      int32_t v1191 = win_f[0][0];	// L1832
      bool v1192 = v1191 == 0;	// L1833
      if (v1192) {	// L1834
        popd = 1;	// L1835
      } else {
        int32_t v1193 = dcred[0];	// L1837
        bool v1194 = v1193 > 0;	// L1838
        if (v1194) {	// L1839
          ap_int<17> v1195 = w;	// L1840
          ap_int<17> v1196;
          ap_int<17> v1196_tmp = v1195;
          v1196_tmp[0] = 1;          v1196 = v1196_tmp;	// L1841
          w = v1196;	// L1842
          half v1197 = win_d[0][0];	// L1843
          uint16_t v1198;
          union { half from; uint16_t to;} _converter_v1197_to_v1198 = {};
          _converter_v1197_to_v1198.from = v1197;
          v1198 = _converter_v1197_to_v1198.to;	// L1844
          ap_int<17> v1199 = w;	// L1845
          ap_int<17> v1200;
          ap_int<17> v1200_tmp = v1199;
          v1200_tmp(16, 1) = v1198;
          v1200 = v1200_tmp;	// L1846
          w = v1200;	// L1847
          int32_t v1201 = dcred[0];	// L1848
          ap_int<33> v1202 = v1201;	// L1849
          ap_int<33> v1203 = v1202 - 1;	// L1850
          int32_t v1204 = v1203;	// L1851
          dcred[0] = v1204;	// L1852
          popd = 1;	// L1853
        }
      }
    }
    int32_t v1205 = popd;	// L1857
    bool v1206 = v1205 == 1;	// L1858
    if (v1206) {	// L1859
      l_S_sft_2_sft1: for (int sft1 = 0; sft1 < 3; sft1++) {	// L1860
        half v1208 = win_d[0][(sft1 + 1)];	// L1861
        win_d[0][sft1] = v1208;	// L1862
        int32_t v1209 = win_f[0][(sft1 + 1)];	// L1863
        win_f[0][sft1] = v1209;	// L1864
        int32_t v1210 = win_s[0][(sft1 + 1)];	// L1865
        win_s[0][sft1] = v1210;	// L1866
      }
      int32_t v1211 = wcnt[0];	// L1868
      ap_int<33> v1212 = v1211;	// L1869
      ap_int<33> v1213 = v1212 - 1;	// L1870
      int32_t v1214 = v1213;	// L1871
      wcnt[0] = v1214;	// L1872
    }
    int32_t v1215 = rp[0];	// L1874
    bool v1216 = v1215 < 2000;	// L1875
    int32_t v1217 = wcnt[0];	// L1876
    bool v1218 = v1217 < 4;	// L1877
    bool v1219 = v1216 & v1218;	// L1878
    if (v1219) {	// L1879
      int32_t v1220 = rp[0];	// L1880
      int v1221 = v1220;	// L1881
      half v1222 = v1122[0][v1221];	// L1882
      int32_t v1223 = wcnt[0];	// L1883
      int v1224 = v1223;	// L1884
      win_d[0][v1224] = v1222;	// L1885
      int32_t v1225 = rp[0];	// L1886
      int v1226 = v1225;	// L1887
      int32_t v1227 = v1123[0][v1226];	// L1888
      int32_t v1228 = wcnt[0];	// L1889
      int v1229 = v1228;	// L1890
      win_f[0][v1229] = v1227;	// L1891
      int32_t v1230 = rp[0];	// L1892
      int32_t v1231 = wcnt[0];	// L1893
      int v1232 = v1231;	// L1894
      win_s[0][v1232] = v1230;	// L1895
      int32_t v1233 = wcnt[0];	// L1896
      ap_int<33> v1234 = v1233;	// L1897
      ap_int<33> v1235 = v1234 + 1;	// L1898
      int32_t v1236 = v1235;	// L1899
      wcnt[0] = v1236;	// L1900
      int32_t v1237 = rp[0];	// L1901
      ap_int<33> v1238 = v1237;	// L1902
      ap_int<33> v1239 = v1238 + 1;	// L1903
      int32_t v1240 = v1239;	// L1904
      rp[0] = v1240;	// L1905
    }
    ap_int<17> v1241 = w;	// L1907
    v1125.write(v1241);	// L1908
  }
}

void drv_e_0(
  half v1242[1][2000],
  int32_t v1243[1][2000],
  int32_t v1244[1][1],
  hls::stream< ap_uint<17> >& v1245,
  hls::stream< int32_t >& v1246
) {
  #pragma HLS array_partition variable=v1242 complete dim=1
  #pragma HLS array_partition variable=v1243 complete dim=1	// L1912
  int32_t dcred1[1];	// L1924
  for (int v1248 = 0; v1248 < 1; v1248++) {	// L1925
    dcred1[v1248] = 0;	// L1925
  }
  int32_t rp1[1];	// L1926
  for (int v1250 = 0; v1250 < 1; v1250++) {	// L1927
    rp1[v1250] = 0;	// L1927
  }
  int32_t wcnt1[1];	// L1928
  for (int v1252 = 0; v1252 < 1; v1252++) {	// L1929
    wcnt1[v1252] = 0;	// L1929
  }
  half win_d1[1][4];	// L1930
  for (int v1254 = 0; v1254 < 1; v1254++) {	// L1931
    for (int v1255 = 0; v1255 < 4; v1255++) {	// L1931
      win_d1[v1254][v1255] = 0.000000;	// L1931
    }
  }
  int32_t win_f1[1][4];	// L1932
  for (int v1257 = 0; v1257 < 1; v1257++) {	// L1933
    for (int v1258 = 0; v1258 < 4; v1258++) {	// L1933
      win_f1[v1257][v1258] = 0;	// L1933
    }
  }
  int32_t win_s1[1][4];	// L1934
  for (int v1260 = 0; v1260 < 1; v1260++) {	// L1935
    for (int v1261 = 0; v1261 < 4; v1261++) {	// L1935
      win_s1[v1260][v1261] = 0;	// L1935
    }
  }
  ap_uint<17> zw1;	// L1936
  zw1 = 0;	// L1937
  int32_t v1263 = v1244[0][0];	// L1938
  ap_int<33> v1264 = v1263;	// L1939
  ap_int<33> v1265 = v1264 - 1;	// L1940
  int v1266 = v1265;	// L1941
  for (int v1267 = 0; v1267 < v1266; v1267 += 1) {	// L1942
    ap_int<17> v1268 = zw1;	// L1943
    v1245.write(v1268);	// L1944
  }
  l_S__pf_1__pf1: for (int _pf1 = 0; _pf1 < 2; _pf1++) {	// L1946
    int32_t v1270 = rp1[0];	// L1947
    bool v1271 = v1270 < 2000;	// L1948
    if (v1271) {	// L1949
      int32_t v1272 = rp1[0];	// L1950
      int v1273 = v1272;	// L1951
      half v1274 = v1242[0][v1273];	// L1952
      int32_t v1275 = wcnt1[0];	// L1953
      int v1276 = v1275;	// L1954
      win_d1[0][v1276] = v1274;	// L1955
      int32_t v1277 = rp1[0];	// L1956
      int v1278 = v1277;	// L1957
      int32_t v1279 = v1243[0][v1278];	// L1958
      int32_t v1280 = wcnt1[0];	// L1959
      int v1281 = v1280;	// L1960
      win_f1[0][v1281] = v1279;	// L1961
      int32_t v1282 = rp1[0];	// L1962
      int32_t v1283 = wcnt1[0];	// L1963
      int v1284 = v1283;	// L1964
      win_s1[0][v1284] = v1282;	// L1965
      int32_t v1285 = wcnt1[0];	// L1966
      ap_int<33> v1286 = v1285;	// L1967
      ap_int<33> v1287 = v1286 + 1;	// L1968
      int32_t v1288 = v1287;	// L1969
      wcnt1[0] = v1288;	// L1970
      int32_t v1289 = rp1[0];	// L1971
      ap_int<33> v1290 = v1289;	// L1972
      ap_int<33> v1291 = v1290 + 1;	// L1973
      int32_t v1292 = v1291;	// L1974
      rp1[0] = v1292;	// L1975
    }
  }
  l_S_t_2_t2: for (int t2 = 0; t2 < 2000; t2++) {	// L1978
  #pragma HLS pipeline II=1
    int32_t v1294 = v1246.read();	// L1979
    int32_t cin1;	// L1980
    cin1 = v1294;	// L1981
    int32_t v1296 = cin1;	// L1982
    int32_t v1297 = dcred1[0];	// L1983
    ap_int<33> v1298 = v1297;	// L1984
    ap_int<33> v1299 = v1296;	// L1985
    ap_int<33> v1300 = v1298 + v1299;	// L1986
    int32_t v1301 = v1300;	// L1987
    dcred1[0] = v1301;	// L1988
    ap_uint<17> w1;	// L1989
    w1 = 0;	// L1990
    int32_t popd1;	// L1991
    popd1 = 0;	// L1992
    int32_t v1304 = wcnt1[0];	// L1993
    bool v1305 = v1304 > 0;	// L1994
    int32_t v1306 = win_s1[0][0];	// L1995
    ap_int<33> v1307 = t2;	// L1996
    ap_int<33> v1308 = v1306;	// L1997
    bool v1309 = v1307 >= v1308;	// L1998
    bool v1310 = v1305 & v1309;	// L1999
    if (v1310) {	// L2000
      int32_t v1311 = win_f1[0][0];	// L2001
      bool v1312 = v1311 == 0;	// L2002
      if (v1312) {	// L2003
        popd1 = 1;	// L2004
      } else {
        int32_t v1313 = dcred1[0];	// L2006
        bool v1314 = v1313 > 0;	// L2007
        if (v1314) {	// L2008
          ap_int<17> v1315 = w1;	// L2009
          ap_int<17> v1316;
          ap_int<17> v1316_tmp = v1315;
          v1316_tmp[0] = 1;          v1316 = v1316_tmp;	// L2010
          w1 = v1316;	// L2011
          half v1317 = win_d1[0][0];	// L2012
          uint16_t v1318;
          union { half from; uint16_t to;} _converter_v1317_to_v1318 = {};
          _converter_v1317_to_v1318.from = v1317;
          v1318 = _converter_v1317_to_v1318.to;	// L2013
          ap_int<17> v1319 = w1;	// L2014
          ap_int<17> v1320;
          ap_int<17> v1320_tmp = v1319;
          v1320_tmp(16, 1) = v1318;
          v1320 = v1320_tmp;	// L2015
          w1 = v1320;	// L2016
          int32_t v1321 = dcred1[0];	// L2017
          ap_int<33> v1322 = v1321;	// L2018
          ap_int<33> v1323 = v1322 - 1;	// L2019
          int32_t v1324 = v1323;	// L2020
          dcred1[0] = v1324;	// L2021
          popd1 = 1;	// L2022
        }
      }
    }
    int32_t v1325 = popd1;	// L2026
    bool v1326 = v1325 == 1;	// L2027
    if (v1326) {	// L2028
      l_S_sft_2_sft2: for (int sft2 = 0; sft2 < 3; sft2++) {	// L2029
        half v1328 = win_d1[0][(sft2 + 1)];	// L2030
        win_d1[0][sft2] = v1328;	// L2031
        int32_t v1329 = win_f1[0][(sft2 + 1)];	// L2032
        win_f1[0][sft2] = v1329;	// L2033
        int32_t v1330 = win_s1[0][(sft2 + 1)];	// L2034
        win_s1[0][sft2] = v1330;	// L2035
      }
      int32_t v1331 = wcnt1[0];	// L2037
      ap_int<33> v1332 = v1331;	// L2038
      ap_int<33> v1333 = v1332 - 1;	// L2039
      int32_t v1334 = v1333;	// L2040
      wcnt1[0] = v1334;	// L2041
    }
    int32_t v1335 = rp1[0];	// L2043
    bool v1336 = v1335 < 2000;	// L2044
    int32_t v1337 = wcnt1[0];	// L2045
    bool v1338 = v1337 < 4;	// L2046
    bool v1339 = v1336 & v1338;	// L2047
    if (v1339) {	// L2048
      int32_t v1340 = rp1[0];	// L2049
      int v1341 = v1340;	// L2050
      half v1342 = v1242[0][v1341];	// L2051
      int32_t v1343 = wcnt1[0];	// L2052
      int v1344 = v1343;	// L2053
      win_d1[0][v1344] = v1342;	// L2054
      int32_t v1345 = rp1[0];	// L2055
      int v1346 = v1345;	// L2056
      int32_t v1347 = v1243[0][v1346];	// L2057
      int32_t v1348 = wcnt1[0];	// L2058
      int v1349 = v1348;	// L2059
      win_f1[0][v1349] = v1347;	// L2060
      int32_t v1350 = rp1[0];	// L2061
      int32_t v1351 = wcnt1[0];	// L2062
      int v1352 = v1351;	// L2063
      win_s1[0][v1352] = v1350;	// L2064
      int32_t v1353 = wcnt1[0];	// L2065
      ap_int<33> v1354 = v1353;	// L2066
      ap_int<33> v1355 = v1354 + 1;	// L2067
      int32_t v1356 = v1355;	// L2068
      wcnt1[0] = v1356;	// L2069
      int32_t v1357 = rp1[0];	// L2070
      ap_int<33> v1358 = v1357;	// L2071
      ap_int<33> v1359 = v1358 + 1;	// L2072
      int32_t v1360 = v1359;	// L2073
      rp1[0] = v1360;	// L2074
    }
    ap_int<17> v1361 = w1;	// L2076
    v1245.write(v1361);	// L2077
  }
}

void drv_n_0(
  half v1362[1][2000],
  int32_t v1363[1][2000],
  int32_t v1364[1][1],
  hls::stream< ap_uint<17> >& v1365,
  hls::stream< int32_t >& v1366
) {
  #pragma HLS array_partition variable=v1362 complete dim=1
  #pragma HLS array_partition variable=v1363 complete dim=1	// L2081
  int32_t dcred2[1];	// L2093
  for (int v1368 = 0; v1368 < 1; v1368++) {	// L2094
    dcred2[v1368] = 0;	// L2094
  }
  int32_t rp2[1];	// L2095
  for (int v1370 = 0; v1370 < 1; v1370++) {	// L2096
    rp2[v1370] = 0;	// L2096
  }
  int32_t wcnt2[1];	// L2097
  for (int v1372 = 0; v1372 < 1; v1372++) {	// L2098
    wcnt2[v1372] = 0;	// L2098
  }
  half win_d2[1][4];	// L2099
  for (int v1374 = 0; v1374 < 1; v1374++) {	// L2100
    for (int v1375 = 0; v1375 < 4; v1375++) {	// L2100
      win_d2[v1374][v1375] = 0.000000;	// L2100
    }
  }
  int32_t win_f2[1][4];	// L2101
  for (int v1377 = 0; v1377 < 1; v1377++) {	// L2102
    for (int v1378 = 0; v1378 < 4; v1378++) {	// L2102
      win_f2[v1377][v1378] = 0;	// L2102
    }
  }
  int32_t win_s2[1][4];	// L2103
  for (int v1380 = 0; v1380 < 1; v1380++) {	// L2104
    for (int v1381 = 0; v1381 < 4; v1381++) {	// L2104
      win_s2[v1380][v1381] = 0;	// L2104
    }
  }
  ap_uint<17> zw2;	// L2105
  zw2 = 0;	// L2106
  int32_t v1383 = v1364[0][0];	// L2107
  ap_int<33> v1384 = v1383;	// L2108
  ap_int<33> v1385 = v1384 - 1;	// L2109
  int v1386 = v1385;	// L2110
  for (int v1387 = 0; v1387 < v1386; v1387 += 1) {	// L2111
    ap_int<17> v1388 = zw2;	// L2112
    v1365.write(v1388);	// L2113
  }
  l_S__pf_1__pf2: for (int _pf2 = 0; _pf2 < 2; _pf2++) {	// L2115
    int32_t v1390 = rp2[0];	// L2116
    bool v1391 = v1390 < 2000;	// L2117
    if (v1391) {	// L2118
      int32_t v1392 = rp2[0];	// L2119
      int v1393 = v1392;	// L2120
      half v1394 = v1362[0][v1393];	// L2121
      int32_t v1395 = wcnt2[0];	// L2122
      int v1396 = v1395;	// L2123
      win_d2[0][v1396] = v1394;	// L2124
      int32_t v1397 = rp2[0];	// L2125
      int v1398 = v1397;	// L2126
      int32_t v1399 = v1363[0][v1398];	// L2127
      int32_t v1400 = wcnt2[0];	// L2128
      int v1401 = v1400;	// L2129
      win_f2[0][v1401] = v1399;	// L2130
      int32_t v1402 = rp2[0];	// L2131
      int32_t v1403 = wcnt2[0];	// L2132
      int v1404 = v1403;	// L2133
      win_s2[0][v1404] = v1402;	// L2134
      int32_t v1405 = wcnt2[0];	// L2135
      ap_int<33> v1406 = v1405;	// L2136
      ap_int<33> v1407 = v1406 + 1;	// L2137
      int32_t v1408 = v1407;	// L2138
      wcnt2[0] = v1408;	// L2139
      int32_t v1409 = rp2[0];	// L2140
      ap_int<33> v1410 = v1409;	// L2141
      ap_int<33> v1411 = v1410 + 1;	// L2142
      int32_t v1412 = v1411;	// L2143
      rp2[0] = v1412;	// L2144
    }
  }
  l_S_t_2_t3: for (int t3 = 0; t3 < 2000; t3++) {	// L2147
  #pragma HLS pipeline II=1
    int32_t v1414 = v1366.read();	// L2148
    int32_t cin2;	// L2149
    cin2 = v1414;	// L2150
    int32_t v1416 = cin2;	// L2151
    int32_t v1417 = dcred2[0];	// L2152
    ap_int<33> v1418 = v1417;	// L2153
    ap_int<33> v1419 = v1416;	// L2154
    ap_int<33> v1420 = v1418 + v1419;	// L2155
    int32_t v1421 = v1420;	// L2156
    dcred2[0] = v1421;	// L2157
    ap_uint<17> w2;	// L2158
    w2 = 0;	// L2159
    int32_t popd2;	// L2160
    popd2 = 0;	// L2161
    int32_t v1424 = wcnt2[0];	// L2162
    bool v1425 = v1424 > 0;	// L2163
    int32_t v1426 = win_s2[0][0];	// L2164
    ap_int<33> v1427 = t3;	// L2165
    ap_int<33> v1428 = v1426;	// L2166
    bool v1429 = v1427 >= v1428;	// L2167
    bool v1430 = v1425 & v1429;	// L2168
    if (v1430) {	// L2169
      int32_t v1431 = win_f2[0][0];	// L2170
      bool v1432 = v1431 == 0;	// L2171
      if (v1432) {	// L2172
        popd2 = 1;	// L2173
      } else {
        int32_t v1433 = dcred2[0];	// L2175
        bool v1434 = v1433 > 0;	// L2176
        if (v1434) {	// L2177
          ap_int<17> v1435 = w2;	// L2178
          ap_int<17> v1436;
          ap_int<17> v1436_tmp = v1435;
          v1436_tmp[0] = 1;          v1436 = v1436_tmp;	// L2179
          w2 = v1436;	// L2180
          half v1437 = win_d2[0][0];	// L2181
          uint16_t v1438;
          union { half from; uint16_t to;} _converter_v1437_to_v1438 = {};
          _converter_v1437_to_v1438.from = v1437;
          v1438 = _converter_v1437_to_v1438.to;	// L2182
          ap_int<17> v1439 = w2;	// L2183
          ap_int<17> v1440;
          ap_int<17> v1440_tmp = v1439;
          v1440_tmp(16, 1) = v1438;
          v1440 = v1440_tmp;	// L2184
          w2 = v1440;	// L2185
          int32_t v1441 = dcred2[0];	// L2186
          ap_int<33> v1442 = v1441;	// L2187
          ap_int<33> v1443 = v1442 - 1;	// L2188
          int32_t v1444 = v1443;	// L2189
          dcred2[0] = v1444;	// L2190
          popd2 = 1;	// L2191
        }
      }
    }
    int32_t v1445 = popd2;	// L2195
    bool v1446 = v1445 == 1;	// L2196
    if (v1446) {	// L2197
      l_S_sft_2_sft3: for (int sft3 = 0; sft3 < 3; sft3++) {	// L2198
        half v1448 = win_d2[0][(sft3 + 1)];	// L2199
        win_d2[0][sft3] = v1448;	// L2200
        int32_t v1449 = win_f2[0][(sft3 + 1)];	// L2201
        win_f2[0][sft3] = v1449;	// L2202
        int32_t v1450 = win_s2[0][(sft3 + 1)];	// L2203
        win_s2[0][sft3] = v1450;	// L2204
      }
      int32_t v1451 = wcnt2[0];	// L2206
      ap_int<33> v1452 = v1451;	// L2207
      ap_int<33> v1453 = v1452 - 1;	// L2208
      int32_t v1454 = v1453;	// L2209
      wcnt2[0] = v1454;	// L2210
    }
    int32_t v1455 = rp2[0];	// L2212
    bool v1456 = v1455 < 2000;	// L2213
    int32_t v1457 = wcnt2[0];	// L2214
    bool v1458 = v1457 < 4;	// L2215
    bool v1459 = v1456 & v1458;	// L2216
    if (v1459) {	// L2217
      int32_t v1460 = rp2[0];	// L2218
      int v1461 = v1460;	// L2219
      half v1462 = v1362[0][v1461];	// L2220
      int32_t v1463 = wcnt2[0];	// L2221
      int v1464 = v1463;	// L2222
      win_d2[0][v1464] = v1462;	// L2223
      int32_t v1465 = rp2[0];	// L2224
      int v1466 = v1465;	// L2225
      int32_t v1467 = v1363[0][v1466];	// L2226
      int32_t v1468 = wcnt2[0];	// L2227
      int v1469 = v1468;	// L2228
      win_f2[0][v1469] = v1467;	// L2229
      int32_t v1470 = rp2[0];	// L2230
      int32_t v1471 = wcnt2[0];	// L2231
      int v1472 = v1471;	// L2232
      win_s2[0][v1472] = v1470;	// L2233
      int32_t v1473 = wcnt2[0];	// L2234
      ap_int<33> v1474 = v1473;	// L2235
      ap_int<33> v1475 = v1474 + 1;	// L2236
      int32_t v1476 = v1475;	// L2237
      wcnt2[0] = v1476;	// L2238
      int32_t v1477 = rp2[0];	// L2239
      ap_int<33> v1478 = v1477;	// L2240
      ap_int<33> v1479 = v1478 + 1;	// L2241
      int32_t v1480 = v1479;	// L2242
      rp2[0] = v1480;	// L2243
    }
    ap_int<17> v1481 = w2;	// L2245
    v1365.write(v1481);	// L2246
  }
}

void drv_s_0(
  half v1482[1][2000],
  int32_t v1483[1][2000],
  int32_t v1484[1][1],
  hls::stream< ap_uint<17> >& v1485,
  hls::stream< int32_t >& v1486
) {
  #pragma HLS array_partition variable=v1482 complete dim=1
  #pragma HLS array_partition variable=v1483 complete dim=1	// L2250
  int32_t dcred3[1];	// L2262
  for (int v1488 = 0; v1488 < 1; v1488++) {	// L2263
    dcred3[v1488] = 0;	// L2263
  }
  int32_t rp3[1];	// L2264
  for (int v1490 = 0; v1490 < 1; v1490++) {	// L2265
    rp3[v1490] = 0;	// L2265
  }
  int32_t wcnt3[1];	// L2266
  for (int v1492 = 0; v1492 < 1; v1492++) {	// L2267
    wcnt3[v1492] = 0;	// L2267
  }
  half win_d3[1][4];	// L2268
  for (int v1494 = 0; v1494 < 1; v1494++) {	// L2269
    for (int v1495 = 0; v1495 < 4; v1495++) {	// L2269
      win_d3[v1494][v1495] = 0.000000;	// L2269
    }
  }
  int32_t win_f3[1][4];	// L2270
  for (int v1497 = 0; v1497 < 1; v1497++) {	// L2271
    for (int v1498 = 0; v1498 < 4; v1498++) {	// L2271
      win_f3[v1497][v1498] = 0;	// L2271
    }
  }
  int32_t win_s3[1][4];	// L2272
  for (int v1500 = 0; v1500 < 1; v1500++) {	// L2273
    for (int v1501 = 0; v1501 < 4; v1501++) {	// L2273
      win_s3[v1500][v1501] = 0;	// L2273
    }
  }
  ap_uint<17> zw3;	// L2274
  zw3 = 0;	// L2275
  int32_t v1503 = v1484[0][0];	// L2276
  ap_int<33> v1504 = v1503;	// L2277
  ap_int<33> v1505 = v1504 - 1;	// L2278
  int v1506 = v1505;	// L2279
  for (int v1507 = 0; v1507 < v1506; v1507 += 1) {	// L2280
    ap_int<17> v1508 = zw3;	// L2281
    v1485.write(v1508);	// L2282
  }
  l_S__pf_1__pf3: for (int _pf3 = 0; _pf3 < 2; _pf3++) {	// L2284
    int32_t v1510 = rp3[0];	// L2285
    bool v1511 = v1510 < 2000;	// L2286
    if (v1511) {	// L2287
      int32_t v1512 = rp3[0];	// L2288
      int v1513 = v1512;	// L2289
      half v1514 = v1482[0][v1513];	// L2290
      int32_t v1515 = wcnt3[0];	// L2291
      int v1516 = v1515;	// L2292
      win_d3[0][v1516] = v1514;	// L2293
      int32_t v1517 = rp3[0];	// L2294
      int v1518 = v1517;	// L2295
      int32_t v1519 = v1483[0][v1518];	// L2296
      int32_t v1520 = wcnt3[0];	// L2297
      int v1521 = v1520;	// L2298
      win_f3[0][v1521] = v1519;	// L2299
      int32_t v1522 = rp3[0];	// L2300
      int32_t v1523 = wcnt3[0];	// L2301
      int v1524 = v1523;	// L2302
      win_s3[0][v1524] = v1522;	// L2303
      int32_t v1525 = wcnt3[0];	// L2304
      ap_int<33> v1526 = v1525;	// L2305
      ap_int<33> v1527 = v1526 + 1;	// L2306
      int32_t v1528 = v1527;	// L2307
      wcnt3[0] = v1528;	// L2308
      int32_t v1529 = rp3[0];	// L2309
      ap_int<33> v1530 = v1529;	// L2310
      ap_int<33> v1531 = v1530 + 1;	// L2311
      int32_t v1532 = v1531;	// L2312
      rp3[0] = v1532;	// L2313
    }
  }
  l_S_t_2_t4: for (int t4 = 0; t4 < 2000; t4++) {	// L2316
  #pragma HLS pipeline II=1
    int32_t v1534 = v1486.read();	// L2317
    int32_t cin3;	// L2318
    cin3 = v1534;	// L2319
    int32_t v1536 = cin3;	// L2320
    int32_t v1537 = dcred3[0];	// L2321
    ap_int<33> v1538 = v1537;	// L2322
    ap_int<33> v1539 = v1536;	// L2323
    ap_int<33> v1540 = v1538 + v1539;	// L2324
    int32_t v1541 = v1540;	// L2325
    dcred3[0] = v1541;	// L2326
    ap_uint<17> w3;	// L2327
    w3 = 0;	// L2328
    int32_t popd3;	// L2329
    popd3 = 0;	// L2330
    int32_t v1544 = wcnt3[0];	// L2331
    bool v1545 = v1544 > 0;	// L2332
    int32_t v1546 = win_s3[0][0];	// L2333
    ap_int<33> v1547 = t4;	// L2334
    ap_int<33> v1548 = v1546;	// L2335
    bool v1549 = v1547 >= v1548;	// L2336
    bool v1550 = v1545 & v1549;	// L2337
    if (v1550) {	// L2338
      int32_t v1551 = win_f3[0][0];	// L2339
      bool v1552 = v1551 == 0;	// L2340
      if (v1552) {	// L2341
        popd3 = 1;	// L2342
      } else {
        int32_t v1553 = dcred3[0];	// L2344
        bool v1554 = v1553 > 0;	// L2345
        if (v1554) {	// L2346
          ap_int<17> v1555 = w3;	// L2347
          ap_int<17> v1556;
          ap_int<17> v1556_tmp = v1555;
          v1556_tmp[0] = 1;          v1556 = v1556_tmp;	// L2348
          w3 = v1556;	// L2349
          half v1557 = win_d3[0][0];	// L2350
          uint16_t v1558;
          union { half from; uint16_t to;} _converter_v1557_to_v1558 = {};
          _converter_v1557_to_v1558.from = v1557;
          v1558 = _converter_v1557_to_v1558.to;	// L2351
          ap_int<17> v1559 = w3;	// L2352
          ap_int<17> v1560;
          ap_int<17> v1560_tmp = v1559;
          v1560_tmp(16, 1) = v1558;
          v1560 = v1560_tmp;	// L2353
          w3 = v1560;	// L2354
          int32_t v1561 = dcred3[0];	// L2355
          ap_int<33> v1562 = v1561;	// L2356
          ap_int<33> v1563 = v1562 - 1;	// L2357
          int32_t v1564 = v1563;	// L2358
          dcred3[0] = v1564;	// L2359
          popd3 = 1;	// L2360
        }
      }
    }
    int32_t v1565 = popd3;	// L2364
    bool v1566 = v1565 == 1;	// L2365
    if (v1566) {	// L2366
      l_S_sft_2_sft4: for (int sft4 = 0; sft4 < 3; sft4++) {	// L2367
        half v1568 = win_d3[0][(sft4 + 1)];	// L2368
        win_d3[0][sft4] = v1568;	// L2369
        int32_t v1569 = win_f3[0][(sft4 + 1)];	// L2370
        win_f3[0][sft4] = v1569;	// L2371
        int32_t v1570 = win_s3[0][(sft4 + 1)];	// L2372
        win_s3[0][sft4] = v1570;	// L2373
      }
      int32_t v1571 = wcnt3[0];	// L2375
      ap_int<33> v1572 = v1571;	// L2376
      ap_int<33> v1573 = v1572 - 1;	// L2377
      int32_t v1574 = v1573;	// L2378
      wcnt3[0] = v1574;	// L2379
    }
    int32_t v1575 = rp3[0];	// L2381
    bool v1576 = v1575 < 2000;	// L2382
    int32_t v1577 = wcnt3[0];	// L2383
    bool v1578 = v1577 < 4;	// L2384
    bool v1579 = v1576 & v1578;	// L2385
    if (v1579) {	// L2386
      int32_t v1580 = rp3[0];	// L2387
      int v1581 = v1580;	// L2388
      half v1582 = v1482[0][v1581];	// L2389
      int32_t v1583 = wcnt3[0];	// L2390
      int v1584 = v1583;	// L2391
      win_d3[0][v1584] = v1582;	// L2392
      int32_t v1585 = rp3[0];	// L2393
      int v1586 = v1585;	// L2394
      int32_t v1587 = v1483[0][v1586];	// L2395
      int32_t v1588 = wcnt3[0];	// L2396
      int v1589 = v1588;	// L2397
      win_f3[0][v1589] = v1587;	// L2398
      int32_t v1590 = rp3[0];	// L2399
      int32_t v1591 = wcnt3[0];	// L2400
      int v1592 = v1591;	// L2401
      win_s3[0][v1592] = v1590;	// L2402
      int32_t v1593 = wcnt3[0];	// L2403
      ap_int<33> v1594 = v1593;	// L2404
      ap_int<33> v1595 = v1594 + 1;	// L2405
      int32_t v1596 = v1595;	// L2406
      wcnt3[0] = v1596;	// L2407
      int32_t v1597 = rp3[0];	// L2408
      ap_int<33> v1598 = v1597;	// L2409
      ap_int<33> v1599 = v1598 + 1;	// L2410
      int32_t v1600 = v1599;	// L2411
      rp3[0] = v1600;	// L2412
    }
    ap_int<17> v1601 = w3;	// L2414
    v1485.write(v1601);	// L2415
  }
}

void col_w_0(
  half v1602[1][2000],
  int32_t v1603[1][1],
  hls::stream< int32_t >& v1604,
  hls::stream< ap_uint<17> >& v1605
) {
  #pragma HLS array_partition variable=v1602 complete dim=1	// L2419
  int32_t k2[1];	// L2428
  for (int v1607 = 0; v1607 < 1; v1607++) {	// L2429
    k2[v1607] = 0;	// L2429
  }
  int32_t cret[1];	// L2430
  for (int v1609 = 0; v1609 < 1; v1609++) {	// L2431
    cret[v1609] = 0;	// L2431
  }
  int32_t zc;	// L2432
  zc = 0;	// L2433
  int32_t v1611 = v1603[0][0];	// L2434
  ap_int<33> v1612 = v1611;	// L2435
  ap_int<33> v1613 = v1612 - 1;	// L2436
  int v1614 = v1613;	// L2437
  for (int v1615 = 0; v1615 < v1614; v1615 += 1) {	// L2438
    int32_t v1616 = zc;	// L2439
    v1604.write(v1616);	// L2440
  }
  cret[0] = 2;	// L2442
  int32_t v1617 = cret[0];	// L2443
  v1604.write(v1617);	// L2444
  l_S_t_1_t5: for (int t5 = 0; t5 < 2000; t5++) {	// L2445
  #pragma HLS pipeline II=1
    ap_uint<17> v1619 = v1605.read();	// L2446
    ap_uint<17> w4;	// L2447
    w4 = v1619;	// L2448
    cret[0] = 0;	// L2449
    ap_int<17> v1621 = w4;	// L2450
    bool v1622;
    ap_int<17> v1622_tmp = v1621;
    v1622 = v1622_tmp[0];	// L2451
    int32_t v1623 = v1622;	// L2452
    bool v1624 = v1623 == 1;	// L2453
    if (v1624) {	// L2454
      cret[0] = 1;	// L2455
      int32_t v1625 = k2[0];	// L2456
      bool v1626 = v1625 < 2000;	// L2457
      if (v1626) {	// L2458
        ap_int<17> v1627 = w4;	// L2459
        int16_t v1628;
        ap_int<17> v1628_tmp = v1627;
        v1628 = v1628_tmp(16, 1);	// L2460
        half v1629;
        union { uint16_t from; half to;} _converter_v1628_to_v1629 = {};
        _converter_v1628_to_v1629.from = v1628;
        v1629 = _converter_v1628_to_v1629.to;	// L2461
        int32_t v1630 = k2[0];	// L2462
        int v1631 = v1630;	// L2463
        v1602[0][v1631] = v1629;	// L2464
        int32_t v1632 = k2[0];	// L2465
        ap_int<33> v1633 = v1632;	// L2466
        ap_int<33> v1634 = v1633 + 1;	// L2467
        int32_t v1635 = v1634;	// L2468
        k2[0] = v1635;	// L2469
      }
    }
    int32_t v1636 = cret[0];	// L2472
    v1604.write(v1636);	// L2473
  }
}

void col_e_0(
  half v1637[1][2000],
  int32_t v1638[1][1],
  hls::stream< int32_t >& v1639,
  hls::stream< ap_uint<17> >& v1640
) {
  #pragma HLS array_partition variable=v1637 complete dim=1	// L2477
  int32_t k3[1];	// L2486
  for (int v1642 = 0; v1642 < 1; v1642++) {	// L2487
    k3[v1642] = 0;	// L2487
  }
  int32_t cret1[1];	// L2488
  for (int v1644 = 0; v1644 < 1; v1644++) {	// L2489
    cret1[v1644] = 0;	// L2489
  }
  int32_t zc1;	// L2490
  zc1 = 0;	// L2491
  int32_t v1646 = v1638[0][0];	// L2492
  ap_int<33> v1647 = v1646;	// L2493
  ap_int<33> v1648 = v1647 - 1;	// L2494
  int v1649 = v1648;	// L2495
  for (int v1650 = 0; v1650 < v1649; v1650 += 1) {	// L2496
    int32_t v1651 = zc1;	// L2497
    v1639.write(v1651);	// L2498
  }
  cret1[0] = 2;	// L2500
  int32_t v1652 = cret1[0];	// L2501
  v1639.write(v1652);	// L2502
  l_S_t_1_t6: for (int t6 = 0; t6 < 2000; t6++) {	// L2503
  #pragma HLS pipeline II=1
    ap_uint<17> v1654 = v1640.read();	// L2504
    ap_uint<17> w5;	// L2505
    w5 = v1654;	// L2506
    cret1[0] = 0;	// L2507
    ap_int<17> v1656 = w5;	// L2508
    bool v1657;
    ap_int<17> v1657_tmp = v1656;
    v1657 = v1657_tmp[0];	// L2509
    int32_t v1658 = v1657;	// L2510
    bool v1659 = v1658 == 1;	// L2511
    if (v1659) {	// L2512
      cret1[0] = 1;	// L2513
      int32_t v1660 = k3[0];	// L2514
      bool v1661 = v1660 < 2000;	// L2515
      if (v1661) {	// L2516
        ap_int<17> v1662 = w5;	// L2517
        int16_t v1663;
        ap_int<17> v1663_tmp = v1662;
        v1663 = v1663_tmp(16, 1);	// L2518
        half v1664;
        union { uint16_t from; half to;} _converter_v1663_to_v1664 = {};
        _converter_v1663_to_v1664.from = v1663;
        v1664 = _converter_v1663_to_v1664.to;	// L2519
        int32_t v1665 = k3[0];	// L2520
        int v1666 = v1665;	// L2521
        v1637[0][v1666] = v1664;	// L2522
        int32_t v1667 = k3[0];	// L2523
        ap_int<33> v1668 = v1667;	// L2524
        ap_int<33> v1669 = v1668 + 1;	// L2525
        int32_t v1670 = v1669;	// L2526
        k3[0] = v1670;	// L2527
      }
    }
    int32_t v1671 = cret1[0];	// L2530
    v1639.write(v1671);	// L2531
  }
}

void col_n_0(
  half v1672[1][2000],
  int32_t v1673[1][1],
  hls::stream< int32_t >& v1674,
  hls::stream< ap_uint<17> >& v1675
) {
  #pragma HLS array_partition variable=v1672 complete dim=1	// L2535
  int32_t k4[1];	// L2544
  for (int v1677 = 0; v1677 < 1; v1677++) {	// L2545
    k4[v1677] = 0;	// L2545
  }
  int32_t cret2[1];	// L2546
  for (int v1679 = 0; v1679 < 1; v1679++) {	// L2547
    cret2[v1679] = 0;	// L2547
  }
  int32_t zc2;	// L2548
  zc2 = 0;	// L2549
  int32_t v1681 = v1673[0][0];	// L2550
  ap_int<33> v1682 = v1681;	// L2551
  ap_int<33> v1683 = v1682 - 1;	// L2552
  int v1684 = v1683;	// L2553
  for (int v1685 = 0; v1685 < v1684; v1685 += 1) {	// L2554
    int32_t v1686 = zc2;	// L2555
    v1674.write(v1686);	// L2556
  }
  cret2[0] = 2;	// L2558
  int32_t v1687 = cret2[0];	// L2559
  v1674.write(v1687);	// L2560
  l_S_t_1_t7: for (int t7 = 0; t7 < 2000; t7++) {	// L2561
  #pragma HLS pipeline II=1
    ap_uint<17> v1689 = v1675.read();	// L2562
    ap_uint<17> w6;	// L2563
    w6 = v1689;	// L2564
    cret2[0] = 0;	// L2565
    ap_int<17> v1691 = w6;	// L2566
    bool v1692;
    ap_int<17> v1692_tmp = v1691;
    v1692 = v1692_tmp[0];	// L2567
    int32_t v1693 = v1692;	// L2568
    bool v1694 = v1693 == 1;	// L2569
    if (v1694) {	// L2570
      cret2[0] = 1;	// L2571
      int32_t v1695 = k4[0];	// L2572
      bool v1696 = v1695 < 2000;	// L2573
      if (v1696) {	// L2574
        ap_int<17> v1697 = w6;	// L2575
        int16_t v1698;
        ap_int<17> v1698_tmp = v1697;
        v1698 = v1698_tmp(16, 1);	// L2576
        half v1699;
        union { uint16_t from; half to;} _converter_v1698_to_v1699 = {};
        _converter_v1698_to_v1699.from = v1698;
        v1699 = _converter_v1698_to_v1699.to;	// L2577
        int32_t v1700 = k4[0];	// L2578
        int v1701 = v1700;	// L2579
        v1672[0][v1701] = v1699;	// L2580
        int32_t v1702 = k4[0];	// L2581
        ap_int<33> v1703 = v1702;	// L2582
        ap_int<33> v1704 = v1703 + 1;	// L2583
        int32_t v1705 = v1704;	// L2584
        k4[0] = v1705;	// L2585
      }
    }
    int32_t v1706 = cret2[0];	// L2588
    v1674.write(v1706);	// L2589
  }
}

void col_s_0(
  half v1707[1][2000],
  int32_t v1708[1][1],
  hls::stream< int32_t >& v1709,
  hls::stream< ap_uint<17> >& v1710
) {
  #pragma HLS array_partition variable=v1707 complete dim=1	// L2593
  int32_t k5[1];	// L2602
  for (int v1712 = 0; v1712 < 1; v1712++) {	// L2603
    k5[v1712] = 0;	// L2603
  }
  int32_t cret3[1];	// L2604
  for (int v1714 = 0; v1714 < 1; v1714++) {	// L2605
    cret3[v1714] = 0;	// L2605
  }
  int32_t zc3;	// L2606
  zc3 = 0;	// L2607
  int32_t v1716 = v1708[0][0];	// L2608
  ap_int<33> v1717 = v1716;	// L2609
  ap_int<33> v1718 = v1717 - 1;	// L2610
  int v1719 = v1718;	// L2611
  for (int v1720 = 0; v1720 < v1719; v1720 += 1) {	// L2612
    int32_t v1721 = zc3;	// L2613
    v1709.write(v1721);	// L2614
  }
  cret3[0] = 2;	// L2616
  int32_t v1722 = cret3[0];	// L2617
  v1709.write(v1722);	// L2618
  l_S_t_1_t8: for (int t8 = 0; t8 < 2000; t8++) {	// L2619
  #pragma HLS pipeline II=1
    ap_uint<17> v1724 = v1710.read();	// L2620
    ap_uint<17> w7;	// L2621
    w7 = v1724;	// L2622
    cret3[0] = 0;	// L2623
    ap_int<17> v1726 = w7;	// L2624
    bool v1727;
    ap_int<17> v1727_tmp = v1726;
    v1727 = v1727_tmp[0];	// L2625
    int32_t v1728 = v1727;	// L2626
    bool v1729 = v1728 == 1;	// L2627
    if (v1729) {	// L2628
      cret3[0] = 1;	// L2629
      int32_t v1730 = k5[0];	// L2630
      bool v1731 = v1730 < 2000;	// L2631
      if (v1731) {	// L2632
        ap_int<17> v1732 = w7;	// L2633
        int16_t v1733;
        ap_int<17> v1733_tmp = v1732;
        v1733 = v1733_tmp(16, 1);	// L2634
        half v1734;
        union { uint16_t from; half to;} _converter_v1733_to_v1734 = {};
        _converter_v1733_to_v1734.from = v1733;
        v1734 = _converter_v1733_to_v1734.to;	// L2635
        int32_t v1735 = k5[0];	// L2636
        int v1736 = v1735;	// L2637
        v1707[0][v1736] = v1734;	// L2638
        int32_t v1737 = k5[0];	// L2639
        ap_int<33> v1738 = v1737;	// L2640
        ap_int<33> v1739 = v1738 + 1;	// L2641
        int32_t v1740 = v1739;	// L2642
        k5[0] = v1740;	// L2643
      }
    }
    int32_t v1741 = cret3[0];	// L2646
    v1709.write(v1741);	// L2647
  }
}

void rdrv_w_0(
  int32_t v1742[1][2000],
  int32_t v1743[1][1],
  hls::stream< ap_uint<26> >& v1744,
  hls::stream< int32_t >& v1745
) {
  #pragma HLS array_partition variable=v1742 complete dim=1	// L2651
  int32_t dcred4[1];	// L2661
  for (int v1747 = 0; v1747 < 1; v1747++) {	// L2662
    dcred4[v1747] = 0;	// L2662
  }
  int32_t rp4[1];	// L2663
  for (int v1749 = 0; v1749 < 1; v1749++) {	// L2664
    rp4[v1749] = 0;	// L2664
  }
  int32_t wcnt4[1];	// L2665
  for (int v1751 = 0; v1751 < 1; v1751++) {	// L2666
    wcnt4[v1751] = 0;	// L2666
  }
  ap_uint<26> win_p[1][4];	// L2667
  for (int v1753 = 0; v1753 < 1; v1753++) {	// L2668
    for (int v1754 = 0; v1754 < 4; v1754++) {	// L2668
      win_p[v1753][v1754] = 0;	// L2668
    }
  }
  ap_uint<26> zp;	// L2669
  zp = 0;	// L2670
  int32_t v1756 = v1743[0][0];	// L2671
  ap_int<33> v1757 = v1756;	// L2672
  ap_int<33> v1758 = v1757 - 1;	// L2673
  int v1759 = v1758;	// L2674
  for (int v1760 = 0; v1760 < v1759; v1760 += 1) {	// L2675
    ap_int<26> v1761 = zp;	// L2676
    v1744.write(v1761);	// L2677
  }
  l_S__pf_1__pf4: for (int _pf4 = 0; _pf4 < 2; _pf4++) {	// L2679
    int32_t v1763 = rp4[0];	// L2680
    bool v1764 = v1763 < 2000;	// L2681
    if (v1764) {	// L2682
      ap_uint<26> cnd;	// L2683
      cnd = 0;	// L2684
      int32_t v1766 = rp4[0];	// L2685
      int v1767 = v1766;	// L2686
      int32_t v1768 = v1742[0][v1767];	// L2687
      ap_uint<26> v1769 = v1768;	// L2688
      ap_int<26> v1770 = cnd;	// L2689
      ap_int<26> v1771;
      ap_int<26> v1771_tmp = v1770;
      v1771_tmp(25, 0) = v1769;
      v1771 = v1771_tmp;	// L2690
      cnd = v1771;	// L2691
      ap_int<26> v1772 = cnd;	// L2692
      int32_t v1773 = wcnt4[0];	// L2693
      int v1774 = v1773;	// L2694
      win_p[0][v1774] = v1772;	// L2695
      int32_t v1775 = wcnt4[0];	// L2696
      ap_int<33> v1776 = v1775;	// L2697
      ap_int<33> v1777 = v1776 + 1;	// L2698
      int32_t v1778 = v1777;	// L2699
      wcnt4[0] = v1778;	// L2700
      int32_t v1779 = rp4[0];	// L2701
      ap_int<33> v1780 = v1779;	// L2702
      ap_int<33> v1781 = v1780 + 1;	// L2703
      int32_t v1782 = v1781;	// L2704
      rp4[0] = v1782;	// L2705
    }
  }
  l_S_t_2_t9: for (int t9 = 0; t9 < 2000; t9++) {	// L2708
  #pragma HLS pipeline II=1
    int32_t v1784 = v1745.read();	// L2709
    int32_t cin4;	// L2710
    cin4 = v1784;	// L2711
    int32_t v1786 = cin4;	// L2712
    int32_t v1787 = dcred4[0];	// L2713
    ap_int<33> v1788 = v1787;	// L2714
    ap_int<33> v1789 = v1786;	// L2715
    ap_int<33> v1790 = v1788 + v1789;	// L2716
    int32_t v1791 = v1790;	// L2717
    dcred4[0] = v1791;	// L2718
    ap_uint<26> pw;	// L2719
    pw = 0;	// L2720
    ap_uint<26> v1793 = win_p[0][0];	// L2721
    ap_uint<26> hp;	// L2722
    hp = v1793;	// L2723
    int32_t popd4;	// L2724
    popd4 = 0;	// L2725
    int32_t v1796 = wcnt4[0];	// L2726
    bool v1797 = v1796 > 0;	// L2727
    if (v1797) {	// L2728
      ap_int<26> v1798 = hp;	// L2729
      bool v1799;
      ap_int<26> v1799_tmp = v1798;
      v1799 = v1799_tmp[25];	// L2730
      int32_t v1800 = v1799;	// L2731
      bool v1801 = v1800 == 0;	// L2732
      if (v1801) {	// L2733
        popd4 = 1;	// L2734
      } else {
        int32_t v1802 = dcred4[0];	// L2736
        bool v1803 = v1802 > 0;	// L2737
        if (v1803) {	// L2738
          ap_int<26> v1804 = hp;	// L2739
          pw = v1804;	// L2740
          int32_t v1805 = dcred4[0];	// L2741
          ap_int<33> v1806 = v1805;	// L2742
          ap_int<33> v1807 = v1806 - 1;	// L2743
          int32_t v1808 = v1807;	// L2744
          dcred4[0] = v1808;	// L2745
          popd4 = 1;	// L2746
        }
      }
    }
    int32_t v1809 = popd4;	// L2750
    bool v1810 = v1809 == 1;	// L2751
    if (v1810) {	// L2752
      l_S_sft_2_sft5: for (int sft5 = 0; sft5 < 3; sft5++) {	// L2753
        ap_uint<26> v1812 = win_p[0][(sft5 + 1)];	// L2754
        win_p[0][sft5] = v1812;	// L2755
      }
      int32_t v1813 = wcnt4[0];	// L2757
      ap_int<33> v1814 = v1813;	// L2758
      ap_int<33> v1815 = v1814 - 1;	// L2759
      int32_t v1816 = v1815;	// L2760
      wcnt4[0] = v1816;	// L2761
    }
    int32_t v1817 = rp4[0];	// L2763
    bool v1818 = v1817 < 2000;	// L2764
    int32_t v1819 = wcnt4[0];	// L2765
    bool v1820 = v1819 < 4;	// L2766
    bool v1821 = v1818 & v1820;	// L2767
    if (v1821) {	// L2768
      ap_uint<26> cnd2;	// L2769
      cnd2 = 0;	// L2770
      int32_t v1823 = rp4[0];	// L2771
      int v1824 = v1823;	// L2772
      int32_t v1825 = v1742[0][v1824];	// L2773
      ap_uint<26> v1826 = v1825;	// L2774
      ap_int<26> v1827 = cnd2;	// L2775
      ap_int<26> v1828;
      ap_int<26> v1828_tmp = v1827;
      v1828_tmp(25, 0) = v1826;
      v1828 = v1828_tmp;	// L2776
      cnd2 = v1828;	// L2777
      ap_int<26> v1829 = cnd2;	// L2778
      int32_t v1830 = wcnt4[0];	// L2779
      int v1831 = v1830;	// L2780
      win_p[0][v1831] = v1829;	// L2781
      int32_t v1832 = wcnt4[0];	// L2782
      ap_int<33> v1833 = v1832;	// L2783
      ap_int<33> v1834 = v1833 + 1;	// L2784
      int32_t v1835 = v1834;	// L2785
      wcnt4[0] = v1835;	// L2786
      int32_t v1836 = rp4[0];	// L2787
      ap_int<33> v1837 = v1836;	// L2788
      ap_int<33> v1838 = v1837 + 1;	// L2789
      int32_t v1839 = v1838;	// L2790
      rp4[0] = v1839;	// L2791
    }
    ap_int<26> v1840 = pw;	// L2793
    v1744.write(v1840);	// L2794
  }
}

void rdrv_e_0(
  int32_t v1841[1][2000],
  int32_t v1842[1][1],
  hls::stream< ap_uint<26> >& v1843,
  hls::stream< int32_t >& v1844
) {
  #pragma HLS array_partition variable=v1841 complete dim=1	// L2798
  int32_t dcred5[1];	// L2808
  for (int v1846 = 0; v1846 < 1; v1846++) {	// L2809
    dcred5[v1846] = 0;	// L2809
  }
  int32_t rp5[1];	// L2810
  for (int v1848 = 0; v1848 < 1; v1848++) {	// L2811
    rp5[v1848] = 0;	// L2811
  }
  int32_t wcnt5[1];	// L2812
  for (int v1850 = 0; v1850 < 1; v1850++) {	// L2813
    wcnt5[v1850] = 0;	// L2813
  }
  ap_uint<26> win_p1[1][4];	// L2814
  for (int v1852 = 0; v1852 < 1; v1852++) {	// L2815
    for (int v1853 = 0; v1853 < 4; v1853++) {	// L2815
      win_p1[v1852][v1853] = 0;	// L2815
    }
  }
  ap_uint<26> zp1;	// L2816
  zp1 = 0;	// L2817
  int32_t v1855 = v1842[0][0];	// L2818
  ap_int<33> v1856 = v1855;	// L2819
  ap_int<33> v1857 = v1856 - 1;	// L2820
  int v1858 = v1857;	// L2821
  for (int v1859 = 0; v1859 < v1858; v1859 += 1) {	// L2822
    ap_int<26> v1860 = zp1;	// L2823
    v1843.write(v1860);	// L2824
  }
  l_S__pf_1__pf5: for (int _pf5 = 0; _pf5 < 2; _pf5++) {	// L2826
    int32_t v1862 = rp5[0];	// L2827
    bool v1863 = v1862 < 2000;	// L2828
    if (v1863) {	// L2829
      ap_uint<26> cnd1;	// L2830
      cnd1 = 0;	// L2831
      int32_t v1865 = rp5[0];	// L2832
      int v1866 = v1865;	// L2833
      int32_t v1867 = v1841[0][v1866];	// L2834
      ap_uint<26> v1868 = v1867;	// L2835
      ap_int<26> v1869 = cnd1;	// L2836
      ap_int<26> v1870;
      ap_int<26> v1870_tmp = v1869;
      v1870_tmp(25, 0) = v1868;
      v1870 = v1870_tmp;	// L2837
      cnd1 = v1870;	// L2838
      ap_int<26> v1871 = cnd1;	// L2839
      int32_t v1872 = wcnt5[0];	// L2840
      int v1873 = v1872;	// L2841
      win_p1[0][v1873] = v1871;	// L2842
      int32_t v1874 = wcnt5[0];	// L2843
      ap_int<33> v1875 = v1874;	// L2844
      ap_int<33> v1876 = v1875 + 1;	// L2845
      int32_t v1877 = v1876;	// L2846
      wcnt5[0] = v1877;	// L2847
      int32_t v1878 = rp5[0];	// L2848
      ap_int<33> v1879 = v1878;	// L2849
      ap_int<33> v1880 = v1879 + 1;	// L2850
      int32_t v1881 = v1880;	// L2851
      rp5[0] = v1881;	// L2852
    }
  }
  l_S_t_2_t10: for (int t10 = 0; t10 < 2000; t10++) {	// L2855
  #pragma HLS pipeline II=1
    int32_t v1883 = v1844.read();	// L2856
    int32_t cin5;	// L2857
    cin5 = v1883;	// L2858
    int32_t v1885 = cin5;	// L2859
    int32_t v1886 = dcred5[0];	// L2860
    ap_int<33> v1887 = v1886;	// L2861
    ap_int<33> v1888 = v1885;	// L2862
    ap_int<33> v1889 = v1887 + v1888;	// L2863
    int32_t v1890 = v1889;	// L2864
    dcred5[0] = v1890;	// L2865
    ap_uint<26> pw1;	// L2866
    pw1 = 0;	// L2867
    ap_uint<26> v1892 = win_p1[0][0];	// L2868
    ap_uint<26> hp1;	// L2869
    hp1 = v1892;	// L2870
    int32_t popd5;	// L2871
    popd5 = 0;	// L2872
    int32_t v1895 = wcnt5[0];	// L2873
    bool v1896 = v1895 > 0;	// L2874
    if (v1896) {	// L2875
      ap_int<26> v1897 = hp1;	// L2876
      bool v1898;
      ap_int<26> v1898_tmp = v1897;
      v1898 = v1898_tmp[25];	// L2877
      int32_t v1899 = v1898;	// L2878
      bool v1900 = v1899 == 0;	// L2879
      if (v1900) {	// L2880
        popd5 = 1;	// L2881
      } else {
        int32_t v1901 = dcred5[0];	// L2883
        bool v1902 = v1901 > 0;	// L2884
        if (v1902) {	// L2885
          ap_int<26> v1903 = hp1;	// L2886
          pw1 = v1903;	// L2887
          int32_t v1904 = dcred5[0];	// L2888
          ap_int<33> v1905 = v1904;	// L2889
          ap_int<33> v1906 = v1905 - 1;	// L2890
          int32_t v1907 = v1906;	// L2891
          dcred5[0] = v1907;	// L2892
          popd5 = 1;	// L2893
        }
      }
    }
    int32_t v1908 = popd5;	// L2897
    bool v1909 = v1908 == 1;	// L2898
    if (v1909) {	// L2899
      l_S_sft_2_sft6: for (int sft6 = 0; sft6 < 3; sft6++) {	// L2900
        ap_uint<26> v1911 = win_p1[0][(sft6 + 1)];	// L2901
        win_p1[0][sft6] = v1911;	// L2902
      }
      int32_t v1912 = wcnt5[0];	// L2904
      ap_int<33> v1913 = v1912;	// L2905
      ap_int<33> v1914 = v1913 - 1;	// L2906
      int32_t v1915 = v1914;	// L2907
      wcnt5[0] = v1915;	// L2908
    }
    int32_t v1916 = rp5[0];	// L2910
    bool v1917 = v1916 < 2000;	// L2911
    int32_t v1918 = wcnt5[0];	// L2912
    bool v1919 = v1918 < 4;	// L2913
    bool v1920 = v1917 & v1919;	// L2914
    if (v1920) {	// L2915
      ap_uint<26> cnd21;	// L2916
      cnd21 = 0;	// L2917
      int32_t v1922 = rp5[0];	// L2918
      int v1923 = v1922;	// L2919
      int32_t v1924 = v1841[0][v1923];	// L2920
      ap_uint<26> v1925 = v1924;	// L2921
      ap_int<26> v1926 = cnd21;	// L2922
      ap_int<26> v1927;
      ap_int<26> v1927_tmp = v1926;
      v1927_tmp(25, 0) = v1925;
      v1927 = v1927_tmp;	// L2923
      cnd21 = v1927;	// L2924
      ap_int<26> v1928 = cnd21;	// L2925
      int32_t v1929 = wcnt5[0];	// L2926
      int v1930 = v1929;	// L2927
      win_p1[0][v1930] = v1928;	// L2928
      int32_t v1931 = wcnt5[0];	// L2929
      ap_int<33> v1932 = v1931;	// L2930
      ap_int<33> v1933 = v1932 + 1;	// L2931
      int32_t v1934 = v1933;	// L2932
      wcnt5[0] = v1934;	// L2933
      int32_t v1935 = rp5[0];	// L2934
      ap_int<33> v1936 = v1935;	// L2935
      ap_int<33> v1937 = v1936 + 1;	// L2936
      int32_t v1938 = v1937;	// L2937
      rp5[0] = v1938;	// L2938
    }
    ap_int<26> v1939 = pw1;	// L2940
    v1843.write(v1939);	// L2941
  }
}

void rdrv_n_0(
  int32_t v1940[1][2000],
  int32_t v1941[1][1],
  hls::stream< ap_uint<26> >& v1942,
  hls::stream< int32_t >& v1943
) {
  #pragma HLS array_partition variable=v1940 complete dim=1	// L2945
  int32_t dcred6[1];	// L2955
  for (int v1945 = 0; v1945 < 1; v1945++) {	// L2956
    dcred6[v1945] = 0;	// L2956
  }
  int32_t rp6[1];	// L2957
  for (int v1947 = 0; v1947 < 1; v1947++) {	// L2958
    rp6[v1947] = 0;	// L2958
  }
  int32_t wcnt6[1];	// L2959
  for (int v1949 = 0; v1949 < 1; v1949++) {	// L2960
    wcnt6[v1949] = 0;	// L2960
  }
  ap_uint<26> win_p2[1][4];	// L2961
  for (int v1951 = 0; v1951 < 1; v1951++) {	// L2962
    for (int v1952 = 0; v1952 < 4; v1952++) {	// L2962
      win_p2[v1951][v1952] = 0;	// L2962
    }
  }
  ap_uint<26> zp2;	// L2963
  zp2 = 0;	// L2964
  int32_t v1954 = v1941[0][0];	// L2965
  ap_int<33> v1955 = v1954;	// L2966
  ap_int<33> v1956 = v1955 - 1;	// L2967
  int v1957 = v1956;	// L2968
  for (int v1958 = 0; v1958 < v1957; v1958 += 1) {	// L2969
    ap_int<26> v1959 = zp2;	// L2970
    v1942.write(v1959);	// L2971
  }
  l_S__pf_1__pf6: for (int _pf6 = 0; _pf6 < 2; _pf6++) {	// L2973
    int32_t v1961 = rp6[0];	// L2974
    bool v1962 = v1961 < 2000;	// L2975
    if (v1962) {	// L2976
      ap_uint<26> cnd2;	// L2977
      cnd2 = 0;	// L2978
      int32_t v1964 = rp6[0];	// L2979
      int v1965 = v1964;	// L2980
      int32_t v1966 = v1940[0][v1965];	// L2981
      ap_uint<26> v1967 = v1966;	// L2982
      ap_int<26> v1968 = cnd2;	// L2983
      ap_int<26> v1969;
      ap_int<26> v1969_tmp = v1968;
      v1969_tmp(25, 0) = v1967;
      v1969 = v1969_tmp;	// L2984
      cnd2 = v1969;	// L2985
      ap_int<26> v1970 = cnd2;	// L2986
      int32_t v1971 = wcnt6[0];	// L2987
      int v1972 = v1971;	// L2988
      win_p2[0][v1972] = v1970;	// L2989
      int32_t v1973 = wcnt6[0];	// L2990
      ap_int<33> v1974 = v1973;	// L2991
      ap_int<33> v1975 = v1974 + 1;	// L2992
      int32_t v1976 = v1975;	// L2993
      wcnt6[0] = v1976;	// L2994
      int32_t v1977 = rp6[0];	// L2995
      ap_int<33> v1978 = v1977;	// L2996
      ap_int<33> v1979 = v1978 + 1;	// L2997
      int32_t v1980 = v1979;	// L2998
      rp6[0] = v1980;	// L2999
    }
  }
  l_S_t_2_t11: for (int t11 = 0; t11 < 2000; t11++) {	// L3002
  #pragma HLS pipeline II=1
    int32_t v1982 = v1943.read();	// L3003
    int32_t cin6;	// L3004
    cin6 = v1982;	// L3005
    int32_t v1984 = cin6;	// L3006
    int32_t v1985 = dcred6[0];	// L3007
    ap_int<33> v1986 = v1985;	// L3008
    ap_int<33> v1987 = v1984;	// L3009
    ap_int<33> v1988 = v1986 + v1987;	// L3010
    int32_t v1989 = v1988;	// L3011
    dcred6[0] = v1989;	// L3012
    ap_uint<26> pw2;	// L3013
    pw2 = 0;	// L3014
    ap_uint<26> v1991 = win_p2[0][0];	// L3015
    ap_uint<26> hp2;	// L3016
    hp2 = v1991;	// L3017
    int32_t popd6;	// L3018
    popd6 = 0;	// L3019
    int32_t v1994 = wcnt6[0];	// L3020
    bool v1995 = v1994 > 0;	// L3021
    if (v1995) {	// L3022
      ap_int<26> v1996 = hp2;	// L3023
      bool v1997;
      ap_int<26> v1997_tmp = v1996;
      v1997 = v1997_tmp[25];	// L3024
      int32_t v1998 = v1997;	// L3025
      bool v1999 = v1998 == 0;	// L3026
      if (v1999) {	// L3027
        popd6 = 1;	// L3028
      } else {
        int32_t v2000 = dcred6[0];	// L3030
        bool v2001 = v2000 > 0;	// L3031
        if (v2001) {	// L3032
          ap_int<26> v2002 = hp2;	// L3033
          pw2 = v2002;	// L3034
          int32_t v2003 = dcred6[0];	// L3035
          ap_int<33> v2004 = v2003;	// L3036
          ap_int<33> v2005 = v2004 - 1;	// L3037
          int32_t v2006 = v2005;	// L3038
          dcred6[0] = v2006;	// L3039
          popd6 = 1;	// L3040
        }
      }
    }
    int32_t v2007 = popd6;	// L3044
    bool v2008 = v2007 == 1;	// L3045
    if (v2008) {	// L3046
      l_S_sft_2_sft7: for (int sft7 = 0; sft7 < 3; sft7++) {	// L3047
        ap_uint<26> v2010 = win_p2[0][(sft7 + 1)];	// L3048
        win_p2[0][sft7] = v2010;	// L3049
      }
      int32_t v2011 = wcnt6[0];	// L3051
      ap_int<33> v2012 = v2011;	// L3052
      ap_int<33> v2013 = v2012 - 1;	// L3053
      int32_t v2014 = v2013;	// L3054
      wcnt6[0] = v2014;	// L3055
    }
    int32_t v2015 = rp6[0];	// L3057
    bool v2016 = v2015 < 2000;	// L3058
    int32_t v2017 = wcnt6[0];	// L3059
    bool v2018 = v2017 < 4;	// L3060
    bool v2019 = v2016 & v2018;	// L3061
    if (v2019) {	// L3062
      ap_uint<26> cnd22;	// L3063
      cnd22 = 0;	// L3064
      int32_t v2021 = rp6[0];	// L3065
      int v2022 = v2021;	// L3066
      int32_t v2023 = v1940[0][v2022];	// L3067
      ap_uint<26> v2024 = v2023;	// L3068
      ap_int<26> v2025 = cnd22;	// L3069
      ap_int<26> v2026;
      ap_int<26> v2026_tmp = v2025;
      v2026_tmp(25, 0) = v2024;
      v2026 = v2026_tmp;	// L3070
      cnd22 = v2026;	// L3071
      ap_int<26> v2027 = cnd22;	// L3072
      int32_t v2028 = wcnt6[0];	// L3073
      int v2029 = v2028;	// L3074
      win_p2[0][v2029] = v2027;	// L3075
      int32_t v2030 = wcnt6[0];	// L3076
      ap_int<33> v2031 = v2030;	// L3077
      ap_int<33> v2032 = v2031 + 1;	// L3078
      int32_t v2033 = v2032;	// L3079
      wcnt6[0] = v2033;	// L3080
      int32_t v2034 = rp6[0];	// L3081
      ap_int<33> v2035 = v2034;	// L3082
      ap_int<33> v2036 = v2035 + 1;	// L3083
      int32_t v2037 = v2036;	// L3084
      rp6[0] = v2037;	// L3085
    }
    ap_int<26> v2038 = pw2;	// L3087
    v1942.write(v2038);	// L3088
  }
}

void rdrv_s_0(
  int32_t v2039[1][2000],
  int32_t v2040[1][1],
  hls::stream< ap_uint<26> >& v2041,
  hls::stream< int32_t >& v2042
) {
  #pragma HLS array_partition variable=v2039 complete dim=1	// L3092
  int32_t dcred7[1];	// L3102
  for (int v2044 = 0; v2044 < 1; v2044++) {	// L3103
    dcred7[v2044] = 0;	// L3103
  }
  int32_t rp7[1];	// L3104
  for (int v2046 = 0; v2046 < 1; v2046++) {	// L3105
    rp7[v2046] = 0;	// L3105
  }
  int32_t wcnt7[1];	// L3106
  for (int v2048 = 0; v2048 < 1; v2048++) {	// L3107
    wcnt7[v2048] = 0;	// L3107
  }
  ap_uint<26> win_p3[1][4];	// L3108
  for (int v2050 = 0; v2050 < 1; v2050++) {	// L3109
    for (int v2051 = 0; v2051 < 4; v2051++) {	// L3109
      win_p3[v2050][v2051] = 0;	// L3109
    }
  }
  ap_uint<26> zp3;	// L3110
  zp3 = 0;	// L3111
  int32_t v2053 = v2040[0][0];	// L3112
  ap_int<33> v2054 = v2053;	// L3113
  ap_int<33> v2055 = v2054 - 1;	// L3114
  int v2056 = v2055;	// L3115
  for (int v2057 = 0; v2057 < v2056; v2057 += 1) {	// L3116
    ap_int<26> v2058 = zp3;	// L3117
    v2041.write(v2058);	// L3118
  }
  l_S__pf_1__pf7: for (int _pf7 = 0; _pf7 < 2; _pf7++) {	// L3120
    int32_t v2060 = rp7[0];	// L3121
    bool v2061 = v2060 < 2000;	// L3122
    if (v2061) {	// L3123
      ap_uint<26> cnd3;	// L3124
      cnd3 = 0;	// L3125
      int32_t v2063 = rp7[0];	// L3126
      int v2064 = v2063;	// L3127
      int32_t v2065 = v2039[0][v2064];	// L3128
      ap_uint<26> v2066 = v2065;	// L3129
      ap_int<26> v2067 = cnd3;	// L3130
      ap_int<26> v2068;
      ap_int<26> v2068_tmp = v2067;
      v2068_tmp(25, 0) = v2066;
      v2068 = v2068_tmp;	// L3131
      cnd3 = v2068;	// L3132
      ap_int<26> v2069 = cnd3;	// L3133
      int32_t v2070 = wcnt7[0];	// L3134
      int v2071 = v2070;	// L3135
      win_p3[0][v2071] = v2069;	// L3136
      int32_t v2072 = wcnt7[0];	// L3137
      ap_int<33> v2073 = v2072;	// L3138
      ap_int<33> v2074 = v2073 + 1;	// L3139
      int32_t v2075 = v2074;	// L3140
      wcnt7[0] = v2075;	// L3141
      int32_t v2076 = rp7[0];	// L3142
      ap_int<33> v2077 = v2076;	// L3143
      ap_int<33> v2078 = v2077 + 1;	// L3144
      int32_t v2079 = v2078;	// L3145
      rp7[0] = v2079;	// L3146
    }
  }
  l_S_t_2_t12: for (int t12 = 0; t12 < 2000; t12++) {	// L3149
  #pragma HLS pipeline II=1
    int32_t v2081 = v2042.read();	// L3150
    int32_t cin7;	// L3151
    cin7 = v2081;	// L3152
    int32_t v2083 = cin7;	// L3153
    int32_t v2084 = dcred7[0];	// L3154
    ap_int<33> v2085 = v2084;	// L3155
    ap_int<33> v2086 = v2083;	// L3156
    ap_int<33> v2087 = v2085 + v2086;	// L3157
    int32_t v2088 = v2087;	// L3158
    dcred7[0] = v2088;	// L3159
    ap_uint<26> pw3;	// L3160
    pw3 = 0;	// L3161
    ap_uint<26> v2090 = win_p3[0][0];	// L3162
    ap_uint<26> hp3;	// L3163
    hp3 = v2090;	// L3164
    int32_t popd7;	// L3165
    popd7 = 0;	// L3166
    int32_t v2093 = wcnt7[0];	// L3167
    bool v2094 = v2093 > 0;	// L3168
    if (v2094) {	// L3169
      ap_int<26> v2095 = hp3;	// L3170
      bool v2096;
      ap_int<26> v2096_tmp = v2095;
      v2096 = v2096_tmp[25];	// L3171
      int32_t v2097 = v2096;	// L3172
      bool v2098 = v2097 == 0;	// L3173
      if (v2098) {	// L3174
        popd7 = 1;	// L3175
      } else {
        int32_t v2099 = dcred7[0];	// L3177
        bool v2100 = v2099 > 0;	// L3178
        if (v2100) {	// L3179
          ap_int<26> v2101 = hp3;	// L3180
          pw3 = v2101;	// L3181
          int32_t v2102 = dcred7[0];	// L3182
          ap_int<33> v2103 = v2102;	// L3183
          ap_int<33> v2104 = v2103 - 1;	// L3184
          int32_t v2105 = v2104;	// L3185
          dcred7[0] = v2105;	// L3186
          popd7 = 1;	// L3187
        }
      }
    }
    int32_t v2106 = popd7;	// L3191
    bool v2107 = v2106 == 1;	// L3192
    if (v2107) {	// L3193
      l_S_sft_2_sft8: for (int sft8 = 0; sft8 < 3; sft8++) {	// L3194
        ap_uint<26> v2109 = win_p3[0][(sft8 + 1)];	// L3195
        win_p3[0][sft8] = v2109;	// L3196
      }
      int32_t v2110 = wcnt7[0];	// L3198
      ap_int<33> v2111 = v2110;	// L3199
      ap_int<33> v2112 = v2111 - 1;	// L3200
      int32_t v2113 = v2112;	// L3201
      wcnt7[0] = v2113;	// L3202
    }
    int32_t v2114 = rp7[0];	// L3204
    bool v2115 = v2114 < 2000;	// L3205
    int32_t v2116 = wcnt7[0];	// L3206
    bool v2117 = v2116 < 4;	// L3207
    bool v2118 = v2115 & v2117;	// L3208
    if (v2118) {	// L3209
      ap_uint<26> cnd23;	// L3210
      cnd23 = 0;	// L3211
      int32_t v2120 = rp7[0];	// L3212
      int v2121 = v2120;	// L3213
      int32_t v2122 = v2039[0][v2121];	// L3214
      ap_uint<26> v2123 = v2122;	// L3215
      ap_int<26> v2124 = cnd23;	// L3216
      ap_int<26> v2125;
      ap_int<26> v2125_tmp = v2124;
      v2125_tmp(25, 0) = v2123;
      v2125 = v2125_tmp;	// L3217
      cnd23 = v2125;	// L3218
      ap_int<26> v2126 = cnd23;	// L3219
      int32_t v2127 = wcnt7[0];	// L3220
      int v2128 = v2127;	// L3221
      win_p3[0][v2128] = v2126;	// L3222
      int32_t v2129 = wcnt7[0];	// L3223
      ap_int<33> v2130 = v2129;	// L3224
      ap_int<33> v2131 = v2130 + 1;	// L3225
      int32_t v2132 = v2131;	// L3226
      wcnt7[0] = v2132;	// L3227
      int32_t v2133 = rp7[0];	// L3228
      ap_int<33> v2134 = v2133;	// L3229
      ap_int<33> v2135 = v2134 + 1;	// L3230
      int32_t v2136 = v2135;	// L3231
      rp7[0] = v2136;	// L3232
    }
    ap_int<26> v2137 = pw3;	// L3234
    v2041.write(v2137);	// L3235
  }
}

void rclc_w_0(
  int32_t v2138[1][2000],
  int32_t v2139[1][1],
  hls::stream< int32_t >& v2140,
  hls::stream< ap_uint<26> >& v2141
) {
  #pragma HLS array_partition variable=v2138 complete dim=1	// L3239
  int32_t k6[1];	// L3249
  for (int v2143 = 0; v2143 < 1; v2143++) {	// L3250
    k6[v2143] = 0;	// L3250
  }
  int32_t cret4[1];	// L3251
  for (int v2145 = 0; v2145 < 1; v2145++) {	// L3252
    cret4[v2145] = 0;	// L3252
  }
  int32_t zc4;	// L3253
  zc4 = 0;	// L3254
  int32_t v2147 = v2139[0][0];	// L3255
  ap_int<33> v2148 = v2147;	// L3256
  ap_int<33> v2149 = v2148 - 1;	// L3257
  int v2150 = v2149;	// L3258
  for (int v2151 = 0; v2151 < v2150; v2151 += 1) {	// L3259
    int32_t v2152 = zc4;	// L3260
    v2140.write(v2152);	// L3261
  }
  cret4[0] = 2;	// L3263
  int32_t v2153 = cret4[0];	// L3264
  v2140.write(v2153);	// L3265
  l_S_t_1_t13: for (int t13 = 0; t13 < 2000; t13++) {	// L3266
  #pragma HLS pipeline II=1
    ap_uint<26> v2155 = v2141.read();	// L3267
    ap_uint<26> pw4;	// L3268
    pw4 = v2155;	// L3269
    cret4[0] = 0;	// L3270
    ap_int<26> v2157 = pw4;	// L3271
    bool v2158;
    ap_int<26> v2158_tmp = v2157;
    v2158 = v2158_tmp[25];	// L3272
    int32_t v2159 = v2158;	// L3273
    bool v2160 = v2159 == 1;	// L3274
    if (v2160) {	// L3275
      cret4[0] = 1;	// L3276
      int32_t v2161 = k6[0];	// L3277
      bool v2162 = v2161 < 2000;	// L3278
      if (v2162) {	// L3279
        ap_int<26> v2163 = pw4;	// L3280
        int32_t v2164 = v2163;	// L3281
        int32_t v2165 = v2164 & 67108863;	// L3282
        int32_t v2166 = k6[0];	// L3283
        int v2167 = v2166;	// L3284
        v2138[0][v2167] = v2165;	// L3285
        int32_t v2168 = k6[0];	// L3286
        ap_int<33> v2169 = v2168;	// L3287
        ap_int<33> v2170 = v2169 + 1;	// L3288
        int32_t v2171 = v2170;	// L3289
        k6[0] = v2171;	// L3290
      }
    }
    int32_t v2172 = cret4[0];	// L3293
    v2140.write(v2172);	// L3294
  }
}

void rclc_e_0(
  int32_t v2173[1][2000],
  int32_t v2174[1][1],
  hls::stream< int32_t >& v2175,
  hls::stream< ap_uint<26> >& v2176
) {
  #pragma HLS array_partition variable=v2173 complete dim=1	// L3298
  int32_t k7[1];	// L3308
  for (int v2178 = 0; v2178 < 1; v2178++) {	// L3309
    k7[v2178] = 0;	// L3309
  }
  int32_t cret5[1];	// L3310
  for (int v2180 = 0; v2180 < 1; v2180++) {	// L3311
    cret5[v2180] = 0;	// L3311
  }
  int32_t zc5;	// L3312
  zc5 = 0;	// L3313
  int32_t v2182 = v2174[0][0];	// L3314
  ap_int<33> v2183 = v2182;	// L3315
  ap_int<33> v2184 = v2183 - 1;	// L3316
  int v2185 = v2184;	// L3317
  for (int v2186 = 0; v2186 < v2185; v2186 += 1) {	// L3318
    int32_t v2187 = zc5;	// L3319
    v2175.write(v2187);	// L3320
  }
  cret5[0] = 2;	// L3322
  int32_t v2188 = cret5[0];	// L3323
  v2175.write(v2188);	// L3324
  l_S_t_1_t14: for (int t14 = 0; t14 < 2000; t14++) {	// L3325
  #pragma HLS pipeline II=1
    ap_uint<26> v2190 = v2176.read();	// L3326
    ap_uint<26> pw5;	// L3327
    pw5 = v2190;	// L3328
    cret5[0] = 0;	// L3329
    ap_int<26> v2192 = pw5;	// L3330
    bool v2193;
    ap_int<26> v2193_tmp = v2192;
    v2193 = v2193_tmp[25];	// L3331
    int32_t v2194 = v2193;	// L3332
    bool v2195 = v2194 == 1;	// L3333
    if (v2195) {	// L3334
      cret5[0] = 1;	// L3335
      int32_t v2196 = k7[0];	// L3336
      bool v2197 = v2196 < 2000;	// L3337
      if (v2197) {	// L3338
        ap_int<26> v2198 = pw5;	// L3339
        int32_t v2199 = v2198;	// L3340
        int32_t v2200 = v2199 & 67108863;	// L3341
        int32_t v2201 = k7[0];	// L3342
        int v2202 = v2201;	// L3343
        v2173[0][v2202] = v2200;	// L3344
        int32_t v2203 = k7[0];	// L3345
        ap_int<33> v2204 = v2203;	// L3346
        ap_int<33> v2205 = v2204 + 1;	// L3347
        int32_t v2206 = v2205;	// L3348
        k7[0] = v2206;	// L3349
      }
    }
    int32_t v2207 = cret5[0];	// L3352
    v2175.write(v2207);	// L3353
  }
}

void rclc_n_0(
  int32_t v2208[1][2000],
  int32_t v2209[1][1],
  hls::stream< int32_t >& v2210,
  hls::stream< ap_uint<26> >& v2211
) {
  #pragma HLS array_partition variable=v2208 complete dim=1	// L3357
  int32_t k8[1];	// L3367
  for (int v2213 = 0; v2213 < 1; v2213++) {	// L3368
    k8[v2213] = 0;	// L3368
  }
  int32_t cret6[1];	// L3369
  for (int v2215 = 0; v2215 < 1; v2215++) {	// L3370
    cret6[v2215] = 0;	// L3370
  }
  int32_t zc6;	// L3371
  zc6 = 0;	// L3372
  int32_t v2217 = v2209[0][0];	// L3373
  ap_int<33> v2218 = v2217;	// L3374
  ap_int<33> v2219 = v2218 - 1;	// L3375
  int v2220 = v2219;	// L3376
  for (int v2221 = 0; v2221 < v2220; v2221 += 1) {	// L3377
    int32_t v2222 = zc6;	// L3378
    v2210.write(v2222);	// L3379
  }
  cret6[0] = 2;	// L3381
  int32_t v2223 = cret6[0];	// L3382
  v2210.write(v2223);	// L3383
  l_S_t_1_t15: for (int t15 = 0; t15 < 2000; t15++) {	// L3384
  #pragma HLS pipeline II=1
    ap_uint<26> v2225 = v2211.read();	// L3385
    ap_uint<26> pw6;	// L3386
    pw6 = v2225;	// L3387
    cret6[0] = 0;	// L3388
    ap_int<26> v2227 = pw6;	// L3389
    bool v2228;
    ap_int<26> v2228_tmp = v2227;
    v2228 = v2228_tmp[25];	// L3390
    int32_t v2229 = v2228;	// L3391
    bool v2230 = v2229 == 1;	// L3392
    if (v2230) {	// L3393
      cret6[0] = 1;	// L3394
      int32_t v2231 = k8[0];	// L3395
      bool v2232 = v2231 < 2000;	// L3396
      if (v2232) {	// L3397
        ap_int<26> v2233 = pw6;	// L3398
        int32_t v2234 = v2233;	// L3399
        int32_t v2235 = v2234 & 67108863;	// L3400
        int32_t v2236 = k8[0];	// L3401
        int v2237 = v2236;	// L3402
        v2208[0][v2237] = v2235;	// L3403
        int32_t v2238 = k8[0];	// L3404
        ap_int<33> v2239 = v2238;	// L3405
        ap_int<33> v2240 = v2239 + 1;	// L3406
        int32_t v2241 = v2240;	// L3407
        k8[0] = v2241;	// L3408
      }
    }
    int32_t v2242 = cret6[0];	// L3411
    v2210.write(v2242);	// L3412
  }
}

void rclc_s_0(
  int32_t v2243[1][2000],
  int32_t v2244[1][1],
  hls::stream< int32_t >& v2245,
  hls::stream< ap_uint<26> >& v2246
) {
  #pragma HLS array_partition variable=v2243 complete dim=1	// L3416
  int32_t k9[1];	// L3426
  for (int v2248 = 0; v2248 < 1; v2248++) {	// L3427
    k9[v2248] = 0;	// L3427
  }
  int32_t cret7[1];	// L3428
  for (int v2250 = 0; v2250 < 1; v2250++) {	// L3429
    cret7[v2250] = 0;	// L3429
  }
  int32_t zc7;	// L3430
  zc7 = 0;	// L3431
  int32_t v2252 = v2244[0][0];	// L3432
  ap_int<33> v2253 = v2252;	// L3433
  ap_int<33> v2254 = v2253 - 1;	// L3434
  int v2255 = v2254;	// L3435
  for (int v2256 = 0; v2256 < v2255; v2256 += 1) {	// L3436
    int32_t v2257 = zc7;	// L3437
    v2245.write(v2257);	// L3438
  }
  cret7[0] = 2;	// L3440
  int32_t v2258 = cret7[0];	// L3441
  v2245.write(v2258);	// L3442
  l_S_t_1_t16: for (int t16 = 0; t16 < 2000; t16++) {	// L3443
  #pragma HLS pipeline II=1
    ap_uint<26> v2260 = v2246.read();	// L3444
    ap_uint<26> pw7;	// L3445
    pw7 = v2260;	// L3446
    cret7[0] = 0;	// L3447
    ap_int<26> v2262 = pw7;	// L3448
    bool v2263;
    ap_int<26> v2263_tmp = v2262;
    v2263 = v2263_tmp[25];	// L3449
    int32_t v2264 = v2263;	// L3450
    bool v2265 = v2264 == 1;	// L3451
    if (v2265) {	// L3452
      cret7[0] = 1;	// L3453
      int32_t v2266 = k9[0];	// L3454
      bool v2267 = v2266 < 2000;	// L3455
      if (v2267) {	// L3456
        ap_int<26> v2268 = pw7;	// L3457
        int32_t v2269 = v2268;	// L3458
        int32_t v2270 = v2269 & 67108863;	// L3459
        int32_t v2271 = k9[0];	// L3460
        int v2272 = v2271;	// L3461
        v2243[0][v2272] = v2270;	// L3462
        int32_t v2273 = k9[0];	// L3463
        ap_int<33> v2274 = v2273;	// L3464
        ap_int<33> v2275 = v2274 + 1;	// L3465
        int32_t v2276 = v2275;	// L3466
        k9[0] = v2276;	// L3467
      }
    }
    int32_t v2277 = cret7[0];	// L3470
    v2245.write(v2277);	// L3471
  }
}

/// This is top function.
void top(
  int32_t v2278[1][1],
  half v2279[1][2000],
  int32_t v2280[1][2000],
  half v2281[1][2000],
  int32_t v2282[1][2000],
  half v2283[1][2000],
  int32_t v2284[1][2000],
  half v2285[1][2000],
  int32_t v2286[1][2000],
  half v2287[1][2000],
  half v2288[1][2000],
  half v2289[1][2000],
  half v2290[1][2000],
  int32_t v2291[1][2000],
  int32_t v2292[1][2000],
  int32_t v2293[1][2000],
  int32_t v2294[1][2000],
  int32_t v2295[1][2000],
  int32_t v2296[1][2000],
  int32_t v2297[1][2000],
  int32_t v2298[1][2000]
) {	// L3475
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v2299;
  #pragma HLS stream variable=v2299 depth=8	// L3476
  hls::stream< ap_uint<17> > v2300;
  #pragma HLS stream variable=v2300 depth=8	// L3477
  hls::stream< ap_uint<17> > v2301;
  #pragma HLS stream variable=v2301 depth=8	// L3478
  hls::stream< ap_uint<17> > v2302;
  #pragma HLS stream variable=v2302 depth=8	// L3479
  hls::stream< ap_uint<17> > v2303;
  #pragma HLS stream variable=v2303 depth=8	// L3480
  hls::stream< ap_uint<17> > v2304;
  #pragma HLS stream variable=v2304 depth=8	// L3481
  hls::stream< ap_uint<17> > v2305;
  #pragma HLS stream variable=v2305 depth=8	// L3482
  hls::stream< ap_uint<17> > v2306;
  #pragma HLS stream variable=v2306 depth=8	// L3483
  hls::stream< ap_uint<26> > v2307;
  #pragma HLS stream variable=v2307 depth=8	// L3484
  hls::stream< ap_uint<26> > v2308;
  #pragma HLS stream variable=v2308 depth=8	// L3485
  hls::stream< ap_uint<26> > v2309;
  #pragma HLS stream variable=v2309 depth=8	// L3486
  hls::stream< ap_uint<26> > v2310;
  #pragma HLS stream variable=v2310 depth=8	// L3487
  hls::stream< ap_uint<26> > v2311;
  #pragma HLS stream variable=v2311 depth=8	// L3488
  hls::stream< ap_uint<26> > v2312;
  #pragma HLS stream variable=v2312 depth=8	// L3489
  hls::stream< ap_uint<26> > v2313;
  #pragma HLS stream variable=v2313 depth=8	// L3490
  hls::stream< ap_uint<26> > v2314;
  #pragma HLS stream variable=v2314 depth=8	// L3491
  hls::stream< int32_t > v2315;
  #pragma HLS stream variable=v2315 depth=8	// L3492
  hls::stream< int32_t > v2316;
  #pragma HLS stream variable=v2316 depth=8	// L3493
  hls::stream< int32_t > v2317;
  #pragma HLS stream variable=v2317 depth=8	// L3494
  hls::stream< int32_t > v2318;
  #pragma HLS stream variable=v2318 depth=8	// L3495
  hls::stream< int32_t > v2319;
  #pragma HLS stream variable=v2319 depth=8	// L3496
  hls::stream< int32_t > v2320;
  #pragma HLS stream variable=v2320 depth=8	// L3497
  hls::stream< int32_t > v2321;
  #pragma HLS stream variable=v2321 depth=8	// L3498
  hls::stream< int32_t > v2322;
  #pragma HLS stream variable=v2322 depth=8	// L3499
  hls::stream< int32_t > v2323;
  #pragma HLS stream variable=v2323 depth=8	// L3500
  hls::stream< int32_t > v2324;
  #pragma HLS stream variable=v2324 depth=8	// L3501
  hls::stream< int32_t > v2325;
  #pragma HLS stream variable=v2325 depth=8	// L3502
  hls::stream< int32_t > v2326;
  #pragma HLS stream variable=v2326 depth=8	// L3503
  hls::stream< int32_t > v2327;
  #pragma HLS stream variable=v2327 depth=8	// L3504
  hls::stream< int32_t > v2328;
  #pragma HLS stream variable=v2328 depth=8	// L3505
  hls::stream< int32_t > v2329;
  #pragma HLS stream variable=v2329 depth=8	// L3506
  hls::stream< int32_t > v2330;
  #pragma HLS stream variable=v2330 depth=8	// L3507
  node_0_0(v2278, v2308, v2309, v2312, v2313, v2300, v2301, v2304, v2305, v2315, v2318, v2319, v2322, v2323, v2326, v2327, v2330, v2307, v2310, v2311, v2314, v2316, v2317, v2320, v2321, v2329, v2328, v2325, v2324, v2299, v2302, v2303, v2306);	// L3508
  drv_w_0(v2279, v2280, v2278, v2299, v2323);	// L3509
  drv_e_0(v2281, v2282, v2278, v2302, v2326);	// L3510
  drv_n_0(v2283, v2284, v2278, v2303, v2327);	// L3511
  drv_s_0(v2285, v2286, v2278, v2306, v2330);	// L3512
  col_w_0(v2287, v2278, v2325, v2301);	// L3513
  col_e_0(v2288, v2278, v2324, v2300);	// L3514
  col_n_0(v2289, v2278, v2329, v2305);	// L3515
  col_s_0(v2290, v2278, v2328, v2304);	// L3516
  rdrv_w_0(v2291, v2278, v2307, v2315);	// L3517
  rdrv_e_0(v2292, v2278, v2310, v2318);	// L3518
  rdrv_n_0(v2293, v2278, v2311, v2319);	// L3519
  rdrv_s_0(v2294, v2278, v2314, v2322);	// L3520
  rclc_w_0(v2295, v2278, v2317, v2309);	// L3521
  rclc_e_0(v2296, v2278, v2316, v2308);	// L3522
  rclc_n_0(v2297, v2278, v2321, v2313);	// L3523
  rclc_s_0(v2298, v2278, v2320, v2312);	// L3524
}

